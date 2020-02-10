#include "LZW.h"

int bin_str_to_int(string s){
    int res = 0;
    for(int i=0;i<s.length();++i){
        res = 2*res + s[i] - '0';
    }
    return res;
}

void LZW(vector<Source> source, bool show_log){
    // for small letters only
    auto source_as_str = convert_to_lowercase(source);
    int cur_len = 5;
    map<string,Code> codes;
    codes["#"] = {0,5};
    for(char i='a'; i<='z';++i){
        string str = "";
        str.push_back(char(i));
        codes[str] = {i-'a' + 1,5};
    }
    int cur_value = codes.size();

    cout << "Converted to str "  << source_as_str << "\n";

    string cur = "";
    vector<Code> coded;

    for(int i=0;i<source_as_str.length();++i){
        cur.push_back(source_as_str[i]);
        if(codes.find(cur) == codes.end()){
            codes[cur] = {cur_value++,cur_len};
            if(show_log){
                cout << cur << "\t" <<
                    code_to_str(codes[cur]) << "\t"<<
                    bin_str_to_int(code_to_str(codes[cur])) <<"\t" <<
                    code_to_str({codes[cur.substr(0,cur.length()-1)].first,cur_len})<< "\t"<<
                    bin_str_to_int(code_to_str({codes[cur.substr(0,cur.length()-1)].first,cur_len})) <<"\n";
            }

            coded.push_back({codes[cur.substr(0,cur.length()-1)].first,cur_len});
            cur = "";cur.push_back(source_as_str[i]);
            if(cur_value > (1 << cur_len)){
                ++cur_len;
            }
        }else{
            if(show_log){
                cout << cur << "\t" << code_to_str(codes[cur]) << "\t" <<
                    bin_str_to_int(code_to_str(codes[cur])) <<"\n";
            }
        }
    }
    coded.push_back({0,cur_len});

    if(show_log) {
        for(int i=0;i<coded.size();++i){
            cout << code_to_str(coded[i]) << "\n";
        }
    }

    int input_size = 5*source_as_str.length();
    int coded_size = 0;
    string coded_as_str = "";
    for(int i=0;i<coded.size();++i){
        coded_size +=coded[i].second;
        coded_as_str += code_to_str(coded[i]);
    }
    cout << "Input size = " << input_size << "\n";
    cout << "Coded size = " << coded_size << "\n";
    cout << coded_as_str << "\n";

    //decoding
    Source cur_char;
    string cur_code = "";
    string decoded;
    string prev_str = "";
    map<string,Code> new_codes;
    map<int,string> inv_codes;
    string cut;
    new_codes["#"] = {0,5};
    inv_codes[0] = "#";
    for(char i='a'; i<='z';++i){
        string str = "";
        str.push_back(char(i));
        new_codes[str] = {i-'a' + 1,5};
        inv_codes[{i-'a' + 1}] = str;
    }

    int new_cur_len = 5;
    int new_cur_value = new_codes.size();
    int pos = 0;
    while(pos < coded_as_str.length()){
        int i;
        cur_code = "";
        for(i=0;i <new_cur_len;++i){
            cur_code.push_back(coded_as_str[pos+i]);
        }
        Code code = str_to_code(cur_code);
        string from = inv_codes[code.first];
        print_bin(code.first,code.second);cout<<" ";
        prev_str += from.substr(0,1);
        if(pos>0){
            new_codes[prev_str] = {new_cur_value,new_cur_len};
            cout << " " << prev_str << " " <<from << " " << new_codes[prev_str].first << " " << new_cur_len << "\n";
            inv_codes[{new_cur_value}] = prev_str;
            ++new_cur_value;
            pos+=new_cur_len;
            if(new_cur_value >= (1 << new_cur_len)){
                ++new_cur_len;
            }
            prev_str = from;
        }
        else{
            pos+=new_cur_len;
        }
        decoded += from;
        //cout << from << " " << prev_str << "\n";
    }
    cout << "Decoded = " << decoded << "\n";
    cout << "Suorce  = " << source_as_str << "\n";

}
