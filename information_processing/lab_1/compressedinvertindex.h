#ifndef COMPRESSEDINVERTINDEX_H
#define COMPRESSEDINVERTINDEX_H

#include <compressedvocabulary.h>
#include <spimiindex.h>


// Gamma codes
class CompressedInvertIndex
{
private:
    CompressedVocabulary vocabulary;
    vector<bool> docs;
    int docs_count = 0;
public:

    CompressedInvertIndex(SpimiIndex &index,int vocBlockSize):vocabulary(vocBlockSize,index.getVocabulary()){
        int lastCharSize = 0;
        char curChar = 0;
        for(int i=0;i<index.getWordsCount();++i){
            WORD_TYPE word = vocabulary.getWordById(i);
            auto val = index.get_word(word);
            for(auto &x:val){
                ++x;
            }

            if(val.size() <= 0){
                continue;
            }
            auto compressed = getCode(val[0]);
            docs.insert(docs.end(),compressed.begin(),compressed.end());
            for(int i=0;i<val.size()-1;++i){
                auto compressed = getCode(val[i+1] - val[i]);
                //cout  << val[i+1] - val[i] << " ";for(auto x:compressed) cout << x ; cout << "\n";
                docs.insert(docs.end(),compressed.begin(),compressed.end());
            }
        }
    }

    vector<bool> getCode(int shift){
        vector<bool> res;
        while(shift > 0){
            if(shift%2){
                res.push_back(1);
            }
            shift/=2;
        }
        res.pop_back();
        int sz = res.size();
        res.push_back(0);
        for(int i=0;i<sz;++i){
            res.push_back(1);
        }
        reverse(res.begin(),res.end());
        return res;
    }

    int size(bool log = false) {
        if(log){
            Info("Compressed index size : " + to_string(docs.size() / 8  + vocabulary.size()));
            Info("Vocabulary       size : " + to_string(vocabulary.size()));
            Info("Docs             size : " + to_string(docs.size()/8));
        }
        return docs.size() / 8  + vocabulary.size();
    }
};


#endif // COMPRESSEDINVERTINDEX_H
