#ifndef LAB_06_B_DAY_H
#define LAB_06_B_DAY_H

#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include "Time.h"

class Day {
public:
    Day(int day_ = 1, std::string month_ = "January");

    bool from_str(const std::string &s);

    std::string to_str();

    void dst(int offset);

private:
    int day;
    std::string month;
    std::vector<Time> list;

    static bool valid_char(const std::string &str);

    static bool valid_month(const std::string &str);
};


#endif