#ifndef PERMUTATIONINDEX_H
#define PERMUTATIONINDEX_H

#include <string>
#include <set>
#include <vector>
#include <fstream>
#include "logger.h"
#include "files.h"

using namespace std;

class PermutationIndex
{
    set<string> words;

public:
    PermutationIndex(vector<string> files){
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
                        for(int j=0;j<=splited[i].size(); ++j){
                            words.insert(s.substr(j,splited[i].length() + 1));
                        }
                    }
                }
                // cout << ("Voc size ater adding line = " + to_string(voc->get_words_count())) << endl;
            }
            in.close();
        }
    }


    vector<string> search_word(string word){
        set<string>::iterator l,r;
        l = words.lower_bound(word);
        cout << word << " ";
        *word.rbegin() = word.back() + 1;
        r = words.lower_bound(word);
        cout << word;
        return vector<string> (l,r);
    }


    bool is_joker_ok(string word,string joker){
        int joker_pos = 0;
        int word_pos = 0;
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

    vector<string> search_joker(string joker){
        joker += "$";

        int pos = joker.length() - 1;
        while(pos >= 0 && joker[pos] != '*'){
            --pos;
        }
        if(pos >= 0){
            joker = joker.substr(pos + 1, joker.size() - pos) + joker.substr(0,pos + 1);
        }

        Info("normalized joker is " + joker);

        pos = 0;
        while(pos < joker.size() && joker[pos] != '*'){
            ++pos;
        }
        vector<string> res = search_word(joker.substr(0,pos));

        //simple joker res, filter now


        for(auto x:res){
            Info("Plain res " + x);
        }

        vector<string> filtered;
        for(int i=0;i<res.size();++i){
            if(is_joker_ok(res[i],joker)){
                filtered.push_back(res[i]);
            }
        }

        for(auto x:filtered){
            Info("Filetered " + x);
        }

        for(auto &x:filtered){
            int pos = 0;
            while(x[pos] != '$')++pos;
            x = x.substr(pos+1,x.size() - pos) + x.substr(0,pos);
        }

        return filtered;
    }
};

#endif // PERMUTATIONINDEX_H
