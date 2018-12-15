//
// Created by Arun Shanmugam Kumar on 2018-12-14.
//
#include <iostream>
#include <stack>
#include <sstream>
#include <vector>
#include <map>
#include <set>
#include <list>

using namespace std;

int main() {

    int number_of_players = 476;
    vector<long> players(number_of_players, 0);
    int current_player = 0;
    list<int> marbles;
    marbles.push_back(0);

    int next_marble_number = 1;
    auto current_marble_itr = marbles.begin();
    int last_marble_number = 71657 * 100;
    long max_points = INT_MIN;

    while(next_marble_number <= last_marble_number) {

        list<int>::iterator new_marble_itr;

        if(next(current_marble_itr) == marbles.end()) {
            new_marble_itr = marbles.begin();
            new_marble_itr = next(new_marble_itr);
        } else {
            new_marble_itr = next(next(current_marble_itr));
        }

        if (next_marble_number % 23 != 0) {
            if(new_marble_itr == marbles.end()) {
                marbles.push_back(next_marble_number);
                new_marble_itr = prev(marbles.end());
            } else {
                new_marble_itr = marbles.insert(new_marble_itr, next_marble_number);
            }
        } else {
            int current_score = next_marble_number;
            players[current_player] += current_score;

            int number_of_rotations = 7;
            new_marble_itr = current_marble_itr;

            while(--number_of_rotations >= 0) {
                if (new_marble_itr == marbles.begin()) {
                    new_marble_itr = marbles.end();
                }
                new_marble_itr = prev(new_marble_itr);
            }

            players[current_player] += *new_marble_itr;
            new_marble_itr = marbles.erase(new_marble_itr);
            max_points = max(max_points, players[current_player]);
        }

        current_player = ((current_player + 1) % number_of_players);
        current_marble_itr = new_marble_itr;
        ++next_marble_number;
    }

    cout << "The winning Elf's score is " << max_points << endl;

    return EXIT_SUCCESS;
}
