#include "defines.h"

string code_to_str(Code code){
    string res = "";
    while(code.second-- > 0 || code.first > 0){
        res.insert(res.begin(),1,'0' + code.first%2);
        code.first/=2;
    }
    return res;
}

Code str_to_code(string str){
    int res = 0;
    for(auto x:str){
        res = res*2 + x - '0';
    }
    return make_pair(res,str.length());
}

string convert_to_lowercase(vector<Source> s){
    string res = "";
    for(int i=0;i<s.size();++i){
        if(s[i] <= 'z' && s[i] >= 'a'){
            res.push_back(s[i]);
        }
        if(s[i] <= 'Z' && s[i] >= 'A'){
            res.push_back(s[i] - 'A' + 'a');
        }
    }
    res.push_back('#');
    return res;
}

void print_bin(int a,int count){
    for(int i=count - 1; i>=0;--i){
        cout << ((a&(1 << i)) >> i);
    }
}
