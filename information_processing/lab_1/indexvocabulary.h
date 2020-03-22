#ifndef INDEXVOCABULARY_H
#define INDEXVOCABULARY_H

#include <fstream>
#include<vocabulary.h>
#include <logger.h>

class IndexVocabulary
{
    map<WORD_TYPE,int> words;
    //map<WORD_TYPE,int>::iterator it;
    int words_count;
public:
    int add_word(const WORD_TYPE &s){
        if( words.find(s) == words.end()){
            return words[s] = words_count++;
        }
        return words[s];
    }
    int get_position(WORD_TYPE &s){
        return words[s];
    }
    int get_words_count(){return words_count;}

    void save(string filepath){
        ofstream fout(filepath,std::ofstream::out);
        for(auto &x:words){
            fout << x.first <<" " <<x.second << " ";
        }
    }

    void load(string filepath){
        words.clear();
        words_count = 0;
        ifstream fin(filepath,std::ifstream::in);
        WORD_TYPE str;int nom;
        while(fin>>str >> nom){
            words[str] = nom;
            ++words_count;
        }
    }

    map<WORD_TYPE,int> getWords(){
        Warn("Getting all vocabulaty, not recomended, maybe add iterators");
        return words;
    }

    int size(){
        return words.size() * (sizeof(WORD_TYPE) + sizeof(int)) + sizeof(words_count);
    }

};

#endif // INDEXVOCABULARY_H
