//
// Created by Arun Shanmugam Kumar on 2018-12-04.
//

#include <iostream>
#include <set>
#include <map>

using namespace std;

int main() {

    set<string> boxIdsWithTwoRepeats;
    set<string> boxIdsWithThreeRepeats;

    string currentBoxId;
    map<char, int> currentBoxIdMap;
    while(getline(cin, currentBoxId) && !currentBoxId.empty()) {

        currentBoxIdMap.clear();
        for(const char &c : currentBoxId) {
            currentBoxIdMap[c]++;
        }

        auto it = currentBoxIdMap.begin();
        while(it != currentBoxIdMap.end()) {
            if (it->second == 2) {
                boxIdsWithTwoRepeats.insert(currentBoxId);
            } else if (it ->second == 3) {
                boxIdsWithThreeRepeats.insert(currentBoxId);
            }
            it++;
        }
    }

    cout << "checksum is " << boxIdsWithTwoRepeats.size() * boxIdsWithThreeRepeats.size() << endl;

    return EXIT_SUCCESS;
}
