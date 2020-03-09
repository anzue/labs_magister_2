#include<files.h>
#include<logger.h>
#include<wordtree.h>
#include"ngramindex.h"
#include"permutationindex.h"

void testWordTreePrefix(int argc, char *argv[]){
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

    WordTree word_tree = WordTree(files);

    vector<string> words;

    string s = "like";

    while(1){
        words = split(s);
        auto res = word_tree.get_words(words[0]);
        Info("Searching for " + words[0]);
        Info("Found " + to_string(res.size()));
        for(auto &x:res){
            Info("Found in " + x);
        }
        Logger::getInstance().print_logs(std::cout);
        getline(cin,s);
        if(s.length() <= 1){
            break;
        }
    }

}



void testJokerPermutation(int argc, char *argv[]){
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

    PermutationIndex perm_index = PermutationIndex(files);


    vector<string> words;

    string s = "like";

    while(1){
      //  words = split(s);
        auto res = perm_index.search_joker(s);
        Info("Searching for " + s);
        Info("Found " + to_string(res.size()));
        for(auto &x:res){
            Info("Found in " + x);
        }
        Logger::getInstance().print_logs(std::cout);
        getline(cin,s);
        if(s.length() <= 1){
            break;
        }
    }

}


void testNgramIndex(int argc, char *argv[]){
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

    NgramIndex ngram_index = NgramIndex(3,files);


    vector<string> words;

    string s = "like";

    while(1){
        auto res = ngram_index.search_joker(s);
        Info("Searching for " + s);
        Info("Found " + to_string(res.size()));
        for(auto &x:res){
            Info("Found in " + x);
        }
        Logger::getInstance().print_logs(std::cout);
        getline(cin,s);
        if(s.length() <= 1){
            break;
        }
    }

}


int main_lab4(int argc, char *argv[]){


    StartTimer();
    Info("Starting");
    //testNgramIndex(argc,argv);
     testJokerPermutation(argc,argv);

    Info("Finished");
    EndTimer();

}


int main(int argc, char *argv[]){
    main_lab4(argc,argv);
}

