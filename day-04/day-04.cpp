#include "../helper.h"

using namespace std;

size_t get_forklift_roll_access(string filePath);
size_t get_forklift_roll_access_max(string filePath);

int main() {
    cout << get_forklift_roll_access("input.txt") << "\n";
    cout << get_forklift_roll_access_max("input.txt") << "\n";
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
            if (grid[row][row_index] == '.') {
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

size_t get_forklift_roll_access_max(string filePath) {
    ifstream input(filePath);

    vector<vector<char>> grid;

    for(string line; getline( input, line );) {
        vector<char> output(line.length());
        for (int i = 0; i < line.length(); i++) {
            output[i] = line[i];
        }
        grid.push_back(output);
    }

    size_t total = 0;
    bool done = false;
    while (!done) {
        vector<pair<int, int>> remove_indeces;
        
        for (int row = 0; row < grid.size(); row++) {
            const int MIN_CHECK = -1;
            const int MAX_CHECK = 1;
            const int MAX_PAPER = 4;

            for (int row_index = 0; row_index < grid[row].size(); row_index++) {
                int paper = 0;
                if (grid[row][row_index] == '.') {
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
                    remove_indeces.push_back({row_index, row});
                    total++;
                }
            }
        }

        if (remove_indeces.size() == 0) {
            done = true;
            break;
        } else {
            for (pair<int, int> v: remove_indeces) {
                grid[v.second][v.first] = '.';
            }
        }
    }
    

    return total;
}