#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>

using namespace std;

char* enter_pname() {
	char* filename = new char[100];
	cout << "Enter file name(if file doesn`t exist it will be created): ";
	cin.getline(filename, 100);
	return filename;
}

void create_pfile(char* filename) {

	FILE* file = fopen(filename, "a");

	cout << "Enter text to add in file(to stop enter \"stop\" on new line ):\n";

	char* temp = new char[256];

	while (true) {
		cin.getline(temp, 255);
		if (strcmp(temp, "stop") == 0) {
			break;
		}
		fprintf(file, "%s\n", temp);
	}

	delete[] temp;
	fclose(file);
}


void print_pfile(char* filename) {
	FILE* file = fopen(filename, "r");

	char temp;
	while ((temp = fgetc(file)) != EOF) {
		cout << temp;
	}
	fclose(file);
}

char* read_ptext(char* filename, int& sentences) {
	FILE* file = fopen(filename, "r");
	char* text = new char[65536];

	char temp;
	int i = 0;

	while ((temp = fgetc(file)) != EOF) {
		if (temp == '\n') {
			temp = ' ';
		}
		text[i] = temp;
		if (temp == '.') {
			sentences++;
		}
		i++;
	}
	fclose(file);
	return text;
}

char* delete_pbrackets(char* text) {

	char* new_text = new char[65536];
	int count = 0;
	int j = 0;

	for (int i = 0; i < strlen(text); i++) {
		if (text[i] == '(') {
			count++;
		}
		else if (text[i] == ')') {
			count--;
		}
		else if (count == 0) {
			new_text[j] = text[i];
			j++;
		}
	}

	new_text[j] = '\0';

	return new_text;
}

char** split_psentences(char* text, int rows) {
	char** sentences = new char* [rows];

	for (int i = 0; i < rows; i++) {
		sentences[i] = new char[1024];
	}

	char* token = strtok(text, ".");

	for (int i = 0; i < rows; i++) {
		if (i == 0) {
			strcpy(sentences[i], token);
		}
		else {
			strcpy(sentences[i], token + 1);
		}
		token = strtok(NULL, ".");
	}
	delete[] text;
	return sentences;
}


void edit_longest_pword(char** sentences, int rows) {
	for (int i = 0; i < rows; i++) {
		int j = 1, longest_word_len = 0, longest_word_pos = 0, word_start = 0;
		int sentence_len = strlen(sentences[i]);

		while (j <= sentence_len) {
			if (sentences[i][j-1] != ' ' && sentences[i][j-1] != '.' && sentences[i][j-1] != ',' && (sentences[i][j] == ' ' || sentences[i][j] == '.' || sentences[i][j] == ',' || sentences[i][j] == '\0')) {
				int word_len = j - word_start;
				if (word_len > longest_word_len) {
					longest_word_len = word_len;
					longest_word_pos = word_start;
				}
				word_start = j + 1;
				
			}
			j++;
		}
		char temp;
		int n = 0;
		for (int k = longest_word_pos; k < (longest_word_pos + longest_word_len) / 2; k++) {
			temp = sentences[i][k];
			sentences[i][k] = sentences[i][longest_word_pos + longest_word_len - n - 1];
			sentences[i][longest_word_pos + longest_word_len - n - 1] = temp;
			n++;
		}
	}
}


void add_data_to_pfile(char* filename, char** sentences, int rows) {
	FILE* file = fopen(filename, "a");

	for (int i = 0; i < rows; i++) {
		fprintf(file, "%s.\n", sentences[i]);
	}

	fclose(file);
}
