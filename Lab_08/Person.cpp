#include "Person.h"

Person::Person(const char *name_): name(name_) {}

void Person::identity() const {
    std::cout << name << std::endl;
}

void Person::interrogate() {}