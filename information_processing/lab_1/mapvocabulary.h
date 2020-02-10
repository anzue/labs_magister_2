#ifndef MAPVOCABULARY_H
#define MAPVOCABULARY_H

#include "vocabulary.h"

// naive mathod of saving words: put into vocabulary, be happy
class MapVocabulary:public Vocabulary{
private:
    set<WORD_TYPE> words;
    set<WORD_TYPE>::iterator it;
public:
    MapVocabulary();
    void print_binary(string filename);
    void read_binary(string filename);
    void print_json(ofstream &str,json js = json());
    void print(ofstream &str);

// inhereted from Vocabulary
private:
    int words_count;
public:
    void add_word(const WORD_TYPE &s);
    void prepare_iteration();
    WORD_TYPE get_next();
    int get_words_count();
    void merge(Vocabulary *other);
};
#endif // MAPVOCABULARY_H
