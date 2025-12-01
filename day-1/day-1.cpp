#include <fstream>
#include <string>
#include <iostream>

using namespace std;

int get_password(int pos, string filePath);
int get_password_all(int pos, string filePath);

#define MIN_VALUE 0
#define MAX_VALUE 99
#define LOOP_AMOUNT 100

int main() {
    cout << get_password(50, "input.txt") << "\n";
    cout << get_password_all(50, "input.txt") << "\n";
}

int get_password(int pos, string filePath) {
    std::ifstream input(filePath);
    int count = 0;

    for(string line; getline( input, line );) {
        int dir = line.substr(0, 1) == "L" ? -1 : 1;
        int amount = std::stoi(line.substr(1, -1));

        if (amount >= LOOP_AMOUNT) {
            int diff = amount / LOOP_AMOUNT;
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

int get_password_all(int pos, string filePath) {
    std::ifstream input(filePath);
    int count = 0;

    for(string line; getline( input, line );) {
        int dir = line.substr(0, 1) == "L" ? -1 : 1;
        int amount = std::stoi(line.substr(1, -1));
        int newPos = 0;

        if (amount >= LOOP_AMOUNT) {
            int diff = amount / LOOP_AMOUNT;
            amount = (amount - (LOOP_AMOUNT * diff));
            count += diff;

            if (pos == 0 && amount == 0) {
                continue;
            }
        }
        
        newPos = pos + (amount * dir);

        if (newPos < MIN_VALUE || newPos > MAX_VALUE) {
            if (amount >= LOOP_AMOUNT) {
                newPos += -(LOOP_AMOUNT * dir);
            } else {
                if (dir == -1) {
                    newPos = ((LOOP_AMOUNT + pos) - amount);
                } else {
                    newPos = newPos - LOOP_AMOUNT;
                }
            }

            if (pos != 0 && newPos != 0) {
                count++;
            }
        }

        pos = newPos;
        count += (pos == 0);
    }

    return count;
}