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

    int min_x = INT_MAX;
    int max_x = INT_MIN;
    int min_y = INT_MAX;
    int max_y = INT_MIN;

    vector<pair<int, int>> coordinates;

    int max_area = INT_MIN;
    string max_coordinate;
    map<string, int> coordinates_area_map;

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

    int max_dimension = max(max_x, max_y);

    cout << min_x << " " << max_x << " " << min_y << " " << max_y <<  " " << max_dimension <<  endl;

    for(int i = min_x; i <= max_x; i++) {
        for(int j = min_y; j <= max_y; j++) {

            int current_x = i;
            int current_y = j;
            int min_distance = INT_MAX;
            map<int, vector<pair<int, int>>> min_coordinate_map;
            bool ignore_coordinate = false;

            for(vector<pair<int, int>>::iterator it = coordinates.begin();
                it != coordinates.end(); ++it) {

                pair<int, int> current_coordinate = *it;
                int current_coordinate_x = get<0>(current_coordinate);
                int current_coordinate_y = get<1>(current_coordinate);

                int distance = abs(current_coordinate_x - current_x) + abs(current_coordinate_y - current_y);

                if (distance <= min_distance) {
                    min_distance = distance;
                    min_coordinate_map[min_distance].push_back(current_coordinate);
                }
            }


            if(min_coordinate_map[min_distance].size() == 1) {

                pair<int, int> min_coordinate = min_coordinate_map[min_distance][0];

                /*cout << " The minimum distance is " << min_distance << " between " << current_x << " " << current_y <<
                " and " << get<0>(min_coordinate) << "_" << get<1>(min_coordinate) << endl;*/
                string k = to_string(get<0>(min_coordinate)) + "_" + to_string(get<1>(min_coordinate));

                if (coordinates_area_map.find(k) == coordinates_area_map.end() || coordinates_area_map[k] == INT_MIN) {
                   /* cout << " starting a new coordinate " << k << endl;*/
                    coordinates_area_map[k] = 0;
                }

                if(!(get<0>(min_coordinate) == min_x || get<0>(min_coordinate) >= max_x ||
                get<1>(min_coordinate) == min_y || get<1>(min_coordinate) >= max_y)) {

                    /*cout << " coordinate is  " << k << endl;*/
                    coordinates_area_map[k]++;

                } else {
                    coordinates_area_map[k] = INT_MIN;
                }
            }

            min_coordinate_map.clear();
        }
    }

    auto it = coordinates_area_map.begin();
    while(it != coordinates_area_map.end()) {
        cout << " coordinates " << it->first << " area is " << it->second << endl;

        if (max_area < it->second) {
            max_area = it->second;
            max_coordinate = it->first;
        }
        it++;
    }


    cout << "The size of the largest area is " << max_area << "  for coordinate " << max_coordinate << endl;


    return EXIT_SUCCESS;
}


