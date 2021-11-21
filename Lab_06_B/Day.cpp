#include "Day.h"

using namespace std;

Day::Day(int day_, string month_) : day(day_), month(month_) {}

bool Day::from_str(const string &s) {
    // Clear object.
    day = 0;
    month.erase(month.begin(), month.end());
    list.erase(list.begin(), list.end());

    // Trim whitespace.
    string tmp_string, no_whitespace;
    const char *whitespace = " \t\n\r\f\v";
    int start = static_cast<int>(s.find_first_not_of(whitespace));
    int end = static_cast<int>(s.find_last_not_of(whitespace)) + 1;
    if (end == s.size()) {
        no_whitespace = s.substr(start, string::npos);
    } else {
        no_whitespace = s.substr(start, end - start);
    }

    // Find day.
    start = 0;
    end = static_cast<int>(no_whitespace.find(32, start));
    if (end == string::npos) return false;
    tmp_string = no_whitespace.substr(start, end - start);
    if (!valid_char(tmp_string)) return false;
    day = std::stoi(tmp_string);

    // Find month.
    while (no_whitespace.at(end) == 32) end++; // Loop in case there are multiple spaces between string items.
    start = end;
    end = static_cast<int>(no_whitespace.find(32, start));
    if (end == string::npos) return false;
    tmp_string = no_whitespace.substr(start, end - start);
    if (!valid_month(tmp_string)) return false;
    month = tmp_string;

    // Find times.
    int times_found = 0;
    bool run = true;
    while (run) {
        Time tmp_time;
        while (no_whitespace.at(end) == 32) end++;
        start = end;
        end = static_cast<int>(no_whitespace.find(32, start));

        if (end == string::npos) {
            tmp_string = no_whitespace.substr(start, string::npos);
            run = false;
        } else {
            tmp_string = no_whitespace.substr(start, end - start);
        }

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
    // Create stringstream, form string, and return string.
    ostringstream out;
    out << day << " " << month;
    for (const Time &tmp: list) {
        out << " " << tmp;
    }
    return out.str();
}

void Day::dst(int offset) {
    // Initialise Time object with hour = offset.
    Time dst_offset(offset);
    for (Time &tmp: list) {
        tmp = tmp + dst_offset;
    }
}

bool Day::valid_char(const string &str) {
    bool valid = true;
    for (const char &ch: str) {
        if (!isdigit(ch)) {
            valid = false;
            break;
        }
    }
    return valid;
}

bool Day::valid_month(const string &str) {
    bool valid = false;
    vector<string> month_list = {"January", "February", "March", "April", "May", "June", "July", "August",
                                 "September", "October", "November", "December"};
    for (const string &tmp: month_list) {
        if (str == tmp) {
            valid = true;
            break;
        }
    }
    return valid;
}
