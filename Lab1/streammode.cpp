#include <iostream>
#include <string>
#include <fstream>
#include <algorithm>

using namespace std;


string enter_name() {

	string name;
	cout << "Enter file name(if file doesn`t exist it will be created): ";
	getline(cin, name);
	return name;
}

void print_file(string filename) {
	ifstream fin;
	fin.open(filename);
	if (!fin.is_open()) {
		cout << "Error. Cant open file!" << endl;
	}
	else {
		string str;

		while (!fin.eof()){
			str = "";
			getline(fin, str);
			cout << str << endl;
		}
	}
	fin.close();
}


void create_file(string filename) {
	ofstream fout;
	fout.open(filename, ios::app);

	if (!fout.is_open()) {
		cout << "Error. Cant open file!" << endl;
	}
	else {
		cout << "Enter text to add in file(to stop enter \"stop\" on new line ):\n";

		while (true) {
			string temp;
			getline(cin, temp);
			if (temp == "stop") {
				break;
			}
			fout << temp << endl;
		}
		fout.close();
	}
}


string read_text(string filename, int& rows) {

	ifstream fin;
	fin.open(filename);
	string text = "";

	if (!fin.is_open()) {
		cout << "Error. Cant open file!" << endl;
	} else{
		char ch;
		while (fin.get(ch)) {
			if (ch == '\n') {
				ch = ' ';
			}
			if (ch == '.') {
				rows++;
			}
			text += ch;
		}
		if (ch != '.') {
			rows++;
		}
	}
	fin.close();
	return text;
}

string* split_sentences(string text, int rows) {
	string* sentences = new string[rows + 1];
	string sentence;
	int n = 0;

	for (int i = 0; i < text.length(); i++) {
		sentence += text[i];

		if (i < text.length() - 1 && text[i] == '.' && text[i + 1] == ' ') {
			sentences[n] = sentence;
			n++;
			i++;
			sentence = "";
		}
	}
	if (sentence != "") {
		sentences[n] = sentence;
	}
	return sentences;
}

void delete_brackets(string* sentences, int rows) {
	
	for (int i = 0; i < rows; i++) {
		int start_pos = 0;
		int end_pos = 0;
		start_pos = sentences[i].find('(');
		while (start_pos != string::npos) {
			end_pos = sentences[i].find(')');
			if (end_pos < sentences->length() && sentences[i][start_pos - 1] == ' ' && sentences[i][end_pos + 1] == ' ') {
				sentences[i].erase(end_pos, 1);
				sentences[i].erase(start_pos, (end_pos - start_pos + 1));
			}
			else {
				sentences[i].erase(start_pos, (end_pos - start_pos + 1));
			}
			
			start_pos = sentences[i].find('(');
		}	
	}
}

string find_longest_word(string row) {
	string current_word = "";
	string longest_word = "";
	for (int i = 0; i < row.length(); i++) {
		if (row[i] == ' ' || row[i] == ',' || row[i] == '.') {
			if (current_word.length() > longest_word.length()) {
				longest_word = current_word;
			}
			current_word = "";
		}
		else {
			current_word += row[i];
		}
	}
	if (current_word.length() > longest_word.length()) {
		longest_word = current_word;
	}
	return longest_word;
}

void edit_longest_word(string* sentences, int rows) {
	for (int i = 0; i < rows; i++) {
		string longest_word = find_longest_word(sentences[i]);

		int pos = sentences[i].find(longest_word, 0);

		reverse(longest_word.begin(), longest_word.end());		//Не знаю чи можна використовувати цю функцію, тому нижче є варіант без неї

		/*int length = longest_word.length();					
		char temp;												
		for (int i = 0; i < length / 2; i++) {
			temp = longest_word[i];
			longest_word[i] = longest_word[length - i - 1];
			longest_word[length - i - 1] = temp;
		}*/

		sentences[i].replace(pos, longest_word.length(), longest_word);

	}
}


void add_data_to_file(string filename, string* sentence, int rows) {
	ofstream fout;
	fout.open(filename);

	if (fout.is_open()) {
		for (int i = 0; i < rows; i++) {
			fout << sentence[i] << endl;
		}
		fout.close();
	}
	else {
		cout << "Error. Cant open/create file!" << endl;
	}
	fout.close();
}
