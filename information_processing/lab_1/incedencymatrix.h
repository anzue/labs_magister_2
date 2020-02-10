#ifndef INCEDENCYMATRIX_H
#define INCEDENCYMATRIX_H
#include<vector>
using std::vector;

#include<indexvocabulary.h>


class IncedencyMatrix
{
    vector<vector<int> > matrix;
    IndexVocabulary vocabulary;
    int docs_count;
public:
    IncedencyMatrix(int docs){
        docs_count = docs;
    }

    int process_word(WORD_TYPE &word){
        vocabulary.add_word(word);
        int id = vocabulary.get_position(word);
        while(matrix.size() <= id){
            matrix.push_back(vector<int>(docs_count,0));
        }
        return id;
    }

    void add(WORD_TYPE &word,int doc){
        matrix[process_word(word)][doc] = 1;
    }

    vector<int> get_word(WORD_TYPE word){
        return matrix[process_word(word)];
    }

};

vector<int> And_im(vector<int> a,vector<int> b){
    vector<int> res(a.size());
    for(int i=0;i<a.size();++i){
        res[i] = a[i] && b[i];
    }
    return res;
}


vector<int> Or_im(vector<int> a,vector<int> b){
    vector<int> res(a.size());
    for(int i=0;i<a.size();++i){
        res[i] = a[i] || b[i];
    }
    return res;
}

vector<int> Not_im(vector<int> a){

    vector<int> res(a.size());
    for(int i=0;i<a.size();++i){
        res[i] = !a[i];
    }
    return res;
}



#endif // INCEDENCYMATRIX_H
