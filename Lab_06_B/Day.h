#ifndef LAB_06_B_DAY_H
#define LAB_06_B_DAY_H


#include <vector>
#include "Time.h"

class Day {
public:
    Day();
    bool from_str(const std::string &s);
    std::string to_str();
    void dst(int offset);
private:
    int day;
    std::string month;
    std::vector<Time> list;
};


#endif