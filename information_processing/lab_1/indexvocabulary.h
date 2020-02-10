#ifndef INDEXVOCABULARY_H
#define INDEXVOCABULARY_H


#include<vocabulary.h>

class IndexVocabulary
{
    map<WORD_TYPE,int> words;
    map<WORD_TYPE,int>::iterator it;
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

};

#endif // INDEXVOCABULARY_H
