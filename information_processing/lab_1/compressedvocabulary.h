#ifndef COMPRESSEDVOCABULARY_H
#define COMPRESSEDVOCABULARY_H

#include <map>
#include <files.h>
#include <fstream>
#include <indexvocabulary.h>

using namespace std;

// block compression
class CompressedVocabulary
{
public:

    string allWords = "";
    vector<int> wordPositions;
    int k;
    int wordsCount;
public:

    CompressedVocabulary(int newK, IndexVocabulary voc){
        k = newK;
        auto words = voc.getWords();
        auto it = words.begin();
        wordsCount = words.size();
        for(int i=0;i<words.size();++i){
            if(i% k == 0){
                wordPositions.push_back(allWords.length());
            }
            allWords.push_back(char(it->first.length()));
            allWords += it->first;
            ++it;
        }
    }

    string getWordById(int id){
        int startPos = wordPositions[id/k];
        for(int i=0;i<id%k;++i){
            startPos += allWords[startPos] + 1;
        }
        return wordAtPos(startPos);
    }

    string wordAtPos(int pos){
        return allWords.substr(pos+1, allWords[pos]);
    }

    int get_position(WORD_TYPE &s){
        int l = 0;
        int r = wordPositions.size() - 1;
        while(l<r){
            int m = (l+r)/2;
            if(s >= wordAtPos(wordPositions[m])){
                l = m;
            }else {
                r = m-1;
            }
        }
        Info( "Search for "+ s + " pos = " +to_string(l) +" "+to_string(r)+ "\n");
        int pos = wordPositions[l];
        for(int i=0;i<k && pos < allWords.size();++i){
            if(wordAtPos(pos) == s){
                return l*k + i;
            }
            pos += allWords[i] + 1;
        }
        Info("Word " + s + " not found");
        return 0;
    }

    //int get_words_count(){return words_count;}

    void save(string filepath){
        ofstream fout(filepath,std::ofstream::out);
        fout << wordPositions.size();
        for(auto x:wordPositions){
            fout << x << " ";
        }
        fout << "\n" << allWords <<"\n";

    }

    void load(string filepath){
        ifstream in(filepath);
        wordPositions.clear();
        int size,val;
        in >> size;
        while(size --){
            in >> val;
            wordPositions.push_back(val);
        }
        in >> allWords;
    }

    int size(){
        return wordPositions.size()* sizeof(int) +allWords.size();
    }

};

#endif // COMPRESSEDVOCABULARY_H
