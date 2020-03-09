#ifndef NGRAMINDEX_H
#define NGRAMINDEX_H

#include<vector>
#include<string>
#include<set>
#include<fstream>
#include "files.h"
#include "logger.h"

using namespace std;


class NgramIndex
{
    int index_length;
    map<string, set<string>> index;
public:

    NgramIndex(int n,vector<string> files){
        index_length = n;
        for(auto filename:files){
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
                    vector<string> splited = split(string(str));
                    string s;
                    for(int i=0;i <splited.size();++i){
                        s = splited[i] + "$" +splited[i];
                        for(int j=0;j<s.length()
                                                - index_length; ++j){
                            if(index.find(s.substr(j,index_length)) == index.end()){
                                index[s.substr(j,index_length)] = set<string>();
                            }
                            index[s.substr(j,index_length)].insert(splited[i]);
                        }
                    }
                }
                // cout << ("Voc size ater adding line = " + to_string(voc->get_words_count())) << endl;
            }
            in.close();
        }
    }

    bool is_joker_ok(string word,string joker){
        int joker_pos = 0;
        int word_pos = 0;
        word = "$" + word + "$";
        for(int i=0;i<=joker.size();++i){
            if(joker[i] == '*' || i == joker.size()){
                bool ok = false;
                for(int j = word_pos;j <= word.size() - (i-joker_pos);++j){
                    int g = 0;
                    for(; g <  (i-joker_pos)&& word[j+g] == joker[joker_pos+g]; ++g);
                    if( g >=(i-joker_pos)){
                        word_pos = j + g;
                        ok = true;
                        break;
                    }
                }
                if(!ok){
                    return false;
                }
                joker_pos = i+1;
            }
        }
        return word_pos >= word.size() || joker[joker.size() - 1] == '*';
    }


    vector<string> get_ngram_from_joker(string joker){
        vector<string> res;
        for(int i=0;i<=joker.length() - index_length;++i){
            bool ok = true;
            for(int j=0;j< index_length;++j){
                if(joker[i+j] == '*'){
                    ok = false;
                }
            }
            if(ok){
                res.push_back(joker.substr(i,index_length));
            }
        }
        return res;
    }

    vector<string> search_joker(string joker){
        joker = "$" + joker + "$";
        Info("normalized joker is " + joker);
        vector<string> ngram_joker = get_ngram_from_joker(joker);
        if(ngram_joker.size() <= 0){
            return vector<string>();
        }
        vector<string> candidates = vector<string>(index[ngram_joker[0]].begin(),index[ngram_joker[0]].end());
        vector<string> filtered;
        for(int i=1;i<ngram_joker.size();++i){
            auto &cur_set = index[ngram_joker[i]];
            for(auto &x:candidates){
                if( cur_set.find(x) != cur_set.end()){
                    filtered.push_back(x);
                }
            }
            candidates = filtered;
            filtered = vector<string>();
        }

        for(auto &x:candidates){
            Info("Candidate = " + x);
        }

        for(auto &x:candidates){
            if(is_joker_ok(x,joker)){
                filtered.push_back(x);
            }
        }
        return filtered;
    }
};

#endif // NGRAMINDEX_H
