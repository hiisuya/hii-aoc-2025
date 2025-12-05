#include "../helper.h"

using namespace std;

int get_highest_voltage(string filePath);
size_t get_highest_voltage(string filePath, int batteries);

int main() {
    cout << get_highest_voltage("input.txt") << "\n";
    cout << get_highest_voltage("input.txt", 12) << "\n";
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

size_t get_highest_voltage(string filePath, int batteries) {
    ifstream input(filePath);
    
    size_t total = 0;
    for(string line; getline( input, line );) {
        vector<int> output;
        int length = line.length();
        int index = 0;

        for (int i = 0; i < batteries; i++) {
            for (int k = index; k < length; k++) {
                int temp = line[k] - '0';
                for (int j = k + 1; j < length; j++) {
                    if ((line[j] - '0' > temp) && ((length - j) > (12 - (output.size() + 1)))) {
                       temp = line[j] - '0';
                       index = j + 1;
                    }
                }

                bool shouldUpdate = (temp >= line[k] - '0' || index == k);
                if (shouldUpdate) {
                    index = index == k ? index + 1 : index;
                    output.push_back(temp);
                    break;
                }
            }
        }

        string value;
        for (int c: output) {
            value.append(to_string(c));
        }

        total += stol(value);
    }

    return total;
}
