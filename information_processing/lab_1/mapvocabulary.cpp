#include<iostream>
#include<fstream>

#include "mapvocabulary.h"



MapVocabulary::MapVocabulary():
    words(),words_count(0){}

void MapVocabulary::add_word(const WORD_TYPE &s){
    words.insert(s);
}

void MapVocabulary::prepare_iteration(){
    it = words.begin();
}

WORD_TYPE MapVocabulary::get_next(){
    return (it != words.end())?(*it++):(static_cast<void>(it++), "");
}

int MapVocabulary::get_words_count(){
    words_count = static_cast<int>(words.size());
    return words_count;
}

void MapVocabulary::print(ofstream &str){
    for(WORD_TYPE word:words){
        str << word <<"\n";
    }
}

void MapVocabulary::print_binary(string filename){
    auto myfile = std::fstream(filename, std::ios::out | std::ios::binary);
    // add transformation here
    for(WORD_TYPE word:words){
        myfile.write( reinterpret_cast<char*>(&word[0]), sizeof(word[0])*word.length());
    }
    myfile.close();
}

void MapVocabulary::read_binary(string filename){
    //TODO, with transformation
}

void MapVocabulary::merge(Vocabulary *other){
    int i=other->get_words_count();
    WORD_TYPE word;
    for(other->prepare_iteration();word=other->get_next(),i--;){
        add_word(word);
    }
}

void MapVocabulary::print_json(ofstream &str,json js){
    js["words"] = words;
    str << js;
}
