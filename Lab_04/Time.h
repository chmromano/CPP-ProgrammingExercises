#ifndef LAB_04_TIME_H
#define LAB_04_TIME_H


class Time {
public:
    Time(int h_ = 0, int min_ = 0);

    void read(const char *str);

    //const keyword does not allow the methods to change object parameters. In the below 3 functions it can be used.
    bool lessThan(Time time) const;

    Time subtract(Time time) const;

    void display() const;

private:
    int h;
    int min;
    //Static function does not operate on an object.
    static bool valid_char(const std::string &str);
};


#endif
