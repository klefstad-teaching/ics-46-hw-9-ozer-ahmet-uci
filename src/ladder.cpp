#include <iostream>
#include <fstream>
#include <queue>
#include <set>
#include <map>
#include <vector>
#include <string>
#include <cmath>
#include "ladder.h"

using namespace std;

void error(string word1, string word2, string msg) {
    cerr << "Error: " << msg << " (" << word1 << " -> " << word2 << ")" << endl;
}

bool edit_distance_within(const string& str1, const string& str2, int d) {
    if (str1.length() != str2.length()) return false;
    int diff_count = 0;
    for (size_t i = 0; i < str1.length(); ++i) {
        if (str1[i] != str2[i]) {
            diff_count++;
            if (diff_count > d) return false;
        }
    }
    return diff_count == d;
}

bool is_adjacent(const string& word1, const string& word2) {
    return edit_distance_within(word1, word2, 1);
}

vector<string> generate_word_ladder(const string& begin_word, const string& end_word, const set<string>& word_list) {
    unordered_set<string> dict(word_list.begin(), word_list.end());
    if (!dict.count(end_word)) return {}; // End word must be in the dictionary

    queue<vector<string>> ladders;
    ladders.push({begin_word});
    unordered_set<string> visited;
    visited.insert(begin_word);

    while (!ladders.empty()) {
        int level_size = ladders.size();
        unordered_set<string> local_visited; // Track visited words at this BFS level

        for (int i = 0; i < level_size; ++i) {
            vector<string> ladder = ladders.front();
            ladders.pop();
            string current = ladder.back();

            if (current == end_word) return ladder;

            // Generate all possible one-letter variations of the current word
            for (int j = 0; j < current.size(); ++j) {
                char original = current[j];
                for (char c = 'a'; c <= 'z'; ++c) {
                    if (c == original) continue;
                    string neighbor = current;
                    neighbor[j] = c;

                    // Check if the generated neighbor is valid
                    if (dict.count(neighbor) && !visited.count(neighbor)) {
                        vector<string> new_ladder = ladder;
                        new_ladder.push_back(neighbor);
                        ladders.push(new_ladder);
                        local_visited.insert(neighbor);
                    }
                }
                current[j] = original; // Restore original character
            }
        }
        visited.insert(local_visited.begin(), local_visited.end()); // Update visited after processing the level
    }

    return {}; // No ladder found
}

void load_words(set<string>& word_list, const string& file_name) {
    ifstream file(file_name);
    if (!file) {
        cerr << "Error opening file: " << file_name << endl;
        return;
    }
    string word;
    while (file >> word) {
        word_list.insert(word);
    }
    file.close();
}

void print_word_ladder(const vector<string>& ladder) {
    if (ladder.empty()) {
        cout << "No word ladder found." << endl;
        return;
    }
    for (size_t i = 0; i < ladder.size(); ++i) {
        cout << ladder[i];
        if (i < ladder.size() - 1) cout << " -> ";
    }
    cout << endl;
}