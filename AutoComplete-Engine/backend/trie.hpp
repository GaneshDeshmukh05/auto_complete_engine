#ifndef TRIE_HPP
#define TRIE_HPP

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

struct TrieNode {
    TrieNode* children[26];
    bool isEnd;
    int freq;
    int wordIndex;

    TrieNode() {
        isEnd = false;
        freq = 0;
        wordIndex = -1;
        for (int i = 0; i < 26; i++)
            children[i] = NULL;
    }
};

class Trie {
private:
    TrieNode* root;
    vector<string>* words;

    void dfs(TrieNode* node, vector<pair<int,int>>& results) {
        if (!node) return;

        if (node->isEnd) {
            results.push_back({node->freq, node->wordIndex});
        }

        for (int i = 0; i < 26; i++) {
            dfs(node->children[i], results);
        }
    }

public:
    Trie(vector<string>* w) {
        root = new TrieNode();
        words = w;
    }

    void insert(string word, int freq, int index) {
        TrieNode* node = root;

        for (char ch : word) {
            if (ch < 'a' || ch > 'z') continue;

            int i = ch - 'a';

            if (!node->children[i])
                node->children[i] = new TrieNode();

            node = node->children[i];
        }

        node->isEnd = true;
        node->freq = freq;
        node->wordIndex = index;
    }

    vector<string> getSuggestions(string prefix, int k) {
        TrieNode* node = root;

        for (char ch : prefix) {
            if (ch < 'a' || ch > 'z') continue;

            int i = ch - 'a';
            if (!node->children[i]) return {};
            node = node->children[i];
        }

        vector<pair<int,int>> results;
        dfs(node, results);

        // sort by frequency descending
        sort(results.begin(), results.end(), greater<>());

        vector<string> output;
        for (int i = 0; i < min(k, (int)results.size()); i++) {
            output.push_back((*words)[results[i].second]);
        }

        return output;
    }
};

#endif