#ifndef LAB_08_SPY_H
#define LAB_08_SPY_H


#include "Person.h"

class Spy: public Person {
public:
    Spy(const char *name_, const char *alias_, int resistance_);
    void set_identity(const char *alias_);
    void identity() const override;
    void interrogate() override;
private:
    std::string alias;
    int resistance;
};


#endif