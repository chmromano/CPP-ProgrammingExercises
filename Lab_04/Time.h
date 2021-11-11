#ifndef LAB_04_TIME_H
#define LAB_04_TIME_H


class Time {
public:
    Time(int h_ = 0, int min_ = 0);

    void read(const char *str);

    bool lessThan(Time time);

    Time subtract(Time time);

    void display();

private:
    int h;
    int min;
    bool valid_char(const std::string &str);
};


#endif
