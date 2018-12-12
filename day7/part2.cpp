//
// Created by Arun Shanmugam Kumar on 2018-12-10.
//


#include <iostream>
#include <stack>
#include <sstream>
#include <vector>
#include <map>
#include <set>

using namespace std;

int main() {

    string current_step;
    vector<pair<char, char>> edges;
    set<char> unique_steps;

    while(getline(cin, current_step) && !current_step.empty()) {

        stringstream ss(current_step);

        char first;
        char second;
        string skip;

        ss >> skip >> first >> skip >> skip >> skip >> skip >> skip >> second;
        edges.push_back(make_pair(first, second));
        unique_steps.insert(first);
        unique_steps.insert(second);
    }

    sort(edges.begin(), edges.end(), [](auto a, auto b){
       return get<1>(a) < get<1>(b);
    });

    map<char, int> incoming_edges_counter_map;
    map<char, vector<char>> incoming_edges_dependencies_map;
    vector<char> next_edge;

    for(auto it = edges.begin(); it != edges.end(); ++it) {
        pair<char, char> current_edge = *it;
        char from = get<0>(current_edge);
        char to = get<1>(current_edge);
        incoming_edges_counter_map[to]++;
        incoming_edges_dependencies_map[to].push_back(from);
    }

    int time_taken = INT_MIN;
    map<char, int> step_to_max_time_to_finish_map;
    set<char> visited;

    for(auto it = unique_steps.begin(); it != unique_steps.end(); ++it) {
        if(incoming_edges_counter_map.find(*it) == incoming_edges_counter_map.end() ||
           incoming_edges_counter_map[*it] == 0) {
            next_edge.push_back(*it);
            step_to_max_time_to_finish_map[*it] = 60 + (*it - 65 + 1);
            time_taken = step_to_max_time_to_finish_map[*it];
            visited.insert(*it);
        }
    }

    auto it = next_edge.begin();
    while(it != next_edge.end()) {

            char current_node = *it;

            cout << current_node << endl;

            if (visited.find(current_node) == visited.end() ) {
                int max_time_taken = INT_MIN;
                vector<char> dependencies = incoming_edges_dependencies_map[current_node];
                for(auto dependency = dependencies.begin(); dependency != dependencies.end(); dependency++) {
                    max_time_taken = max(max_time_taken, step_to_max_time_to_finish_map[*dependency]);
                }
                step_to_max_time_to_finish_map[current_node] = max_time_taken + 60 + (current_node - 65 + 1);
                time_taken = step_to_max_time_to_finish_map[current_node];
                visited.insert(current_node);
            }

            it = next_edge.erase(it);

            // opportunity for optimization by using a heap
            for(auto it1 = edges.begin(); it1 != edges.end(); it1++) {

                if (get<0>(*it1) == current_node) {

                    incoming_edges_counter_map[get<1>(*it1)]--;

                    if(incoming_edges_counter_map[get<1>(*it1)] <= 0) {
                        next_edge.push_back(get<1>(*it1));
                        it = next_edge.begin();
                    }
                }
            }
    }

    cout << "Total time taken is " << time_taken << endl;

    return EXIT_SUCCESS;
}