#include <iostream>
#include "choosingmode.h"
#include "streammode.h"
#include "pointermode.h"


using namespace std;


int main(int argc, char* argv[]) {

	switch (mode(argc, argv)) {

	case 0:
		cout << "check the command line options!" << endl;
		break;

	case 1:
	{
		char* filename = enter_pname();
		create_pfile(filename);

		cout << "\nEnter the name of the file with the results." << endl;
		char* result_filename = enter_pname();

		cout << "\n\nText in \"" << filename << "\":\n" << endl;
		print_pfile(filename);

		int sentences = 0;
		char* text = read_ptext(filename, sentences);
		text = delete_pbrackets(text);
		char** rows = split_psentences(text, sentences);
		edit_longest_pword(rows, sentences);
		add_data_to_pfile(result_filename, rows, sentences);

		cout << "\n\nText in \"" << result_filename << "\":\n" << endl;
		print_pfile(result_filename);

		break;
	}
	case 2:
	{
		string filename = enter_name();
		create_file(filename);

		cout << "\nEnter the name of the file with the results: ";
		string result_filename = enter_name();

		cout << "\n\nText in \"" << filename << "\":\n" << endl;
		print_file(filename);
		int sentences = 0;
		string text = read_text(filename, sentences);
		string* rows = split_sentences(text, sentences);
		delete_brackets(rows, sentences);
		edit_longest_word(rows, sentences);
		add_data_to_file(result_filename, rows, sentences);

		cout << "\n\nText in \"" << result_filename << "\":\n" << endl;
		print_file(result_filename);
		break;
	}
	}
}