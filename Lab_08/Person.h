#ifndef LAB_08_PERSON_H
#define LAB_08_PERSON_H


#include <iostream>
#include <string>

class Person {
public:
    Person(const char* name_ = "nobody");
    virtual ~Person() = default;
    virtual void identity() const;
    virtual void interrogate();
protected:
    std::string name;
};


#endif