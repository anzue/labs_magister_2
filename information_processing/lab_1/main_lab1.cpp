#include <iostream>
#include <vocabulary.h>
#include <logger.h>
#include <mapvocabulary.h>
#include <omp.h>
#include <stdio.h>
#include<dirent.h>
#include <algorithm>
using namespace std;

#define FILE "main.cpp"

#include<files.h>

int main_lab1(int argc, char *argv[]){
    StartTimer();
    Info("Starting");

    vector<string> files;

    for(int i=1;i<argc;++i){
        vector<string> tmp = get_files(argv[i]);
        Info("Adding folder " + string(argv[i]) + ", total count = " + to_string(tmp.size()));
        for(int j=0;j<tmp.size();++j){
            Info(" | File " + tmp[j]);
        }
        Info(" +------------------------------------------");

        files.insert(files.end(),tmp.begin(),tmp.end());
    }
    int sz = files.size();
    int i;
    if(files.size() <= 10){
        Warn("Only " + to_string(files.size()) + " files found in input");
    }

    int threads = 6;
    vector<Vocabulary*> results;

    for(int i=0;i<threads;++i){
        results.push_back(new MapVocabulary());
    }

    int filesize[threads];
    int words_count[threads];

#pragma omp parallel for num_threads(threads)
    for(int i=0;i<sz;++i){
        int tid = omp_get_thread_num();
        Info("Thread " + to_string(tid) + " | Working with file " + files[i]);
        read_file(results[tid],files[i],filesize[tid],words_count[tid]);
        Info("Thread " + to_string(tid) + " | Finished working with file " + files[i]);
    }

    for(int i=0;i<threads;++i){
        ofstream out(to_string(i) + ".txt");
        results[i]->print(out);
    }

    Vocabulary* res = results[0];
    for(int i=1;i<threads;++i){
        res->merge(results[i]);
        filesize[0]+=filesize[i];
        words_count[0]+=words_count[i];
    }
    ofstream out("global_res.txt");
    res->print(out);
    out.close();
    out = ofstream("global_res.json");

    json js;
    js["words_count"] = words_count[0];
    js["filesize"] = filesize[0];
    res->print_json(out,js);
    out.close();
    Info("Finished");
    Info("Runtime = "+std::to_string(EndTimer()));

    return 0;
}

/*
 * Vocabulary is a realy simple and in the same time effective way of saving words
 * It has good insertion time and as a result parsing files is realy fast
 * For speading up algo was split into parallel processes
 *
 * Time complexity -
 *      non-parallel - O( n * log n + m ) where n - number of distinct words, m - total length of files
 *      parallel     - O( (n/k) * log (n/k) + m/k + n*log n) where k is number of subprocesses
 * Note:
 *      Complexity for parallel approach seems worse but most of programm execution time is hard drive reading and paralllel
 *      approach allows to always have something reading from it which makes app work faster
 *      Also both complexities are O-big (worst-case) which means than real complexities might be smaller but impossible to estimate without knowing the strcuture of the data.
 */

