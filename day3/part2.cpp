//
// Created by Arun Shanmugam Kumar on 2018-12-05.
//

#include <iostream>
#include <vector>
#include <sstream>
#include <map>
#include <set>

using namespace std;

int main() {

    int fabric[1001][1001] = { {0} };
    map<string, string> cellToClaimIdMap;
    set<string> uniqueClaimIds;

    string currentClaim;
    while(getline(cin, currentClaim) && !currentClaim.empty()) {

        stringstream ss(currentClaim);

        string ignore;
        string claimId;
        string x_y;
        string width_height;

        ss >> claimId >> ignore >> x_y >> width_height;

        int left = stoi(x_y.substr(0, x_y.find(",")));
        int top = stoi(x_y.substr(x_y.find(",")+1, x_y.size() - 1));
        int width = stoi(width_height.substr(0, width_height.find("x")));
        int height = stoi(width_height.substr(width_height.find("x") + 1, width_height.size()));

        uniqueClaimIds.insert(claimId);

        for(int x = left; x < left + width; x++) {
            for (int y = top; y < top + height; y++) {
                fabric[x][y]++;
                string cell_index = to_string(x)+"_"+to_string(y);
                if (cellToClaimIdMap.find(cell_index) !=  cellToClaimIdMap.end()) {
                    uniqueClaimIds.erase(cellToClaimIdMap[cell_index]);
                    uniqueClaimIds.erase(claimId);
                }
                cellToClaimIdMap[cell_index] = claimId;
            }
        }
    }

    assert(uniqueClaimIds.size() == 1);

    cout << "ID of the only claim that doesn't overlap is " << *uniqueClaimIds.begin() << endl;

    return EXIT_SUCCESS;
}
