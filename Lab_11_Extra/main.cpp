// Christopher Romano

#include <iostream>
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


// DerivedObserver class ---------------------------------------------------------------------------------------------

class DerivedObserver : public CounterObserver {
private:
    string name;
public:
    // String has its own move method.
    DerivedObserver(string name_) : name(std::move(name_)) {};

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
    OverflowCounter(int value_ = 0, int upperLim_ = 10) : value(value_), upperLim(upperLim_) {};

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
    int upperLim;
    vector<CounterObserver *> obs;

    void Notify() {
        for (auto observer: obs) {
            observer->HandleLimitReached(this);
        }
    };
public:
    LimitedCounter(int value_ = 0, int upperLim_ = 10) : value(value_), upperLim(upperLim_) {};

    void inc() override {
        if (value < upperLim) {
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
    // Creating objects.
    DerivedObserver overflowObserver("OVF-OBS"), limitedObserver("LIM-OBS"), sharedObserver("SHR-OBS");
    OverflowCounter overflowCounter(0, 5);
    LimitedCounter limitedCounter(0, 10);

    // Assigning OVF-OBS observer to the overflow counter and testing. Counter at 0.
    overflowCounter.SetObserver(&overflowObserver);
    cout << "Testing overflowCounter with OVF-OBS (value = 0):" << endl;
    UseCounter(overflowCounter, 6); // Ceiling is reached once.
    UseCounter(overflowCounter, 12); // ceiling is reached twice.
    UseCounter(overflowCounter, -8); // Floor is reached twice.
    UseCounter(overflowCounter, 1); // Nothing happens.
    UseCounter(overflowCounter, 1); // Ceiling is reached once.

    // Assigning LIM-OBS observer to the limited counter and testing.
    limitedCounter.SetObserver(&limitedObserver);
    cout << endl << "Testing limitedCounter with LIM-OBS (value = 0):" << endl;
    UseCounter(limitedCounter, 11); // Ceiling is reached once.
    UseCounter(limitedCounter, 3); // Ceiling is reached thrice.
    UseCounter(limitedCounter, -10); // Nothing happens.
    UseCounter(limitedCounter, -1); // Floor is reached once.
    UseCounter(limitedCounter, -2); // Floor is reached twice.

    // Assigning SHR-OBS observer to both counters and testing.
    overflowCounter.SetObserver(&sharedObserver);
    limitedCounter.SetObserver(&sharedObserver);
    cout << endl << "Testing overflowCounter with OVF-OBS and SHR-OBS (value = 0):" << endl;
    UseCounter(overflowCounter, 6); // Ceiling is reached once.
    UseCounter(overflowCounter, 12); // ceiling is reached twice.
    UseCounter(overflowCounter, -8); // Floor is reached twice.
    UseCounter(overflowCounter, 1); // Nothing happens.
    UseCounter(overflowCounter, 1); // Ceiling is reached once.
    cout << endl << "Testing overflowCounter with LIM-OBS and SHR-OBS (value = 0):" << endl;
    UseCounter(limitedCounter, 11); // Ceiling is reached once.
    UseCounter(limitedCounter, 3); // Ceiling is reached thrice.
    UseCounter(limitedCounter, -10); // Nothing happens.
    UseCounter(limitedCounter, -1); // Floor is reached once.
    UseCounter(limitedCounter, -2); // Floor is reached twice.

    cout << endl
         << "Same test results but notified twice for each limit (one notification per observer)."
         << endl;
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