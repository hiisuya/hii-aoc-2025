#include "../helper.h"

using namespace std;

size_t get_splits(const string& filePath);
size_t get_timelines(const string& filePath);

int main() {
    cout << get_splits("input.txt") << "\n";
    cout << get_timelines("input.txt") << "\n";
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

struct TimelinePos {
    int pos;
    size_t timelines;
    size_t next;

    TimelinePos(int pos, size_t timelines) :
        pos(pos), timelines(timelines), next(timelines) {}
};

TimelinePos* find_by_pos(std::vector<TimelinePos>& vec, int pos) {
    auto it = std::find_if(vec.begin(), vec.end(),
        [&](const TimelinePos& item) {
            return item.pos == pos;
        }
    );

    if (it != vec.end()) {
        return &(*it);
    }

    return nullptr;
}

size_t get_next_timeline(const vector<string>& lines, int index, int pos, TimelinePos* tp_far, TimelinePos* tp_mid, TimelinePos* tp_cur, int offset) {
    if (!tp_far || !tp_cur) {
        return 0;
    }

    size_t num = 0;
    int mid = pos + offset;
    int far = pos + offset * 2;

    if (lines[index - 1][far] != '.' && lines[index][far] == '^') {
        num += tp_far->timelines;
    }

    if (lines[index - 1][mid] != '.') {
        num += tp_mid->timelines;
    }

    if (lines[index - 1][pos] != '.') {
        num += tp_cur->timelines;
    }

    return num;
}

size_t get_timelines(const string& filePath) {
    ifstream input(filePath);

    vector<string> lines;
    for(string line; getline( input, line );) {
        lines.push_back(line);
    }

    vector<TimelinePos> timelines;
    vector<int> beam_pos;
    size_t total = 0;
    for (int i = 0; i < lines.size(); i++) {
        if (lines[i].find_first_of("S") != string::npos) {
            int start_pos = lines[i].find_first_of("S");
            beam_pos.push_back(start_pos);
            timelines.push_back(TimelinePos(start_pos, 1));
            lines[i + 1][start_pos] = '|';
            continue;
        }

        vector<int> temp;
        for (int beam = 0; beam < beam_pos.size(); beam++) {
            int pos = beam_pos[beam];
            if (lines[i][pos] == '^') {
                TimelinePos* tp_cur = find_by_pos(timelines, pos);
                TimelinePos* tp_left = find_by_pos(timelines, (pos - 1));
                TimelinePos* tp_right = find_by_pos(timelines, (pos + 1));
                TimelinePos* tp_left_far = find_by_pos(timelines, (pos - 2));
                TimelinePos* tp_right_far = find_by_pos(timelines, (pos + 2));

                auto side = [&](int offset, TimelinePos*& tp_side, TimelinePos* tp_far) {
                    int side_pos = pos + offset;

                    if (!tp_side) {
                        timelines.push_back(TimelinePos(side_pos, 1));
                    } else {
                        tp_side->next = get_next_timeline(lines, i, pos, tp_far, tp_side, tp_cur, offset);
                    }

                    temp.push_back(side_pos);
                    lines[i][side_pos] = '|';
                };

                side(-1, tp_left, tp_left_far);
                side(1, tp_right, tp_right_far);
            } else {
                lines[i][pos] = '|';
                if (count(temp.begin(), temp.end(), pos) == 0) {
                    temp.push_back(pos);

                    TimelinePos* tp = find_by_pos(timelines, pos);
                    if (!tp) {
                        timelines.push_back(TimelinePos(pos, 1));
                    }
                } 
                
            }
        }

        for (auto& tl : timelines) {
            tl.timelines = tl.next;
        }

        beam_pos.clear();
        beam_pos = temp;
    }

    for (int i = 0; i < lines.back().size(); i++) {
        if (lines.back()[i] == '|') {
            for (const auto& tp : timelines) {
                if (tp.pos == i) {
                    total += tp.timelines;
                    break;
                }
            }
        }
    }

    return total;
}
