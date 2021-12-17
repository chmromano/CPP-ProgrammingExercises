// Christopher Romano

#include <iostream>

using namespace std;


// Observer class ------------------------------------------------------------------------------------------------------

class Observer {
public:
    virtual void HandleLimitReached() = 0;
};


// Counter class -------------------------------------------------------------------------------------------------------

class Counter {
public:
    virtual ~Counter() = default;;

    virtual void inc() = 0;

    virtual void dec() = 0;

    virtual operator int() = 0;
};


// OverflowCounter class -----------------------------------------------------------------------------------------------

class OverflowCounter : public Counter {
private:
    int value;
    int upperLim;
    Observer *obs;

    void Notify() { obs->HandleLimitReached(); };
public:
    OverflowCounter(int value_ = 0, int upperLim_ = 0) : value(value_), upperLim(upperLim_) {};

    void inc() override {
        if (value >= upperLim) {
            value = 0;
            this->Notify();
        } else {
            value++;
        }
    };

    void dec() override {
        if (value <= 0) {
            value = upperLim;
            this->Notify();
        } else {
            value--;
        }
    };

    operator int() override {
        return value;
    };

    void SetObserver(Observer *obs_) {
        obs = obs_;
    }
};


// UserCounter class ---------------------------------------------------------------------------------------------------

class CounterUser : public Observer {
private:
    OverflowCounter overflowCounter;
public:
    CounterUser(int upperLim_ = 5) : overflowCounter(0, upperLim_) {
        overflowCounter.SetObserver(this);
    }

    void IncrementBy(int n) {
        for (int i = n; i > 0; i--) {
            overflowCounter.inc();
        }
    }

    void HandleLimitReached() override {
        cout << "Limit has been reached." << endl;
    }
};


// Main ----------------------------------------------------------------------------------------------------------------

int main() {
    CounterUser cu(5);
    cu.IncrementBy(12); // OUTPUT: two times "Limit has been reached"
    CounterUser cu2(9);
    cu2.IncrementBy(9);
    cout << "Just passing time" << endl;
    cu2.IncrementBy(1); // OUTPUT: "Limit has been reached"
}