#include "../helper.h"

using namespace std;

size_t get_accumulative_total_rl(string filePath);

int main() {
    cout << get_accumulative_total_rl("input.txt") << "\n";
}

struct Problem {
    vector<string> values;
    char op;
    int start_index;
    int end_index;
    int length;
};

inline size_t do_operation(const char op, size_t num1, size_t num2) {
    return (op == '+' ? (num1 + num2) : (num1 * num2));
}

void get_start_and_end_index(string& input, vector<Problem>& problems) {
    size_t pos_start = 0, pos_end;

    while ((pos_end = (input.find_first_of("+*", pos_start))) != string::npos) {
        Problem p;
        p.op = *input.substr(pos_end, 1).data();
        p.start_index = pos_end;
        pos_start = pos_end + 1;
        problems.push_back(p);
    }

    for (auto problem = problems.begin(); problem != problems.end(); ++problem) {
        if (next(problem) != problems.end()) {
            problem->end_index = ((next(problem)->start_index) - 1);
        } else {
            problem->end_index = (input.length());
        }
        problem->length = problem->end_index - problem->start_index;
    }
}

void get_values_in_line(string& input, vector<Problem>& problems) {
    size_t pos_start = 0, pos_end;

    for (auto& problem : problems) {
        problem.values.push_back(input.substr(problem.start_index, problem.length));
    }
}

size_t get_accumulative_total_rl(string filePath) {
    ifstream input(filePath);

    vector<string> rev_file;
    vector<Problem> problems;

    for(string line; getline( input, line );) {
        rev_file.push_back(line);
    }

    for (int i = rev_file.size() - 1; i >= 0; i--) {
        if (i == rev_file.size() - 1) {
            get_start_and_end_index(rev_file[i], problems);
            continue;
        }

        get_values_in_line(rev_file[i], problems);
    }

    reverse(problems.begin(), problems.end());

    size_t total = 0;
    for (auto& problem : problems) {
        reverse(problem.values.begin(), problem.values.end());

        vector<size_t> nums;
        for (int i = 0; i < problem.length; i++) {
            string num_str = "";
            for (const auto& val : problem.values) {
                if (val[i] != ' ') {
                    num_str += val[i];
                }
            }

            nums.push_back(stoll(num_str));
        }

        size_t output = nums[0];
        for (int i = 1; i < nums.size(); i++) {
            output = do_operation(problem.op, output, nums[i]);
        }

        total += output;
    }   

    return total;
}