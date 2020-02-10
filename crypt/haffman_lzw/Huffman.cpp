#include "Huffman.h"

map<Source,int> transform_to_counts(vector<Source> inp){
    map<Source,int> res;
    for(auto &x:inp){
        ++res[x];
    }
    return res;
}

class Node{
public:
    Node(int source = -1){
        this->source = source;
        left = right = 0;
    }
    Source source;
    Node *left;
    Node *right;
};

void delete_tree(Node *root){
    if(root->left){
        delete_tree(root->left);
    }
    if(root->right){
        delete_tree(root->right);
    }
    delete root;
}


map<Source, Code> dfs(Node* cur, int code, int depth){
    if(!cur->left){
        map<Source, Code> res;
        res[cur->source] = {code,depth};
        return res;
    }
    map<Source, Code> res1 = dfs(cur->left,code*2,depth+1);
    map<Source, Code> res2 = dfs(cur->right,code*2+1,depth+1);

    for(auto &x:res2){
        res1.insert(x);
    }
    return res1;
}

// tree construction
map<Source,Code> encode(map<Source,int> counts){
    set<pair<int,Node*>> tree;
    for(auto x:counts){
        tree.insert({x.second,new Node(x.first)});
    }
    while(tree.size() > 1){
        auto v1 = tree.begin();
        tree.erase(tree.begin());
        auto v2 = tree.begin();
        tree.erase(tree.begin());
        Node* node = new Node();
        node->left = v1->second;
        node->right = v2->second;
        tree.insert({v1->first + v2->first,node});
    }
    Node* root = tree.begin()->second;
    map<Source, Code > res = dfs(root,0,0);
    delete_tree(tree.begin()->second);
    return res;
}


vector<Source> decode(string s,map<Source,Code> codes){
    map<Code,Source> inv_codes;
    for(auto x:codes){
        inv_codes[x.second] = x.first;
    }
    vector<Source> res;
    string cur = "";
    for(int i=0;i<s.length();++i){
        cur.push_back(s[i]);
        Code val = str_to_code(cur);
        if(inv_codes.find(val) != inv_codes.end()){
            cur = "";
            res.push_back(inv_codes[val]);
        }
    }
    return res;
}

void Huffman(vector<Source> source, bool show_log){
    auto counts = transform_to_counts(source);
    auto codes = encode(counts);
    int coded_size = 0;
    string coded = "";

    for(auto x:codes){
        coded_size += counts[x.first]*x.second.second;
    }
    for(auto x:source){
        coded += code_to_str(codes[x]);
    }
    cout << "Huffman\n";
    cout << "Original size "  << sizeof (Source) * 8 * source.size() << " bites\n";
    cout << "Coded size    " << coded_size << "\n";

    auto decoded = decode(coded,codes);

    if(show_log){
        cout << "Counts\n";
        for(auto x:counts){
            cout << (int)x.first << ":" << x.second << "\t";
        }
        for(auto x: codes){
            cout << (int)x.first << "\t";print_bin(x.second.first,x.second.second);cout << "\n";
        }
        cout << std::endl;
        cout << "Coded = " << coded <<"\n";

        for(int i=0;i<decoded.size();++i){
            cout << (int)decoded[i] << "," << (int)source[i] << " ";
        }
    }
}
