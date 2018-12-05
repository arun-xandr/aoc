#include <iostream>
using namespace std;

int main() {

    string currentFrequency;
    long finalFrequency = 0;
    while(getline(cin, currentFrequency) && !currentFrequency.empty()) {
        finalFrequency += stoi(currentFrequency);
    }

    cout << "final frequency is " << finalFrequency;

    return EXIT_SUCCESS;
}
