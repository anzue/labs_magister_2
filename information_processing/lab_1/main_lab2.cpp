#include<incedencymatrix.h>
#include<invertindex.h>
#include<files.h>
#include<logger.h>

void test_invertindex(int argc, char *argv[]){


    StartTimer();
    Info("Starting");

    InvertIndex index = InvertIndex();

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

    for(int i=0;i<sz;++i){

        string filename = files[i];
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
                vector<string> splited = split(string(str));
                for(auto &x:splited){
                    index.add_word_doc(x,i);
                }
            }
        }
        in.close();
    }

    vector<int> find_this = Or_ii(
                                And_ii(
                                       index.get_word("a"),
                                       index.get_word("b")),

                                Not_ii(
                                       index.get_word("a"),files.size()));


    Info("Request result");

    for(int i=0;i<find_this.size();++i){
        Info(files[find_this[i]]);
    }
    Info("Finished");
    Info("Runtime = "+std::to_string(EndTimer()));
}

void test_incendency_matrix(int argc, char *argv[]){

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

    IncedencyMatrix matrix = IncedencyMatrix(files.size());

    for(int i=0;i<sz;++i){

        string filename = files[i];
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
                vector<string> splited = split(string(str));
                for(auto &x:splited){
                    matrix.add(x,i);
                }
            }
        }
        in.close();
    }

    vector<int> find_this = Or_im(
        And_im(
            matrix.get_word("a"),
            matrix.get_word("b")),
        Not_im(
            matrix.get_word("a")));

    Info("Request result");
    for(int i=0;i<find_this.size();++i){
        if(find_this[i]){
            Info(files[i]);
        }
    }
    Info("Finished");
    Info("Runtime = "+std::to_string(EndTimer()));
}



int main_lab2(int argc, char *argv[]){
    test_invertindex(argc, argv);
    test_incendency_matrix(argc,argv);
}
