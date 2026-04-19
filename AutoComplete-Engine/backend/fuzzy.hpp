#ifndef FUZZY_HPP
#define FUZZY_HPP

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

// Edit Distance (Levenshtein)
int editDistance(string a, string b) {
    int n = a.size(), m = b.size();
    vector<vector<int>> dp(n+1, vector<int>(m+1));

    for (int i = 0; i <= n; i++) dp[i][0] = i;
    for (int j = 0; j <= m; j++) dp[0][j] = j;

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            int cost = (a[i-1] == b[j-1]) ? 0 : 1;

            dp[i][j] = min({
                dp[i-1][j] + 1,
                dp[i][j-1] + 1,
                dp[i-1][j-1] + cost
            });
        }
    }
    return dp[n][m];
}

// Fuzzy search
vector<string> fuzzySearch(string input, vector<string>& words) {
    vector<pair<int,string>> matches;

    for (auto &w : words) {
        int dist = editDistance(input, w);
        if (dist <= 2) {
            matches.push_back({dist, w});
        }
    }

    sort(matches.begin(), matches.end());

    vector<string> result;
    for (int i = 0; i < min(5, (int)matches.size()); i++) {
        result.push_back(matches[i].second);
    }

    return result;
}

#endif