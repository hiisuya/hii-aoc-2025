#include <fstream>
#include <string>
#include <iostream>
#include <vector>

using namespace std;

size_t get_invalid_ids(string filePath);

int main() {
    cout << get_invalid_ids("input.txt") << "\n";
}

vector<string> split_string_by(string input, string delimiter) {
    vector<string> output;
    int pos = 0;
    while ((pos = input.find(delimiter)) != string::npos) {
        string token = input.substr(0, pos);
        output.push_back(token);
        input.erase(0, pos + 1);
    }

    output.push_back(input);

    return output;
}

size_t get_invalid_ids(string filePath) {
    ifstream t(filePath);
    string str((istreambuf_iterator<char>(t)),
                istreambuf_iterator<char>());

    vector<string> inputs = split_string_by(str, ",");

    size_t total = 0;
    for (int i = 0; i < inputs.size(); i++) {
        vector<string> nums = split_string_by(inputs[i], "-");
        size_t num1 = std::stol(nums[0]);
        size_t num2 = std::stol(nums[1]);

        for (size_t index = num1; index < num2; index++) {
            string input = to_string(index);
            size_t len = input.length();
            string front = input.substr(0, len / 2);
            string back = input.substr((len / 2), -1);
            
            if (len >= 2) {
                if (front.compare(back) == 0) {
                    total += index;
                }
            }
        }
    }

    return total;
}