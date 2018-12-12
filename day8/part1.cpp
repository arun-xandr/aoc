//
// Created by Arun Shanmugam Kumar on 2018-12-11.
//
#include <iostream>
#include <stack>
#include <sstream>
#include <vector>
#include <map>
#include <set>

using namespace std;

struct node {
    int header[2];
    vector<node> children;
    vector<int> metadata;
};

void constructNode(stringstream& ss, struct node& parent) {

    if (!ss.rdbuf()->in_avail()) {
        return;
    }

    int number_of_children;
    int number_of_metadata;

    ss >> number_of_children;
    ss >> number_of_metadata;

    parent.header[0] = number_of_children;
    parent.header[1] = number_of_metadata;

    for(int i = 0; i < number_of_children; i++) {
        node current_child;
        parent.children.push_back(current_child);
        constructNode(ss, parent.children[i]);
    }

    for(int i = 0; i < number_of_metadata; i++) {

        int current_metadata;
        ss >> current_metadata;

        parent.metadata.push_back(current_metadata);
    }
}

int countTotalMetadata(struct node& parent) {

    int sum_of_metadata = 0;

    for(auto it = parent.metadata.begin(); it != parent.metadata.end(); it++) {
        sum_of_metadata += *it;
    }

    for(auto it = parent.children.begin(); it != parent.children.end(); it++) {
        sum_of_metadata += countTotalMetadata(*it);
    }

    return sum_of_metadata;
}

int main() {

    string input;
    node root;

    while(getline(cin, input) && !input.empty()) {

        stringstream ss(input);

        constructNode(ss, root);

        cout << "Sum of all metadata entries is " << countTotalMetadata(root) << endl;
    }

    return EXIT_SUCCESS;
}