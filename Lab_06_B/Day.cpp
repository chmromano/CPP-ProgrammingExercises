#include "Day.h"

using namespace std;

Day::Day(int day_, string month_) : day(day_), month(month_) {}

bool Day::from_str(const string &s) {
    month.erase(month.begin(), month.end());
    list.erase(list.begin(), list.end());

    string tmp_string;
    int start = 0;
    int end;

    end = static_cast<int>(s.find(32, start));
    if (end == string::npos) return false;
    tmp_string = s.substr(start, end - start);
    if (!valid_char(tmp_string)) return false;
    day = std::stoi(tmp_string);

    start = end + 1;
    end = static_cast<int>(s.find(32, start));
    tmp_string = s.substr(start, end - start);
    if (!valid_month(tmp_string)) return false;
    month = tmp_string;

    const int chars_in_time = 5;
    int times_found = 0;
    while (true) {
        Time tmp_time;
        start = end + 1;
        if (start > s.length()) break;
        end = start + chars_in_time;
        tmp_string = s.substr(start, end - start);
        if (tmp_time.read_from_string(tmp_string)) {
            list.push_back(tmp_time);
            times_found++;
        } else {
            break;
        }
    }

    if (times_found > 0) {
        return true;
    } else {
        return false;
    }
}

string Day::to_str() {
    ostringstream out;
    out << day << " " << month;
    for (Time tmp: list) {
        out << " " << tmp;
    }
    return out.str();
}

void Day::dst(int offset) {
    Time dst_offset(offset);
    for (auto &tmp: list) {
        tmp = tmp + dst_offset;
    }
}

bool Day::valid_char(const string &str) {
    bool valid = true;
    for (const char &ch: str) {
        if (!std::isdigit(ch)) {
            valid = false;
            break;
        }
    }
    return valid;
}

bool Day::valid_month(const string &str) {
    bool valid = false;
    std::vector<std::string> month_list = {"January", "February", "March", "April", "May", "June", "July", "August",
                                           "September", "October", "November", "December"};
    for (const string &tmp: month_list) {
        if (str == tmp) {
            valid = true;
            break;
        }
    }
    return valid;
}
