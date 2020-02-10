#ifndef HUFFMAN_H
#define HUFFMAN_H

#include "defines.h"



#include "defines.h"


// tree construction
map<Source,Code> encode(map<Source,int> counts);
vector<Source> decode(string s,map<Source,Code> codes);
void Huffman(vector<Source> source, bool show_log = false);

#endif // HUFFMAN_H
