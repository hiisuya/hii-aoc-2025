#include "../helper.h"

using namespace std;

size_t get_accumulative_total(string filePath);
size_t get_accumulative_total_rl(string filePath);

int main() {
    cout << get_accumulative_total("input.txt") << "\n";
    cout << get_accumulative_total_rl("test.txt") << "\n";
}

struct Problem {
    vector<size_t> values;
    char op;
};

inline size_t do_operation(const char op, size_t num1, size_t num2) {
    return (op == '+' ? (num1 + num2) : (num1 * num2));
}

inline string trim(string& str) {
    str.erase(str.find_last_not_of(' ') + 1);
    str.erase(0, str.find_first_not_of(' '));
    return str;
}

int replace_spaces_with_char(string& input, const char& replace) {
    string result;
    int length = 0;
    bool prev_space = false;

    for (char c : input) {
        if (c == ' ') {
            if (!prev_space) {
                result += replace;
                prev_space = true;
                length++;
            }
        } else {
            result += c;
            prev_space = false;
        }
    }

    input = result;
    return length + 1;
}

void split(string s, string delimiter, vector<Problem>& problems) {
    size_t pos_start = 0, pos_end, delim_len = delimiter.length();
    string token;
    vector<string> res;

    int index = 0;
    while ((pos_end = s.find(delimiter, pos_start)) != string::npos) {
        token = s.substr(pos_start, pos_end - pos_start);
        pos_start = pos_end + delim_len;
        if (token != " ") {
            if (token.find_first_of("0123456789") != string::npos) {
                problems[index].values.emplace_back(stoi(token));
            } else {
                problems[index].op = *token.data();
            }
        }

        index++;
    }

    token = s.substr(pos_start, pos_end - pos_start);
    if (token.find_first_of("0123456789") != string::npos) { 
        problems[index].values.emplace_back(stoi(token));
    } else {
        problems[index].op = *token.data();
    }
}

size_t get_accumulative_total(string filePath) {
    ifstream input(filePath);

    vector<Problem> problems;
    
    size_t total = 0;
    for(string line; getline( input, line );) {
        trim(line);
        int length = replace_spaces_with_char(line, ',');

        cout << line << "\n";

        if (problems.empty()) {
            problems.resize(length);
        }

        split(line, ",", problems);
    }

    size_t output = 0;
    for (const auto& problem : problems) {
        output = problem.values[0];
        for (int i = 1; i < problem.values.size(); i++) {
            output = do_operation(problem.op, output, problem.values[i]);
        }

        total += output;
    }

    return total;
}