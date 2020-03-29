#ifndef ZONERANGER_H
#define ZONERANGER_H

#include<indexvocabulary.h>
#include<files.h>

class ZoneIndex{
private:
    vector<vector<int>> docs;
    int docs_count = 0;
    IndexVocabulary* vocabulary;

public:
    ZoneIndex(IndexVocabulary* globalVocabulary){
        vocabulary = globalVocabulary;
        docs_count = 0;
    }

    void add_word_doc(WORD_TYPE &word,int doc){
        docs_count = max(docs_count, 1 + doc);
        int id = process_word(word);
        if(docs[id].size() <= 0 || docs[id].back() != doc){
            docs[id].push_back(doc);
        }

    }

    int process_word(WORD_TYPE &word){
        int id = vocabulary->add_word(word);
        while(id >= docs.size()){
            docs.push_back(vector<int>());
        }
        return id;
    }

    vector<int> get_word(WORD_TYPE s){
        return docs[process_word(s)];
    }

    vector<int> getWords(vector<WORD_TYPE> words, int atLeast){
        if(atLeast <= 0){
            atLeast = words.size();
        }
        map<int,int> counts;

        for(auto &word:words){
            auto x = get_word(word);
            for(auto val:x){
                if(counts.find(val) == counts.end()){
                    counts[val] = 1;
                } else {
                    ++counts[val];
                }
            }
        }
        vector<int> res;
        for(auto &x:counts){
            if(x.second >= atLeast){
                res.push_back(x.first);
            }
        }
        return res;
    }
};


class ZoneRanger
{
private:
    IndexVocabulary vocabulary;
    vector<string> zones =       { "Body", "Info", "Title: ", "Author: ","Release Date: ", "Last Updated:", "Language: ", "Character set encoding:"};
    vector<double> zoneWeights = { 0.6,    0.1,    0.2,      0.1,        0,                 0,            0,             0};
    vector<ZoneIndex> indexes;
    vector<string> filenames;
public:
    ZoneRanger(vector<string> filenames){
        vocabulary = IndexVocabulary();
        indexes = vector<ZoneIndex>(zones.size(),ZoneIndex(&vocabulary));
        addGuttenbergDocuments(filenames);
    }

    void addGutenbergDocument(string filename,int id){
        ifstream in(filename);

        if(!in) {
            Err("Cannot open file " + filename);
            return;
        }
        int max_line_len = 1000;
        char str[max_line_len];

        while(in) {
            in.getline(str, max_line_len);
            if(in){
                if(strlen(str) >= 3 && str[0] == str[1] && str[1] == str[2] && str[2] == '*'){
                    break;
                }
                string tmp = string(str);
                int zoneId = 1;
                for(int i=0;i<zones.size();++i){
                    if(tmp.length() >= zones[i].length() && tmp.substr(0,zones[i].size()) == zones[i]){
                        zoneId  = i;
                    }
                }

                vector<string> splited = split(string(str));
                if(splited.size() > 0){
                    for(int i=0;i<zones.size(); ++i){
                        if(splited[0] == zones[i]){
                            zoneId = i;
                        }
                    }
                }
                for(auto &x:splited){
                    indexes[zoneId].add_word_doc(x,id);
                }
            }
        }

        while(in) {
            in.getline(str, max_line_len);
            if(in){
                if(strlen(str) >= 3 && str[0] == str[1] && str[1] == str[2] && str[2] == '*'){
                    break;
                }
                vector<string> splited = split(string(str));
                for(auto &x:splited){
                    indexes[0].add_word_doc(x,id);
                }
            }
        }
        in.close();
    }

    void addGuttenbergDocuments(vector<string> filenames){
        for(int i=0;i<filenames.size();++i){
            addGutenbergDocument(filenames[i],i+this->filenames.size());
        }
        this->filenames.insert(this->filenames.end(),filenames.begin(),filenames.end());

    }

    vector<pair<string,double>> getRelevancy(vector<WORD_TYPE> request){
        vector<pair<double,int>> totalRes;
        for(int i=0;i<filenames.size();++i){
            totalRes.push_back({0,i});
        }
        for(int i=0;i< zones.size();++i){
            auto x = indexes[i].getWords(request,0);
            for(auto val:x){
                totalRes[val].first += zoneWeights[i];
                Info("Request was found in zone " + zones[i] + " of  file " + filenames[val]);
            }
        }

        sort(totalRes.begin(),totalRes.end(),greater<pair<double,int>>());


        vector<pair<string,double>> res;
        for(int i=0;i<totalRes.size();++i){
            res.push_back({filenames[totalRes[i].second],totalRes[i].first});
        }
        return res;
    }

};

#endif // ZONERANGER_H
