#include "files.h"
#include<dirent.h>
#include<fstream>
#include<logger.h>

vector<string> get_files(const char *path) {
    struct dirent *entry;
    vector<string> res;
    DIR *dir = opendir(path);

    if (dir == NULL) {
        return res;
    }
    while ((entry = readdir(dir)) != NULL) {
        if(strlen(entry->d_name) >= 5){
            res.push_back(string(path) + entry->d_name);
        }
    }
    closedir(dir);
    return res;
}

vector<string> split(string inp){
    vector<string> res;
    int prev_pos = 0;
    inp = inp + " ";
    for(int i=0;i<inp.length();++i){
        if( !isalpha(inp[i])){
            if(prev_pos < i){
                string data = inp.substr(prev_pos,i-prev_pos);
                std::transform(data.begin(), data.end(), data.begin(),
                               [](unsigned char c){ return std::tolower(c); });
                res.push_back(data);
            }
            prev_pos = i+1;
        }
    }
    return res;
}

vector<pair<string,int>> split_with_position(string inp){
    vector<pair<string,int>> res;
    int prev_pos = 0;
    inp = inp + " ";
    for(int i=0;i<inp.length();++i){
        if( !isalpha(inp[i])){
            if(prev_pos < i){
                string data = inp.substr(prev_pos,i-prev_pos);
                std::transform(data.begin(), data.end(), data.begin(),
                               [](unsigned char c){ return std::tolower(c); });
                res.push_back(make_pair(data,prev_pos));
            }
            prev_pos = i+1;
        }
    }
    return res;
}

void read_file(Vocabulary* voc, string filename, int& filesize, int &words_count){
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
            words_count += splited.size();
            filesize += strlen(str);
            for(auto &str:splited){
                voc->add_word(str);
            }
        }
        // cout << ("Voc size ater adding line = " + to_string(voc->get_words_count())) << endl;
    }
    in.close();
}

string get_filename(string path){
    int pos = path.size() - 1;
    while(pos>=0 && path[pos] != '/' && path[pos] != '\\'){
        --pos;
    }
    ++pos;
    return path.substr(pos,path.size() - pos);
}
