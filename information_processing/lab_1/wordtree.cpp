#include "wordtree.h"
#include "files.h"
#include "logger.h"



WordTreeNode::WordTreeNode(){
    memset(sons,0,sizeof(void*) * 27);
    final = false;
}

WordTreeNode::~WordTreeNode(){
    for(int i=0;i<27;++i){
        if(sons[i]){
            delete sons[i];
        }
    }
}

WordTree::WordTree(vector<string> files,bool inverse/* = false */){
    root = new WordTreeNode();
    for(auto filename: files){
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

                for(int i=0;i<splited.size();++i){
                    if(!inverse){
                        add_word(splited[i]);
                    }else{
                        add_suffix(splited[i]);
                    }
                }
            }
        }
        in.close();
    }
}

WordTree::~WordTree(){
    delete root;
}

void WordTree::add_word(string word){
    int i=0;
    WordTreeNode* cur = root;
    while(i < word.length() && cur->sons[get_letter_code(word[i])] != nullptr){
        cur = cur->sons[get_letter_code(word[i])];
        ++i;
    }
    for(; i < word.length() ;++i){
        WordTreeNode* node = new WordTreeNode();
        cur->sons[get_letter_code(word[i])] = node;
        cur = node;
    }

    cur->final = true;
}

void WordTree::add_suffix(string word){
    reverse(word.begin(),word.end());
    add_word(word);
}

vector<string> WordTree::get_all_words(WordTreeNode* node , string word){
    vector<string> res;
    cout << word << " " << node ->final << "\n";
    if(node->final){
        res.push_back(word);
    }
    for(int i=0;i<27;++i){
        if(node->sons[i]){
            word.push_back('a' + i);
            auto tmp = get_all_words(node->sons[i],word);
            res.insert(res.end(), tmp.begin(), tmp.end());
            word.pop_back();
        }
    }
    return res;
}

vector<string> WordTree::get_words(string word){
    int i=0;
    WordTreeNode* cur = root;
    while(i < word.length() && cur->sons[get_letter_code(word[i])] != nullptr){
        cur = cur->sons[get_letter_code(word[i++])];
    }
    if(i >= word.length()){
        return get_all_words(cur,word);
    }
    return vector<string>();
}


vector<string> WordTree::get_suffix(string word){
    reverse(word.begin(),word.end());
    auto tmp = get_words(word);
    for(auto &x:tmp){
        reverse(x.begin(),x.end());
    }
    return tmp;
}

