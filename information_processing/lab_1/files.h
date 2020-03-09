#ifndef FILES_H
#define FILES_H

#include<vector>
#include<string>
using namespace std;

#include<vocabulary.h>

vector<string> get_files(const char *path);
vector<string> split(string inp);
vector<pair<string,int>> split_with_position(string str);
void read_file(Vocabulary* voc, string filename, int& filesize, int &words_count);
string get_filename(string path);
int get_letter_code(char a);
char get_code_letter(int a);
#endif // FILES_H
