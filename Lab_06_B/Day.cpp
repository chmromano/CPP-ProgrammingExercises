#include "Day.h"

using namespace std;

Day::Day(int day_, string month_) : day(day_), month(month_) {}

bool Day::from_str(const string &s) {
    // Clear object.
    day = 0;
    month.erase(month.begin(), month.end());
    list.erase(list.begin(), list.end());

    const char *whitespace = " \t\n\r\f\v";
    string tmp_string, no_whitespace;

    // Trim leading and trailing whitespace.
    int start = static_cast<int>(s.find_first_not_of(whitespace));
    int end = static_cast<int>(s.find_last_not_of(whitespace)) + 1;
    if (end == string::npos || start == string::npos) return false;
    no_whitespace = s.substr(start, end - start);

    // Parse day.
    start = 0;
    end = static_cast<int>(no_whitespace.find(32, start));
    if (end == string::npos) return false;
    tmp_string = no_whitespace.substr(start, end - start);
    if (!valid_char(tmp_string)) return false;
    day = std::stoi(tmp_string);

    // Parse month.
    while (true) {
        try {
            if (no_whitespace.at(end) == 32) {
                end++;
            } else {
                break;
            }
        } catch (const std::out_of_range &oor) {
            break;
        }
    }
    start = end;
    end = static_cast<int>(no_whitespace.find(32, start));
    if (end == string::npos) return false;
    tmp_string = no_whitespace.substr(start, end - start);
    if (!valid_month(tmp_string)) return false;
    month = tmp_string;

    // Parse times. When whitespace is not found anymore it means it is the last time in the string, therefore read
    // create substring from start until end of string.
    int times_found = 0;
    bool run = true;
    while (run) {
        Time tmp_time;
        while (true) {
            try {
                if (no_whitespace.at(end) == 32) {
                    end++;
                } else {
                    break;
                }
            } catch (const std::out_of_range &oor) {
                break;
            }
        }
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
            run = false;
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
    // Initialise Time object with offset as hour value.
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

// Function to check if the month contained is the string is a valid month name.
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
