#include "../helper.h"

using namespace std;

size_t get_invalid_ids(string filePath);
size_t get_all_repeat_ids(string filePath);

int main() {
    cout << get_invalid_ids("input.txt") << "\n";
    cout << get_all_repeat_ids("input.txt") << "\n";
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

size_t get_all_repeat_ids(string filePath) {
    ifstream t(filePath);
    string str((istreambuf_iterator<char>(t)),
                istreambuf_iterator<char>());

    vector<string> inputs = split_string_by(str, ",");

    size_t total = 0;
    for (int i = 0; i < inputs.size(); i++) {
        vector<string> nums = split_string_by(inputs[i], "-");
        size_t num1 = std::stol(nums[0]);
        size_t num2 = std::stol(nums[1]);

        for (size_t index = num1; index <= num2; index++) {
            string input = to_string(index);
            size_t len = input.length();
            string pattern;

            for (int k = 0; k < len; k++) {
                int p_len = pattern.size();
                
                if (p_len == 0) {
                    pattern.append(input.substr(k, 1));
                    continue;
                }

                if (pattern.compare(input.substr(k, p_len)) == 0) {
                    bool matching = len == 2;
                    int pos = p_len;

                    while (pos <= len && !matching) {
                        if (pattern.compare(input.substr(pos, p_len)) == 0) {
                            pos += p_len;
                            if (pos == len) {
                                matching = true;
                            }
                        } else {
                            break;
                        }
                    }
                    
                    if (matching) {
                        total += index;
                        break;
                    }
                }

                pattern.append(input.substr(k, 1));
            }
        }
    }

    return total;
}