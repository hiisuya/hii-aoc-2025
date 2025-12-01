#include <fstream>
#include <string>
#include <iostream>

using namespace std;

int get_password(int pos, string filePath, bool withClick);

#define MIN_VALUE 0
#define MAX_VALUE 99
#define LOOP_AMOUNT 100

int main() {
    cout << get_password(50, "input.txt", false) << "\n";
    cout << get_password(50, "input.txt", true) << "\n";
}

int get_password(int pos, string filePath, bool withClick) {
    std::ifstream input(filePath);
    int count = 0;

    for(string line; getline( input, line );) {
        int dir = line.substr(0, 1) == "L" ? -1 : 1;
        int amount = std::stoi(line.substr(1, -1));
        int diff = 0;

        if (amount >= LOOP_AMOUNT) {
            diff = amount / LOOP_AMOUNT;
            amount = (amount - (LOOP_AMOUNT * diff));
        }

        pos += (amount * dir);

        if (pos < MIN_VALUE || pos > MAX_VALUE) {
            pos += -(LOOP_AMOUNT * dir);
        }

        count += pos == 0;
    }

    return count;
}