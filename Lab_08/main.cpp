#include <iostream>
#include <string>


// Person class --------------------------------------------------------------------------------------------------------

class Person {
public:
    Person(const char *name_ = "nobody");

    virtual ~Person() = default;

    virtual void identity() const;

    virtual void interrogate();

protected:
    std::string name;
};

Person::Person(const char *name_) : name(name_) {}

void Person::identity() const {
    std::cout << name << std::endl;
}

void Person::interrogate() {}


// Spy class -----------------------------------------------------------------------------------------------------------

class Spy : public Person {
public:
    Spy(const char *name_, const char *alias_, int resistance_);

    void set_identity(const char *alias_);

    void identity() const override;

    void interrogate() override;

private:
    std::string alias;
    int resistance;
};

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


// Main ----------------------------------------------------------------------------------------------------------------

int main(int argc, char **argv) {

    Person agent("James Bond");
    Spy spy("Emilio Largo", "William Johnson", 3);
    Spy spy2("Ernst Blofield", "John Keats", 5);

    std::cout << std::endl << "Nice to meet you. ";
    agent.identity();

    for (int i = 0; i < 6; ++i) {
        std::cout << "Who are you?" << std::endl;
        spy.interrogate();
        spy.identity();
    }
    spy.set_identity("Bill Munny");
    spy.identity();

    std::cout << std::endl << "Nice to meet you. ";
    agent.identity();

    for (int i = 0; i < 6; ++i) {
        std::cout << "Who are you?" << std::endl;
        spy2.interrogate();
        spy2.identity();
    }

    return 0;
}