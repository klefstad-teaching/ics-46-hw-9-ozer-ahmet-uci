#include <iostream>
#include <set>
#include <vector>
#include <string>
#include <algorithm>
#include "ladder.h"

using namespace std;

int main() {
    set<string> word_list;
    load_words(word_list, "../src/words.txt");
    
    string start_word, end_word;
    cout << "Enter start word: ";
    cin >> start_word;
    cout << "Enter end word: ";
    cin >> end_word;
    
    transform(start_word.begin(), start_word.end(), start_word.begin(), ::tolower);
    transform(end_word.begin(), end_word.end(), end_word.begin(), ::tolower);
    
    if (start_word == end_word) {
        cout << "Error: Start and end words must be different." << endl;
        return 1;
    }
    
    vector<string> ladder = generate_word_ladder(start_word, end_word, word_list);
    print_word_ladder(ladder);
    return 0;
}