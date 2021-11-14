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

Time Time::operator+(const Time &time) const {
    Time result;
    result.min = min + time.min;
    while (result.min > 59) {
        result.min -= 60;
        result.h += 1;
    }
    result.h += h + time.h;
    while (result.h > 23) {
        result.h -= 24;
    }
    return result;
}

//I can reuse previous methods for - and < in the overloaded methods.
Time Time::subtract(Time time) const {
    Time result;
    result.min = min - time.min;
    while (result.min < 0) {
        result.min += 60;
        result.h -= 1;
    }
    result.h += h - time.h;
    while (result.h < 0) {
        result.h += 24;
    }
    return result;
}

Time Time::operator-(const Time &time) const {
    return this->subtract(time);
}

bool Time::lessThan(Time time) const {
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

bool Time::operator<(const Time &time) const {
    return this->lessThan(time);
}

//I don't know if it's possible to reuse the display method for the << overloaded operator method.
void Time::display() const {
    std::cout << std::setiosflags(std::ios::right);
    std::cout << std::setfill('0') << std::setw(2) << h;
    std::cout << ":" << std::setfill('0') << std::setw(2) << min << std::endl;
}

std::ostream &operator<<(std::ostream &out, const Time &time) {
    out << std::setiosflags(std::ios::right);
    out << std::setfill('0') << std::setw(2) << time.h;
    out << ":" << std::setfill('0') << std::setw(2) << time.min;
    return out;
}

//Pre ++ method.
Time &Time::operator++() {
    ++min;
    if (min > 59) {
        min -= 60;
        h++;
        if (h > 23) {
            h -= 24;
        }
    }
    return *this;
}

//Post ++ method.
Time Time::operator++(int) {
    Time old = *this;
    ++min;
    if (min > 59) {
        min -= 60;
        h++;
        if (h > 23) {
            h -= 24;
        }
    }
    return old;
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