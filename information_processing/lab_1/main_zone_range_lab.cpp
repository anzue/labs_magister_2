#include <vector>
#include <string>
#include <files.h>
#include <spimiindex.h>
#include <logger.h>
#include <zoneranger.h>

using namespace std;

int main_zone_range_lab(int argc, char *argv[]){


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


    ZoneRanger index = ZoneRanger(files);


    vector<string> words;
    string s = "like";


    while(1){
        words = split(s);
        auto res = index.getRelevancy(words);
        Info("\n\n");
        for(auto x:res){
            if(x.second > 0){
                Info("For document " + x.first + " total res is \t  " + to_string(x.second));
            }
        }
        Logger::getInstance().print_logs(std::cout);
        getline(cin,s);
        if(s.length() <= 1){
            break;
        }
    }

    Info("Finished");
    EndTimer();
}



int main(int argc, char *argv[]){
    main_zone_range_lab(argc,argv);
}
