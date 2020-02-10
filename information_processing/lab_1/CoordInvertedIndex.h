#ifndef COORDINVERTEDINDEX_H
#define COORDINVERTEDINDEX_H

#include "indexvocabulary.h"
#include "files.h"
#include "logger.h"
#include <algorithm>

using std::max;

class WordInfo{
public:
    map<int,vector<int>> word_doc_positions;

    void add(int doc, int pos){
        if(word_doc_positions.find(doc) == word_doc_positions.end()){
            word_doc_positions[doc] = vector<int>();
        }
        word_doc_positions[doc].push_back(pos);
    }
};


class CoordInvertedIndex{
    IndexVocabulary vocabulary;
    vector<WordInfo> words;
    int doc_id;
    vector<string> names;
public:
    CoordInvertedIndex(vector<string> files){
        names = files;
        doc_id = 0;
        vocabulary = IndexVocabulary();
        for(auto &x:files){
            process_file(x);
        }
    }

    void process_file(string filename){

        ifstream in(filename);

        if(!in) {
            Err("Cannot open file " + filename);
            return;
        }
        int max_line_len = 1000;
        char str[max_line_len];
        int total_pos = 0;
        while(in) {
            in.getline(str, max_line_len);
            if(in){
                vector<string> splited = split(string(str));

                for(int i=0;i<splited.size();++i){
                    int pos = vocabulary.add_word(splited[i]);
                    while(pos >= words.size()){
                        words.resize(max(pos+1,(int)words.size()));
                    }
                    words[ pos ].add(doc_id,total_pos + i);
                }
                total_pos += splited.size();
            }
            // cout << ("Voc size ater adding line = " + to_string(voc->get_words_count())) << endl;
        }
        in.close();
        ++doc_id;
    }

    map<int,vector<int>> megre_docs_simple( map<int,vector<int>> v1, map<int,vector<int>> v2){

        vector<int> t1,t2;
        map<int,vector<int>> res;
        for(auto &info:v1){
            if(v2.find(info.first) != v2.end()){
                vector<int> &t1 = info.second;
                vector<int> &t2 = v2[info.first];
                vector<int> inters;
                int pos_w2 = 0;
                for(int i=0;i<t1.size()&& pos_w2 < t2.size() ;++i){
                    while(pos_w2 < t2.size() && t2[pos_w2] + 1 < t1[i]){
                        ++pos_w2;
                    }
                    if(pos_w2 < t2.size() && t2[pos_w2] == t1[i] + 1){
                        if(res.find(info.first) == res.end()){
                            res[info.first] = vector<int>();
                        }
                        res[info.first].push_back(t2[pos_w2]);
                    }
                }
            }
        }
        return res;
    }



    map<int,vector<int>> megre_docs_radius( map<int,vector<int>> v1, map<int,vector<int>> v2,int radius = 1){

        vector<int> t1,t2;
        map<int,vector<int>> res;
        for(auto &info:v1){
            if(v2.find(info.first) != v2.end()){
                vector<int> &t1 = info.second;
                vector<int> &t2 = v2[info.first];
                vector<int> inters;
                int lpos = 0,rpos = 0;
                for(int i=0;i<t1.size()&& lpos < t2.size() ;++i){
                    while(lpos < t2.size() && t2[lpos] + radius < t1[i]){
                        ++lpos;
                    }
                    while(rpos < t2.size() && t2[rpos] - radius < t1[i]){
                        ++rpos;
                    }
                    for(int pos = lpos; pos < rpos; ++ pos){
                        if(res.find(info.first) == res.end()){
                            res[info.first] = vector<int>();
                        }
                        res[info.first].push_back(t2[pos]);
                    }
                }
            }
        }
        return res;
    }

    vector<string> naive_search(vector<string> &search){
        map<int,vector<int> > search_res = words[vocabulary.add_word(search[0])].word_doc_positions;
        for(int i=1;i<search.size();++i){
            for(auto &x:search_res){
                cout << x.first << "," << x.second[0] << " ";
            }cout<<endl;
            search_res = megre_docs_simple(search_res,words[vocabulary.add_word(search[i])].word_doc_positions);
        }
        vector<string> res(search_res.size());
        for(auto &x:search_res){
            res.push_back(names[x.first]);
        }
        return res;
    }

    vector<string> radius_search(vector<string> &search,int radius = 1){
        map<int,vector<int> > search_res = words[vocabulary.add_word(search[0])].word_doc_positions;
        for(int i=1;i<search.size();++i){
            for(auto &x:search_res){
                cout << x.first << "," << x.second[0] << " ";
            }cout<<endl;
            search_res = megre_docs_radius(search_res,words[vocabulary.add_word(search[i])].word_doc_positions,radius);
        }
        vector<string> res;
        for(auto &x:search_res){
            res.push_back(get_filename(names[x.first]));
        }
        return res;
    }

};

#endif // COORDINVERTEDINDEX_H
