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
            beam_pos.push_back(lines[i].find_first_of("S"));
            continue;
        }

        vector<int> temp;
        for (int beam = 0; beam < beam_pos.size(); beam++) {
            int pos = beam_pos[beam];
            if (lines[i][pos] == '^') {
                temp.push_back(pos - 1);
                temp.push_back(pos + 1);
                total += 1;
            } else {
                if (count(temp.begin(), temp.end(), pos) == 0) {
                    temp.push_back(pos);
                }
            }
        }
        
        beam_pos = temp;
    }

    return total;
}
