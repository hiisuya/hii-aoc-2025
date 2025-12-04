#include <fstream>
#include <string>
#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

size_t get_forklift_roll_access(string filePath);

int main() {
    cout << get_forklift_roll_access("input.txt") << "\n";
}

size_t get_forklift_roll_access(string filePath) {
    ifstream input(filePath);

    vector<vector<char>> grid;

    size_t total = 0;
    for(string line; getline( input, line );) {
        vector<char> output(line.length());
        for (int i = 0; i < line.length(); i++) {
            output[i] = line[i];
        }
        grid.push_back(output);
    }

    for (int row = 0; row < grid.size(); row++) {
        const int MIN_CHECK = -1;
        const int MAX_CHECK = 1;
        const int MAX_PAPER = 4;

        for (int row_index = 0; row_index < grid[row].size(); row_index++) {
            int paper = 0;
            if (grid[row][row_index] == '.' || paper >= MAX_PAPER) {
                continue;
            }

            for (int x = MIN_CHECK; x <= MAX_CHECK; x++) {
                if ((row_index + x) <= MIN_CHECK || (row_index + x) > (grid[row].size() - 1)) {
                    continue;
                }

                for (int y = MIN_CHECK; y <= MAX_CHECK; y++) {
                    if ((row + y <= MIN_CHECK) || ((row + y) > (grid.size() - 1)) || (x == 0 && y == 0)) {
                        continue;
                    }

                    if (grid[row + y][row_index + x] == '@') {
                        paper++;
                    }
                }
            }

            if (paper < MAX_PAPER) {
                total++;
            }
        }
    }

    return total;
}