#include "LZW.h"
#include "Huffman.h"

using namespace std;


vector<Source> generate_values(int count){
    vector<Source> res;
    for(int i=0;i<count;++i){
        res.push_back(rand()%256);
    }
    return res;
}

vector<Source> generate_from_string(){
    string text = "Text messaging, or texting, is the act of composing and sending electronic messages, typically consisting of alphabetic and numeric characters, between two or more users of mobile devices, desktops/laptops, or other type of compatible computer. Text messages may be sent over a cellular network, or may also be sent via an Internet connection.";
   // string text = "TOBEORNOTTOBEORTOBEORNOT";
    vector<Source> res;
    for(int i=0;i<text.size();++i){
        res.push_back(text[i]);
    }
    return res;
}


int main_h()
{
   // auto source = generate_values(10000);
    auto source = generate_from_string();
    //Huffman(source,true);

    LZW(source,true);

    return 0;
}


int main(){
    main_h();
}
