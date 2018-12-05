//
// Created by Arun Shanmugam Kumar on 2018-12-04.
//

#include <iostream>
#include <set>
#include <vector>

using namespace std;

int main() {

    vector<string> originalFrequencyChanges;
    string currentFrequency;

    long frequencySoFar = 0;
    set<long> uniqueFrequencies;

    while(getline(cin, currentFrequency) && !currentFrequency.empty()) {
        originalFrequencyChanges.push_back(currentFrequency);
    }

    int originalFrequencyChangesIndex = 0;
    int originalFrequencyChangesSize = originalFrequencyChanges.size();
    long skippedFirstFrequency = stoi(originalFrequencyChanges[0]);

    while(true) {
        frequencySoFar += stoi(originalFrequencyChanges[originalFrequencyChangesIndex]);
        if (uniqueFrequencies.find(frequencySoFar) != uniqueFrequencies.end() && frequencySoFar != skippedFirstFrequency) {
                break;
        }
        uniqueFrequencies.insert(frequencySoFar);
        originalFrequencyChangesIndex = (originalFrequencyChangesIndex + 1) % originalFrequencyChangesSize;
    }

    cout << "first frequency repeated twice is " << frequencySoFar;

    return EXIT_SUCCESS;
}
