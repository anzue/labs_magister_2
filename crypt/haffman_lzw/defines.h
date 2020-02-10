#ifndef DEFINES_H
#define DEFINES_H

#include <iostream>
#include <vector>
#include <set>
#include <map>
#include <iomanip>
#include <bitset>

using namespace std;


typedef unsigned char Source;
typedef pair<int,int> Code; //code and size;

const int maxVal = 256;

string code_to_str(Code code);
Code str_to_code(string str);
string convert_to_lowercase(vector<Source> s);
void print_bin(int a,int count);

#endif // DEFINES_H
