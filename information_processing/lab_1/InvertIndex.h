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

vector<int> And_ii(vector<int> a,vector<int> b){
    int b_pos = 0;
    vector<int> res;
    for(int i=0;i<a.size() && b_pos < b.size();++i){
        while(b_pos < b.size() && b[b_pos] < a[i] ) ++ b_pos;
        if(b_pos < b.size() && b[b_pos] == a[i]){
            res.push_back(a[i]);
        }
    }
    return res;
}


vector<int> Or_ii(vector<int> a,vector<int> b){
    int b_pos = 0;
    vector<int> res;
    for(int i=0;i<a.size();++i){
        while(b_pos < b.size() && b[b_pos] < a[i]){
            res.push_back(b[b_pos]);
            ++b_pos;
        }
        res.push_back(a[i]);
    }
    while(b_pos<b.size()){
        res.push_back(b[b_pos++]);
    }
    return res;
}

vector<int> Not_ii(vector<int> a, int doc_count){
    int pos = 0;
    vector<int> res;
    for(int i=0;i<doc_count;++i){
        if(a[pos] == i){
            ++pos;
        }else{
            res.push_back(i);
        }
    }
    return res;
}


#endif // INVERTINDEX_H
