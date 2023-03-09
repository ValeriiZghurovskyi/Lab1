#pragma once


char* enter_pname();
void create_pfile(char*);
void print_pfile(char*);
char* read_ptext(char*, int&);
char* delete_pbrackets(char*);
char** split_psentences(char*, int);
void edit_longest_pword(char**, int);
void add_data_to_pfile(char*, char**, int);
