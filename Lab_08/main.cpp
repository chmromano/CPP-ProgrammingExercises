// Christopher Romano

#include <iostream>
#include <string>


// Person class --------------------------------------------------------------------------------------------------------

class Person {
public:
    Person(const char *name_ = "nobody") : name(name_) {};

    virtual ~Person() = default;

    virtual void identity() const { std::cout << "My name is: " << name << std::endl; };

    virtual void interrogate() {};

private:
    std::string name;
};


// Spy class -----------------------------------------------------------------------------------------------------------

class Spy : public Person {
public:
    Spy(const char *name_ = "nobody", const char *alias_ = "nobody", int resistance_ = 0) :
            Person(name_), alias(alias_), resistance(resistance_) {
    };

    void set_identity(const char *alias_) { alias = alias_; };

    void identity() const override {
        if (resistance == 0) {
            Person::identity();
            std::cout << "My alias is: " << alias << std::endl;
        } else {
            std::cout << "My name is: " << alias << std::endl;
        }
    };

    void interrogate() override { if (resistance > 0) resistance--; };

private:
    std::string alias;
    int resistance;
};


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