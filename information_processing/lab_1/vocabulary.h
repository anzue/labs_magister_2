#ifndef VOCABULARY_H
#define VOCABULARY_H


#include<string>
#include<iostream>
#include<set>

#include "json.hpp"
using json = nlohmann::json;

using namespace std;

typedef string WORD_TYPE;

// interface class for vocabularies
class Vocabulary
{
private:
    int words_count;
public:
    Vocabulary():words_count(0){}
    virtual void add_word(const WORD_TYPE &s) = 0;
    virtual int get_words_count(){return words_count;}
    virtual void prepare_iteration() = 0;
    virtual WORD_TYPE get_next() = 0;
    virtual void print(ofstream &str) = 0;
    virtual void print_json(ofstream &str,json js = json()) = 0;
    virtual void merge(Vocabulary* other) = 0;
    virtual void print_binary(string filename) = 0;
    virtual void read_binary(string filename) = 0;
};

#endif // VOCABULARY_H
