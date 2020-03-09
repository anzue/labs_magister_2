#ifndef WORDTREE_H
#define WORDTREE_H

#include<string>
#include<algorithm>
#include<cstdio>
#include<vector>
#include <bits/stdc++.h>

using namespace std;


class WordTreeNode{
public:
    bool final = false;
    WordTreeNode *sons[27];
    WordTreeNode();
    ~WordTreeNode();
};

class WordTree
{
    WordTreeNode* root;
public:
    WordTree(vector<string> files,bool inverse = false);
    ~WordTree();

    void add_word(string word);
    void add_suffix(string word);

    vector<string> get_all_words(WordTreeNode* node , string word);
    vector<string> get_words(string word);
    vector<string> get_suffix(string word);
};


#endif // WORDTREE_H
