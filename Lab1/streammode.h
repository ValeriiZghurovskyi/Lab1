#pragma once
#include <iostream>
#include <string>
using namespace std;


string enter_name();
void create_file(string);
void print_file(string);
string read_text(string, int&);
string* split_sentences(string, int);
void delete_brackets(string*, int);
void edit_longest_word(string*, int);
void add_data_to_file(string, string*, int);