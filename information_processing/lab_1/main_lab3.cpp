#include<files.h>
#include<logger.h>
#include <twowordindex.h>
#include<CoordInvertedIndex.h>

void test_2wordindex(int argc, char *argv[]){
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

    TwoWordIndex index(files);


    vector<string> words;

    string s = "Test test test";

    while(1){
        words = split(s);
        auto res = index.search(words);
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


void test_coordindex(int argc, char *argv[]){
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

    CoordInvertedIndex index(files);


    vector<string> words;

    string s = "test test test";

    while(1){
        words = split(s);
      //  auto res = index.naive_search(words);
        auto res = index.radius_search(words,10);
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

int main_lab3(int argc, char *argv[]){


    StartTimer();
    Info("Starting");
    test_coordindex(argc,argv);
   // test_2wordindex(argc,argv);

    Info("Finished");
    EndTimer();

}


int main(int argc, char *argv[]){
    main_lab3(argc,argv);
}

