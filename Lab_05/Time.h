#ifndef LAB_04_TIME_H
#define LAB_04_TIME_H


class Time {
    friend std::ostream &operator<<(std::ostream &out, const Time &time);

public:
    Time(int h_ = 0, int min_ = 0);

    void read(const char *str);

    bool lessThan(Time time) const;

    Time subtract(Time time) const;

    Time operator+(const Time &time) const;

    Time operator-(const Time &time) const;

    Time &operator++();

    Time operator++(int);

    bool operator<(const Time &time) const;

    //Now unused.
    void display() const;

private:
    int h;
    int min;

    static bool valid_char(const std::string &str);
};


#endif