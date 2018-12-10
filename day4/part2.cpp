//
// Created by Arun Shanmugam Kumar on 12/9/18.
//

#include <iostream>
#include <vector>
#include <map>
#include <sstream>
#include <sstream>
#include "date/date.h"

using namespace std;
using namespace std::chrono;

int main() {

    vector<tuple<system_clock::time_point, string>> records;
    string currentRecord;

    while(getline(cin, currentRecord) && !currentRecord.empty()) {

        stringstream ss(currentRecord);

        string date;
        string time;
        string rest;

        ss >> date >> time >> rest >> rest;

        string date_time = date + " " + time;
        date_time = date_time.substr(1, date_time.size() - 2);

        system_clock::time_point tp;
        istringstream in{date_time};
        in >> date::parse("%F %H:%M", tp);

        records.push_back(make_tuple(tp, rest));
    }

    sort(records.begin(), records.end(), [](auto a, auto b){
        if (get<0>(a) < get<0>(b)) return true;
        if (get<0>(b) < get<0>(a)) return false;
        return false;
    });

    int max_sleep_minute = INT_MIN;
    int max_sleep_count = INT_MIN;
    string guard_max_total_time_asleep;

    map<string, map<long, int>> guard_to_sleep_count_map;

    string current_guard;
    auto previous_wakeup_minutes = 0;

    for(vector<tuple<system_clock::time_point, string>>::iterator it = records.begin(); it != records.end(); ++it) {
        string current = get<1>(*it);
        system_clock::time_point tp = get<0>(*it);
        auto diff = date::make_time(tp - date::floor<date::days>(tp));

        if(current.find("#") != string::npos) {
            current_guard = current;
        } else if (current == "up") {

            for(int i = previous_wakeup_minutes; i < diff.minutes().count(); i++) {
                guard_to_sleep_count_map[current_guard][i]++;

                if (max_sleep_count < guard_to_sleep_count_map[current_guard][i]) {
                    max_sleep_count = guard_to_sleep_count_map[current_guard][i];
                    max_sleep_minute = i;
                    guard_max_total_time_asleep = current_guard;
                }
            }

            previous_wakeup_minutes = diff.minutes().count();
        } else if (current == "asleep") {
            previous_wakeup_minutes = diff.minutes().count();
        } else {
            return EXIT_FAILURE;
        }
    }

    cout << "best guard/minute combination " << stoi(guard_max_total_time_asleep.substr(1)) * max_sleep_minute << endl;

    return EXIT_SUCCESS;
}
