// Christopher Romano

#include <iostream>

using namespace std;


// Observer class ------------------------------------------------------------------------------------------------------

class Observer {
public:
    virtual void HandleLimitReached() = 0;
};


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


// OverflowCounter class -----------------------------------------------------------------------------------------------

class OverflowCounter : public Counter {
private:
    int value;
    int upperLim;
    CounterObserver *obs;

    void Notify() { obs->HandleLimitReached(this); };
public:
    OverflowCounter(int value_ = 0, int upperLim_ = 0) : value(value_), upperLim(upperLim_) {};

    void inc() override {
        if (value >= upperLim) {
            value = 0;
            Notify();
        } else {
            value++;
        }
    };

    void dec() override {
        if (value <= 0) {
            value = upperLim;
        } else {
            value--;
        }
    };

    operator int() override {
        return value;
    };

    void SetObserver(CounterObserver *obs_) override {
        obs = obs_;
    }
};


// LimitedCounter class ------------------------------------------------------------------------------------------------

class LimitedCounter : public Counter {
private:
    int value;
    int upper_lim;
    CounterObserver *obs;

    void Notify() { obs->HandleLimitReached(this); };
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
        if (value > 0) value--;
    };

    operator int() override {
        return value;
    };

    void SetObserver(CounterObserver *obs_) override {
        obs = obs_;
    }
};


// CounterUserOver class ---------------------------------------------------------------------------------------------------

class CounterUserOver : public CounterObserver {
private:
    OverflowCounter overflowCounter;
public:
    CounterUserOver(int upperLim_ = 5) : overflowCounter(0, upperLim_) {
        overflowCounter.SetObserver(this);
    }

    void IncrementBy(int n) {
        for (int i = n; i > 0; i--) {
            overflowCounter.inc();
        }
    }

    void HandleLimitReached(Counter *ctr) override {
        cout << "Limit reached. Current value: " << *ctr << endl;
    }
};


// CounterUserLim class ---------------------------------------------------------------------------------------------------

class CounterUserLim : public CounterObserver {
private:
    LimitedCounter limitedCounter;
public:
    CounterUserLim(int upperLim_ = 5) : limitedCounter(0, upperLim_) {
        limitedCounter.SetObserver(this);
    }

    void IncrementBy(int n) {
        for (int i = n; i > 0; i--) {
            limitedCounter.inc();
        }
    }

    void HandleLimitReached(Counter *ctr) override {
        cout << "Limit reached. Current value: " << *ctr << endl;
    }
};


// Main ----------------------------------------------------------------------------------------------------------------

void UseCounter(Counter &ctr, int num);

int main() {
    CounterUserOver cu(5);
    cu.IncrementBy(12); //OUTPUT: two times "Limit has been reached"
    CounterUserOver cu2(9);
    cu2.IncrementBy(9);
    cout << "Just passing time" << endl;
    cu2.IncrementBy(1); //OUTPUT: "Limit has been reached"}
}