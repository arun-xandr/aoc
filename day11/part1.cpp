//
// Created by Arun Shanmugam Kumar on 2018-12-15.
//

#include <iostream>
#include <sstream>
#include <stack>
#include <vector>
#include <map>
#include <set>

using namespace std;


int get_power_level(int x, int y, int grid_serial_number) {

    int power_level = 0;

    int rackId = x + 10;
    power_level += rackId * y;
    power_level += grid_serial_number;
    power_level = power_level * rackId;
    power_level = (power_level / 100) % 10;
    power_level -= 5;

    return power_level;
}

tuple<int, int, int> get_total_power(int x, int y, vector<vector<int>>& grid) {

    if ((x - 1 < 0) || (x + 1 >= 300) || (y - 1 < 0) || (y + 1 >= 300)) {
        return make_tuple(INT_MIN, -1, -1);
    }

    int total_power = 0;

    for(int i = -1; i <= 1; i++) {
        for(int j = -1; j <= 1; j++) {
            total_power += grid[x + i][y + j];
        }
    }

    return make_tuple(total_power, x - 1, y - 1);
}

int main() {

    int grid_serial_number = 9435;

    vector<vector<int>> grid(300);
    for(int x = 0; x < 300; x++) {
        grid[x] = vector<int>(300);
        for(int y = 0; y < 300; y++) {
            grid[x][y] = get_power_level(x, y, grid_serial_number);
        }
    }

    int max_total_power = INT_MIN;
    int top_x;
    int top_y;

    for(int x = 0; x < 300; x++) {
        for(int y = 0; y < 300; y++) {

            tuple<int, int, int> current_total_power = get_total_power(x, y, grid);

            if (get<0>(current_total_power) > max_total_power) {
                max_total_power = get<0>(current_total_power);
                top_x = get<1>(current_total_power);
                top_y = get<2>(current_total_power);
            }
        }
    }

    cout << "The max total power is " << max_total_power << ", top x = " << top_x << ", top y = " << top_y << endl;

    return EXIT_SUCCESS;
}