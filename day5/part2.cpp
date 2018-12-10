//
// Created by Arun Shanmugam Kumar on 12/9/18.
//

#include <iostream>
#include <stack>

using namespace std;

int get_polymer_size(string polymer, char skip_character) {

    int total_polymer_units = polymer.size();

    stack<char> reacted_polymer;

    for(auto i = 0; i < total_polymer_units; i++) {

        if (tolower(polymer[i]) == tolower(skip_character)) {
            continue;
        }

        if (reacted_polymer.size() == 0) {
            reacted_polymer.push(polymer[i]);
        } else {

            char top_unit = reacted_polymer.top();
            char current_unit = polymer[i];

            if (top_unit != current_unit && tolower(top_unit) == tolower(current_unit)) {
                reacted_polymer.pop();
            } else {
                reacted_polymer.push(current_unit);
            }
        }
    }

    return reacted_polymer.size();
}

int main() {

    string polymer;

    while(getline(cin, polymer) && !polymer.empty()) {

        int minimum_polymer_size = INT_MAX;

        for(int i = 0; i < 26; i++) {
            minimum_polymer_size = min(minimum_polymer_size, get_polymer_size(polymer, char('A' + i)));
        }

        cout << "Shortest Polymer units length is " << minimum_polymer_size << endl;
    }

    return EXIT_SUCCESS;
}


