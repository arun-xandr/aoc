//
// Created by Arun Shanmugam Kumar on 2018-12-14.
//
#include <iostream>
#include <stack>
#include <sstream>
#include <vector>
#include <map>
#include <set>

using namespace std;

int main() {

    int number_of_players = 476;
    vector<int> players(number_of_players, 0);
    int current_player = 0;
    vector<int> marbles;
    marbles.push_back(0);

    int next_marble_number = 1;
    int current_marble_index = 0;
    int exit_condition = 71657;
    int max_points = INT_MIN;

    while(next_marble_number != exit_condition) {

        int new_marble_index = ((current_marble_index + 1) % marbles.size()) + 1;

        if (next_marble_number % 23 != 0) {
            if(new_marble_index >= marbles.size()) {
                marbles.push_back(next_marble_number);
            } else {
                marbles.insert(marbles.begin() + new_marble_index, next_marble_number);
            }
        } else {
            int current_score = next_marble_number;
            players[current_player] += current_score;

            new_marble_index = current_marble_index - 7;

            if(new_marble_index < 0) {
                new_marble_index = marbles.size() + new_marble_index;
            }

            players[current_player] += marbles[new_marble_index];

            marbles.erase(marbles.begin() + new_marble_index);

            max_points = max(max_points, players[current_player]);

        }

        current_player = ((current_player + 1) % number_of_players);
        current_marble_index = new_marble_index;
        ++next_marble_number;
    }

    cout << "The winning Elf's score is " << max_points << endl;

    return EXIT_SUCCESS;
}
