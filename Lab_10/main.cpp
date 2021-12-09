// Christopher Romano

#include <iostream>

using namespace std;


// Counter class -------------------------------------------------------------------------------------------------------

class Counter {
public:
    virtual ~Counter() = default;;

    virtual void inc() = 0;

    virtual void dec() = 0;

    virtual operator int() = 0;
};


// LimitedCounter class ------------------------------------------------------------------------------------------------

class LimitedCounter : public Counter {
private:
    int value;
    int upper_lim;
public:
    LimitedCounter(int value_ = 0, int upper_lim_ = 0) : value(value_), upper_lim(upper_lim_) {};

    void inc() override {
        if (value < upper_lim) value++;
    };

    void dec() override {
        if (value != 0) value--;
    };

    operator int() override {
        return value;
    };
};


// OverflowCounter class -----------------------------------------------------------------------------------------------

class OverflowCounter : public Counter {
private:
    int value;
    int upper_lim;
public:
    OverflowCounter(int value_ = 0, int upper_lim_ = 0) : value(value_), upper_lim(upper_lim_) {};

    void inc() override {
        if (value == upper_lim) {
            value = 0;
        } else {
            value++;
        }
    };

    void dec() override {
        if (value == 0) {
            value = upper_lim;
        } else {
            value--;
        }
    };

    operator int() override {
        return value;
    };
};


// Main ----------------------------------------------------------------------------------------------------------------

void UseCounter(Counter &ctr, int num);

int main(int argc, char **argv) {
    LimitedCounter lc(0, 5);
    OverflowCounter oc(5, 9);

    cout << oc << endl;
    UseCounter(oc, 5);
    cout << oc << endl; // should display zero
    UseCounter(oc, -1);
    cout << oc << endl; // should display 9
    oc.dec();
    cout << oc << endl; // should display 8

    cout << lc << endl;
    lc.inc();
    cout << lc << endl;
    lc.dec();
    cout << lc << endl;
    for (int i = 0; i < 10; ++i) lc.inc();
    cout << lc << endl;
    UseCounter(lc, -9);
    cout << lc << endl;

    return 0;
}

void UseCounter(Counter &ctr, int num) {
    if (num > 0) {
        for (int i = num; i > 0; i--) {
            ctr.inc();
        }
    } else if (num < 0) {
        for (int i = num; i < 0; i++) {
            ctr.dec();
        }
    }
}