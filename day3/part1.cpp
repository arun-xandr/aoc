//
// Created by Arun Shanmugam Kumar on 2018-12-05.
//

#include <iostream>
#include <vector>
#include <sstream>

using namespace std;

int main() {

    int overlapping_claims = 0;
    int fabric[1001][1001] = { {0} };

    string currentClaim;
    while(getline(cin, currentClaim) && !currentClaim.empty()) {

        stringstream ss(currentClaim);

        string ignore;
        string x_y;
        string width_height;
        ss >> ignore >> ignore >> x_y >> width_height;

        int left = stoi(x_y.substr(0, x_y.find(",")));
        int top = stoi(x_y.substr(x_y.find(",")+1, x_y.size() - 1));
        int width = stoi(width_height.substr(0, width_height.find("x")));
        int height = stoi(width_height.substr(width_height.find("x") + 1, width_height.size()));

        for(int x = left; x < left + width; x++) {
            for (int y = top; y < top + height; y++) {
                fabric[x][y]++;
            }
        }
    }

    for(int x = 0; x < 1001; x++) {
        for(int y = 0; y < 1001; y++) {
            if(fabric[x][y] > 1) {
                ++overlapping_claims;
            }
        }
    }

    cout << "number of square inches within two or more claims is " << overlapping_claims << endl;

    return EXIT_SUCCESS;
}