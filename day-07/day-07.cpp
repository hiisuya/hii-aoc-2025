#include "../helper.h"

using namespace std;

size_t get_splits(const string& filePath);

int main() {
    cout << get_splits("input.txt") << "\n";
}

size_t get_splits(const string& filePath) {
    ifstream input(filePath);

    vector<string> lines;
    for(string line; getline( input, line );) {
        lines.push_back(line);
    }

    vector<int> beam_pos;
    size_t total = 0;
    for (int i = 0; i < lines.size(); i++) {
        if (lines[i].find_first_of("S") != string::npos) {
            int start_pos = lines[i].find_first_of("S");
            beam_pos.push_back(start_pos);
            lines[i + 1][start_pos] = '|';
            continue;
        }

        vector<int> temp;
        for (int beam = 0; beam < beam_pos.size(); beam++) {
            int pos = beam_pos[beam];
            if (lines[i][pos] == '^') {
                lines[i][pos - 1] = '|';
                lines[i][pos + 1] = '|';
                temp.push_back(pos - 1);
                temp.push_back(pos + 1);
                total += 1;
            } else {
                lines[i][pos] = '|';
                if (count(temp.begin(), temp.end(), pos) == 0) {
                    temp.push_back(pos);
                }
            }
        }

        beam_pos.clear();
        beam_pos = temp;
    }

    return total;
}
