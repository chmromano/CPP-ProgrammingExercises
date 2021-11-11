#include <string>
#include <iostream>
#include <cctype>
#include <iomanip>
#include "Time.h"

Time::Time(int h_, int min_) : h(h_), min(min_) {}

void Time::read(const char *str) {
    bool valid_input = false;
    std::string line, str_h, str_min;

    do {
        std::cout << str << " (hh:mm, 0 <= hh <= 23, 0 <= mm <= 59):" << std::endl;
        getline(std::cin, line);

        int delimiter = static_cast<int> (line.find(':'));

        if (delimiter != std::string::npos) {
            //Get substrings and check if they contain non-digit characters.
            str_h = line.substr(0, delimiter);
            str_min = line.substr(delimiter + 1, std::string::npos);
            if (valid_char(str_h) && valid_char(str_min)) {
                //Convert string to integer and check that they fall within allowed mm and hh ranges.
                int tmp_h, tmp_min;
                tmp_h = std::stoi(str_h);
                tmp_min = std::stoi(str_min);
                if (tmp_h >= 0 && tmp_h <= 23 && tmp_min >= 0 && tmp_min <= 59) {
                    h = tmp_h;
                    min = tmp_min;
                    valid_input = true;
                }
            }
        }
        if (!valid_input) std::cout << "Invalid input. ";
    } while (!valid_input);
}

bool Time::lessThan(Time time) {
    bool is_less = false;
    if (h < time.h) {
        is_less = true;
    } else if (h == time.h) {
        if (min < time.min) {
            is_less = true;
        }
    }
    return is_less;
}

Time Time::subtract(Time time) {
    Time duration;
    duration.h = h - time.h;
    duration.min = min - time.min;
    if (duration.min < 0) {
        duration.min += 60;
        duration.h -= 1;
    }
    return duration;
}

void Time::display() {
    std::cout << std::setiosflags(std::ios::right);
    std::cout << std::setfill('0') << std::setw(2) << h;
    std::cout << ":" << std::setfill('0') << std::setw(2) << min << std::endl;
}

//Helper function to check if a string contains non-digit characters.
bool Time::valid_char(const std::string &str) {
    bool valid = true;
    for (const char &ch: str) {
        if (!std::isdigit(ch)) {
            valid = false;
            break;
        }
    }
    return valid;
}
