//
// Created by Arun Shanmugam Kumar on 2018-12-04.
//

#include <iostream>
#include <vector>
#include <map>

using namespace std;

int main() {

    vector<string> boxIds;
    string currentBoxId;
    map<char, int> currentBoxIdMap;
    while(getline(cin, currentBoxId) && !currentBoxId.empty()) {
        boxIds.push_back(currentBoxId);
    }

    sort(boxIds.begin(), boxIds.end());

    string output_letters("");
    for (auto i = 0; i != boxIds.size(); i++) {

        string first = boxIds[i];
        string second;

        if ((i + 1) < boxIds.size()) {
            second = boxIds[i + 1];

            int len = first.length();
            int number_of_mismatch = 0;
            for(auto j = 0; j < len; j++) {
                if (first.at(j) == second.at(j)) {
                    output_letters += first.at(j);
                } else {
                    ++number_of_mismatch;
                }
            }

            if (number_of_mismatch == 1) {
                break;
            } else {
                output_letters = "";
            }
        }
    }

    cout << "common letters between two correct box IDs = " << output_letters << endl;

    return EXIT_SUCCESS;
}
