#include <iostream>
#include <fstream>
#include <unordered_map>
#include <vector>
#include <algorithm>

using namespace std;

string clean_word(string word) {
	string clean_word = "";
	for (int i = 0; i < word.length(); i++) {
		if (isalpha(word.at(i))) {
			if (word.at(i) > 65 && word.at(i) < 90) {
				clean_word += word.at(i) | 0x20;
			}
			else {
				clean_word += word.at(i);
			}
		}
	}
	return clean_word;
}

bool sort_by_count(const pair<string, int>& p1, const pair<string, int>& p2) {
	return p1.second > p2.second;
}

void parse_file(string file_name, int max_n_out, int min_word_len, int max_word_len) {
	ifstream file;
	file.open(file_name);
	unordered_map<string, int> tally;
	string word;
	while (file >> word) {
		word = clean_word(word);
		if (word.length() >= min_word_len && word.length() <= max_word_len) {
			unordered_map<string, int>::iterator iterator = tally.find(word);
			if (iterator == tally.end()) {
				tally.insert(make_pair(word, 1));
			}
			else {
				tally.at(word)++;
			}
		}
	}
	file.close();
	vector<pair<string, int>> tally_v;
	unordered_map<string, int>::iterator iterator = tally.begin();
	while (iterator != tally.end()) {
		tally_v.push_back(make_pair(iterator->first, iterator->second));
		iterator++;
	}
	sort(tally_v.begin(), tally_v.end(), sort_by_count);
	for (int i = 0; i < max_n_out && i < tally.size(); i++) {
		cout << tally_v[i].first << ": " << tally_v[i].second << endl;
	}
}

bool isInteger(string s) {
	for (int i = 0; i < s.length(); i++) {
		if ((int)s.at(i) < 48 || (int)s.at(i) > 57)
			return false;
	}
	return true;
}

int main(int argc, char* argv[]) {
	if (argc < 5) {
		cout << "usage: wordcounts.exe MAX_N_OUT MIN_WORD_LEN MAX_WORD_LEN FILE..." << endl;
		return 0;
	}
	for (int i = 1; i < 4; i++) {
		if (!isInteger(argv[i])) {
			switch (i) {
			case 1:
				cout << "bad integer value '" << argv[i] << "' for MAX_N_OUT" << endl;
				return 0;
			case 2:
				cout << "bad integer value '" << argv[i] << "' for MIN_WORD_LEN" << endl;
				return 0;
			case 3:
				cout << "bad integer value '" << argv[i] << "' for MAX_WORD_LEN" << endl;
				return 0;
			default:
				return 0;
			}
		}
	}
	if (atoi(argv[2]) > atoi(argv[3])) {
		cout << "MIN_WORD_LEN " << atoi(argv[2]) << " is greater than MAX_WORD_LEN " << atoi(argv[3]) << endl;
		return 0;
	}
	for (int i = 4; i < argc; i++) {
		ifstream file_test;
		file_test.open(argv[i]);
		if (file_test.good() != 1) {
			cout << "cannot read " << argv[i] << ": No such file or directory" << endl;
			return 0;
		}
		file_test.close();
		parse_file(argv[i], atoi(argv[1]), atoi(argv[2]), atoi(argv[3]));
	}
}
