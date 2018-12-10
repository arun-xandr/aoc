//
// Created by Arun Shanmugam Kumar on 12/9/18.
//

#include <iostream>
#include <stack>

using namespace std;

int main() {

    string polymer;

    while(getline(cin, polymer) && !polymer.empty()) {

        int total_polymer_units = polymer.size();

        stack<char> reacted_polymer;

        for(auto i = 0; i < total_polymer_units; i++) {

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

        cout << "Polymer units remaining is " << reacted_polymer.size() << endl;
    }


    return EXIT_SUCCESS;
}
