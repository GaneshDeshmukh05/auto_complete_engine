#include <iostream>
#include <fstream>
#include <vector>
#include <string>

#include "trie.hpp"

using namespace std;

int main(int argc, char* argv[]) {

    cout << "[DEBUG] Program started\n";

    vector<string> words;
    vector<int> freqs;

    string path = "D:\\AutoComplete-Engine\\backend\\dictionary.txt";    
    
    cout << "[DEBUG] Opening file: " << path << endl;

    ifstream file(path);

    if (!file) {
        cout << "[ERROR] File NOT FOUND!\n";
        return 0;
    }

    string word;
    int freq;
    int count = 0;

    while (file >> word >> freq) {
        words.push_back(word);
        freqs.push_back(freq);
        count++;
    }

    file.close();

    cout << "[DEBUG] Words loaded: " << count << endl;

    // ✅ FIX: pass words vector to Trie
    Trie trie(&words);

    for (int i = 0; i < words.size(); i++) {
        trie.insert(words[i], freqs[i], i); // ✅ correct call
    }

    string input;

    if (argc > 1) {
        input = argv[1];
        cout << "[DEBUG] Input from API: " << input << endl;
    } else {
        cout << "Enter prefix: ";
        cin >> input;
    }

    vector<string> result = trie.getSuggestions(input, 5); // ✅ needs k

    cout << "[DEBUG] Suggestions:\n";

    for (auto &w : result) {
        cout << w << endl;
    }

    cout << "[DEBUG] Program finished\n";

    return 0;
}