// Christopher Romano

#include <iostream>
#include <utility>
#include <vector>

using namespace std;


// Forward declaration of CounterObserver class.
class CounterObserver;


// Counter class -------------------------------------------------------------------------------------------------------

class Counter {
public:
    virtual ~Counter() = default;;

    virtual void inc() = 0;

    virtual void dec() = 0;

    virtual operator int() = 0;

    virtual void SetObserver(CounterObserver *obs) = 0;
};


// CounterObserver class -----------------------------------------------------------------------------------------------

class CounterObserver {
public:
    virtual void HandleLimitReached(Counter *ctr) = 0;
};


// InheritedObserver class ---------------------------------------------------------------------------------------------

class InheritedObserver : public CounterObserver {
private:
    string name;
public:
    InheritedObserver(string name_) : name(std::move(name_)) {};

    void HandleLimitReached(Counter *ctr) override {
        cout << "[" << name << "] Limit has been reached. Value: " << *ctr << endl;
    };
};


// OverflowCounter class -----------------------------------------------------------------------------------------------

class OverflowCounter : public Counter {
private:
    int value;
    int upperLim;
    vector<CounterObserver *> obs;

    void Notify() {
        for (auto observer: obs) {
            observer->HandleLimitReached(this);
        }
    };
public:
    OverflowCounter(int value_ = 0, int upperLim_ = 0) : value(value_), upperLim(upperLim_) {};

    void inc() override {
        if (value >= upperLim) {
            Notify();
            value = 0;
        } else {
            value++;
        }
    };

    void dec() override {
        if (value <= 0) {
            Notify();
            value = upperLim;
        } else {
            value--;
        }
    };

    operator int() override {
        return value;
    };

    void SetObserver(CounterObserver *obs_) override {
        obs.push_back(obs_);
    }
};


// LimitedCounter class ------------------------------------------------------------------------------------------------

class LimitedCounter : public Counter {
private:
    int value;
    int upper_lim;
    vector<CounterObserver *> obs;

    void Notify() {
        for (auto observer: obs) {
            observer->HandleLimitReached(this);
        }
    };
public:
    LimitedCounter(int value_ = 0, int upper_lim_ = 0) : value(value_), upper_lim(upper_lim_) {};

    void inc() override {
        if (value < upper_lim) {
            value++;
        } else {
            Notify();
        }
    };

    void dec() override {
        if (value > 0) {
            value--;
        } else {
            Notify();
        }
    };

    operator int() override {
        return value;
    };

    void SetObserver(CounterObserver *obs_) override {
        obs.push_back(obs_);
    }
};


// Main ----------------------------------------------------------------------------------------------------------------

void UseCounter(Counter &ctr, int num);

int main() {
    InheritedObserver overflowObserver("OVF_OBS"), limitedObserver("LIM_OBS"), sharedObserver("SHR_OBS");
    OverflowCounter overflowCounter(0, 5);
    LimitedCounter limitedCounter(0, 10);

    overflowCounter.SetObserver(&overflowObserver);
    overflowCounter.SetObserver(&sharedObserver);

    limitedCounter.SetObserver(&limitedObserver);
    limitedCounter.SetObserver(&sharedObserver);

    UseCounter(overflowCounter, 9);

    UseCounter(limitedCounter, 11);
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