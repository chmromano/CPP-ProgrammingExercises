#include "Spy.h"

Spy::Spy(const char *name_, const char *alias_, const int resistance_) :
                                Person(name_), alias(alias_), resistance(resistance_) {
}

void Spy::set_identity(const char *alias_) {
    alias = alias_;
}

void Spy::identity() const {
    if (resistance == 0) {
        std::cout << "My name is: " << name << std::endl;
        // Person::identity(); Can use this if data members of Person class are private (here
        // I have set them as protected).
        std::cout << "My alias is: " << alias << std::endl;
    } else {
        std::cout << "My name is: " << alias << std::endl;
    }
}

void Spy::interrogate() {
    if (resistance > 0) resistance--;
}