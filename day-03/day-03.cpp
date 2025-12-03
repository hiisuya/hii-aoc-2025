#include <fstream>
#include <string>
#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

int get_highest_voltage(string filePath);

int main() {
    cout << get_highest_voltage("input.txt") << "\n";
}

int get_highest_voltage(string filePath) {
    ifstream input(filePath);

    size_t total = 0;
    for(string line; getline( input, line );) {
        int first = line[0] - '0';
        int second = line[1] - '0';

        for (int i = 2; i < line.length(); i++) {
            int num = stoi(to_string(line[i] - '0'));
            int current = stoi(to_string(first).append(to_string(second)));
            int compare = stoi(to_string(first).append(to_string(num)));

            if (second > first) {
                first = second;
                second = num;
                continue;
            }

            if (compare > current) {
                second = num;
            }

        }

        total += stoi(to_string(first).append(to_string(second)));
    }

    return total;
}