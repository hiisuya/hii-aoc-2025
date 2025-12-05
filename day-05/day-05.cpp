#include "../helper.h"

using namespace std;

size_t get_fresh_food(string filePath);
size_t get_all_fresh_food(string filePath);

int main() {
    cout << get_fresh_food("input.txt") << "\n";
    cout << get_all_fresh_food("input.txt") << "\n";
}

size_t get_fresh_food(string filePath) {
    ifstream input(filePath);

    vector<pair<size_t, size_t>> ranges;
    vector<size_t> ids;
    vector<size_t> fresh;

    for(string line; getline( input, line );) {
        int dash_index = line.find("-");
        if (dash_index > 0) {
            ranges.push_back({stol(line.substr(0, dash_index)), stol(line.substr(dash_index + 1, -1))});
            continue;
        }

        if (line != "") {
            ids.push_back(stol(line));
        }
    }

    for (const size_t& id: ids) {
        for (const auto& range : ranges) {
            if (id >= range.first && id <= range.second) {
                fresh.push_back(id);
                break;
            }
        }
    }

    return fresh.size();
}

size_t get_all_fresh_food(string filePath) {
    ifstream input(filePath);

    vector<pair<size_t, size_t>> ranges;
    vector<pair<size_t, size_t>> new_ranges;

    for(string line; getline( input, line );) {
        int dash_index = line.find("-");
        if (dash_index > 0) {
            ranges.push_back({stol(line.substr(0, dash_index)), stol(line.substr(dash_index + 1, -1))});
            continue;
        }

        if (line == "") {
            break;
        }
    }

    sort(ranges.begin(), ranges.end(), [](auto &left, auto &right) {
        return left.first < right.first;
    });

    for (const auto& range : ranges) {
        if (new_ranges.empty() || range.first > new_ranges.back().second) {
            new_ranges.push_back({range.first, range.second});
        } else {
            new_ranges.back().second = max(new_ranges.back().second, range.second);
        }
    }

    size_t total = 0;
    for (const auto& range: new_ranges) {
        total += (range.second - range.first) + 1;
    }

    return total;
}
