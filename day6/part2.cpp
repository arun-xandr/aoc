//
// Created by Arun Shanmugam Kumar on 12/9/18.
//

#include <iostream>
#include <stack>
#include <sstream>
#include <vector>
#include <map>

using namespace std;

int main() {

    string current_coordinate;
    vector<pair<int, int>> coordinates;

    int min_x = INT_MAX;
    int max_x = INT_MIN;
    int min_y = INT_MAX;
    int max_y = INT_MIN;

    int total_size_of_region = 0;

    while(getline(cin, current_coordinate) && !current_coordinate.empty()) {

        stringstream ss(current_coordinate);

        int x, y;
        char ignore;

        ss >> x >> ignore >> y;

        if (x < min_x) {
            min_x = x;
        } else if (x > max_x) {
            max_x = x;
        }

        if (y < min_y) {
            min_y = y;
        } else if (y > max_y) {
            max_y = y;
        }

        coordinates.push_back(make_pair(x, y));
    }

    for(int i = min_x; i <= max_x; i++) {
        for(int j = min_y; j <= max_y; j++) {

            int total_distance = 0;

            for(vector<pair<int, int>>::iterator it = coordinates.begin();
                it != coordinates.end(); ++it) {

                pair<int, int> current_coordinate = *it;
                int current_coordinate_x = get<0>(current_coordinate);
                int current_coordinate_y = get<1>(current_coordinate);

                int distance = abs(current_coordinate_x - i) + abs(current_coordinate_y - j);

                total_distance += distance;
            }

            if (total_distance < 10000) {
                ++total_size_of_region;
            }
        }
    }

    cout << "The size of the region is " << total_size_of_region << endl;

    return EXIT_SUCCESS;
}


