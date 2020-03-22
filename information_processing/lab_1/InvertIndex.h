#ifndef INVERTINDEX_H
#define INVERTINDEX_H

#include<indexvocabulary.h>

class InvertIndex{
private:
    IndexVocabulary vocabulary;
    vector<vector<int>> docs;
    int docs_count = 0;

public:
    InvertIndex(){
        vocabulary = IndexVocabulary();
    }

    void add_word_doc(WORD_TYPE &word,int doc){
        docs_count = max(docs_count, 1 + doc);
        int id = process_word(word);
        if(docs[id].size() <= 0 || docs[id].back() != doc){
            docs[id].push_back(doc);
        }

    }

    int process_word(WORD_TYPE &word){
        vocabulary.add_word(word);
        int id = vocabulary.get_position(word);
        if(id >= docs.size()){
            docs.push_back(vector<int>());
        }
        return id;
    }

    vector<int> get_word(WORD_TYPE s){
        return docs[process_word(s)];
    }


};




#endif // INVERTINDEX_H
