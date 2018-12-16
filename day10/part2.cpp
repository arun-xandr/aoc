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

tuple<bool, int, int, int> calculate_new_position(int current_time,
                                                  int prev_min_y, int prev_max_y,
                                                  int min_total_rows,
                                                  vector<tuple<int, int, int, int>>& rows) {

    int number_of_repeating_rows = 0;
    set<int> unique_x_rows;
    int min_x = INT_MAX, max_x = INT_MIN;
    int min_y = INT_MAX, max_y = INT_MIN;


    for(auto itr = rows.begin(); itr != rows.end(); itr++) {

        auto current_tuple = *itr;
        auto new_position_x = get<0>(current_tuple) + get<2>(current_tuple);
        auto new_position_y = get<1>(current_tuple) + get<3>(current_tuple);

        min_x = min(new_position_x, min_x);
        max_x = max(new_position_x, max_x);

        min_y = min(new_position_y, min_y);
        max_y = max(new_position_y, max_y);

        unique_x_rows.insert(new_position_x);
    }

    bool exit_condition_met = false;
    bool min_unique_x_rows_found = false;
    int new_min_total_rows = min_total_rows;

    if(min_total_rows < static_cast<int>(unique_x_rows.size())) {
        min_unique_x_rows_found = true;
    } else {
        new_min_total_rows = static_cast<int>(unique_x_rows.size());
    }

    if(min_unique_x_rows_found && ((max_y - min_y) > (prev_max_y - prev_min_y))) {
        exit_condition_met = true;
    }

    if (!exit_condition_met) {

        for(auto itr = rows.begin(); itr != rows.end(); itr++) {

            auto current_tuple = *itr;
            auto new_position_x = get<0>(current_tuple) + get<2>(current_tuple);
            auto new_position_y = get<1>(current_tuple) + get<3>(current_tuple);

            *itr = make_tuple(new_position_x, new_position_y, get<2>(current_tuple), get<3>(current_tuple));
        }
    }

    return make_tuple(exit_condition_met, min_y, max_y, new_min_total_rows);
}

void print_current_message(vector<tuple<int, int, int, int>>& rows) {

    map<int, set<int>> matrix;
    int min_x = INT_MAX, max_x = INT_MIN;
    int min_y = INT_MAX, max_y = INT_MIN;

    for(auto itr = rows.begin(); itr != rows.end(); itr++) {

        auto current_tuple = *itr;
        auto x = get<0>(current_tuple);
        auto y = get<1>(current_tuple);

        min_x = min(x, min_x);
        max_x = max(x, max_x);

        min_y = min(y, min_y);
        max_y = max(y, max_y);

        matrix[x].insert(y);
    }

    for(int j = min_y; j <= max_y; j++) {
        for(int i = min_x; i <= max_x; i++) {

            if(matrix.find(i) != matrix.end() && matrix[i].find(j) != matrix[i].end()) {
                cout << " # ";
            } else {
                cout << " . ";
            }
        }
        cout << endl;
    }
}

int main() {

    string input;


    int min_total_rows = INT_MAX;
    int min_total_columns = INT_MAX;
    int min_x, min_y = INT_MAX;
    int max_x, max_y = INT_MIN;

    vector<tuple<int, int, int, int>> rows;

    while(getline(cin, input) && !input.empty()) {

        stringstream ss(input);

        long position_x, position_y;
        long velocity_x, velocity_y;

        ss.ignore(10);
        ss >> position_x;
        ss.ignore(2);
        ss >> position_y;
        ss.ignore(12);
        ss >> velocity_x;
        ss.ignore(2);
        ss >> velocity_y;

        rows.push_back(make_tuple(position_x, position_y, velocity_x, velocity_y));
    }

    int current_time = 0;

    calculate_new_position(current_time, min_y, max_y, min_total_rows, rows);

    tuple<bool, int, int, int> current_execution_result;

    while(true) {

        current_execution_result =
                calculate_new_position(current_time + 1, min_y, max_y, min_total_rows, rows);

        ++current_time;

        if (get<0>(current_execution_result)) {
            print_current_message(rows);
            break;
        } else {
            min_y = get<1>(current_execution_result);
            max_y = get<2>(current_execution_result);
            min_total_rows = get<3>(current_execution_result);
        }
    }

    cout << "The elves have to wait for " << current_time << " seconds " << endl;

    return EXIT_SUCCESS;
}