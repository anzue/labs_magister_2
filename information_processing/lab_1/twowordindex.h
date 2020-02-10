#ifndef TWO_WORD_INDEX_H
#define TWO_WORD_INDEX_H

#include "indexvocabulary.h"
#include "logger.h"
#include "files.h"

#include <iostream>
using namespace std;

class DocumentIndex2{
    IndexVocabulary *global_voc;
    map< pair<int,int> , bool> positions;
public:
    string name;
    DocumentIndex2(IndexVocabulary *voc,string filename){
        name = get_filename(filename);
        global_voc = voc;

        ifstream in(filename);

        if(!in) {
            Err("Cannot open file " + filename);
            return;
        }
        int max_line_len = 1000;
        char str[max_line_len];

        while(in) {
            in.getline(str, max_line_len);
            if(in){
                vector<pair<string,int>> splited = split_with_position(string(str));

                if(splited.size() > 0){
                    global_voc->add_word(splited[0].first);
                }
                for(int i=0;i + 1 <splited.size();++i){
                    positions[make_pair(
                                  global_voc->add_word(splited[i].first),
                                  global_voc->add_word(splited[i+1].first))] = true;//.push_back(splited[i].second);
                }
            }
            // cout << ("Voc size ater adding line = " + to_string(voc->get_words_count())) << endl;
        }
        in.close();
    }

    bool search_pair(string a,string b){
        return positions[make_pair(global_voc->add_word(a),global_voc->add_word(b))];

    }

    bool naive_search(vector<string> &search){
        for(int i=0;i<search.size()-1;++i){
            if( !search_pair(search[i],search[i+1])){
                return false;
            }
        }
        return true;
    }

};

class TwoWordIndex
{
    IndexVocabulary vocabulary;
    vector<DocumentIndex2> documents;
public:
    TwoWordIndex(vector<string> files){
        vocabulary = IndexVocabulary();

        for(auto &str:files){
            add_file(str);
        }
    }

    void add_file(string filename){
        documents.push_back(DocumentIndex2(&vocabulary,filename));
    }

    vector<string> search(vector<string> &words){
        vector<string> res;
        for(int i=0;i<documents.size();++i){
            if(documents[i].naive_search(words)){
                res.push_back(documents[i].name);
            }
        }
        return res;
    }
};

#endif // TWO_WORD_INDEX_H
