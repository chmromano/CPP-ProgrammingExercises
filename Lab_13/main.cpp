// Christopher Romano

#define _CRTDBG_MAP_ALLOC

#include <stdlib.h>
#include <crtdbg.h>
#include <iostream>
#include <memory>
#include <vector>
#include <string>
#include <algorithm>
#include <iterator>
#include <ctime>


// Car class -----------------------------------------------------------------------------------------------------------

class Car {
    friend std::ostream &operator<<(std::ostream &out, const Car &car) {
        std::cout << "Model: " << car.model << std::endl << "License: " << car.license << std::endl << "Mileage: "
                  << car.mileage << std::endl;

        return out;
    }

private:
    std::string model;
    std::string license;
    int mileage;
public:
    Car(const char *m = "Ford", const char *l = nullptr, int ml = 0) :
            model(m), license(l ? l : (rand() % 2 ? "FOO-" : "BAR-") + std::to_string(rand() % 999 + 1)),
            mileage(ml ? ml : rand() % 10000) {}

    ~Car() {
        std::cout << model << " " << license << " deleted" << std::endl;
    }

    void Read() {
        //std::cout << "Enter car information" << std::endl;
        // replace the following with your own code
        model = "Seat";
        license = (rand() % 2 ? "ZAP-" : "ZIP-") + std::to_string(rand() % 999 + 1);
        mileage = 10000 + rand() % 10000;
    }

    std::string GetLicense() const {
        return license;
    }
};


// Website class -------------------------------------------------------------------------------------------------------

class Website {
private:
    std::string name;
    std::vector<std::weak_ptr<Car>> listing;
public:
    Website(const char *n = nullptr) : name(n ? n : "www.cars" + std::to_string(rand() % 99 + 1) + ".com") {}

    ~Website() {
        std::cout << name << " deleted" << std::endl;
    }

    void advertise(const std::weak_ptr<Car> &car) {
        listing.push_back(car);
    }

    void print(std::ostream &out = std::cout) {

        listing.erase(std::remove_if(listing.begin(), listing.end(),
                                     [](std::weak_ptr<Car> &c) { return c.expired(); }), listing.end());

        out << name << std::endl;
        for (const auto &car: listing) out << *car.lock();
        out << name << " end of list" << std::endl;
    }
};


// Dealer class --------------------------------------------------------------------------------------------------------

class Dealer {
    friend std::ostream &operator<<(std::ostream &out, const Dealer &dealer) {
        std::cout << dealer.name << "'s cars for sale" << std::endl;
        for (auto car: dealer.cars) std::cout << *car;
        std::cout << "End of " << dealer.name << "'s cars listing" << std::endl;
        return out;
    }

private:
    std::string name;
    std::vector<std::shared_ptr<Car>> cars;
    std::vector<std::shared_ptr<Website>> sites;
public:
    Dealer(const char *name_ = "John Doe") : name(name_) {};

    ~Dealer() {
        std::cout << name << " deleted" << std::endl;
    };

    void buy() {
        std::shared_ptr<Car> car = std::make_shared<Car>();
        car->Read();
        add(car);
    }

    void sell() {
        std::cout << *this;
        std::cout << "Enter license of car you want to buy" << std::endl;

        std::string license;
        std::cin >> license;

        auto ci = std::find_if(cars.begin(), cars.end(), [&license](const std::shared_ptr<Car> &c) {
            return license == c->GetLicense();
        });

        if (ci != cars.end()) {
            cars.erase(ci);
        }
    }

    void add(const std::shared_ptr<Car> &car) {
        cars.push_back(car);
        for (const auto &site: sites) {
            site->advertise(car);
        }
    }


    void add_site(const std::shared_ptr<Website> &w) {
        sites.push_back(w);
    }
};


// Main ----------------------------------------------------------------------------------------------------------------

void car_sales() {
    std::cout << "Car sales started" << std::endl;

    auto wa = std::make_shared<Website>("www.autos.com");
    auto wb = std::make_shared<Website>("www.bilar.com");
    auto wc = std::make_shared<Website>("www.cars.com");

    auto a = std::make_shared<Dealer>("Alan Aldis");
    auto b = std::make_shared<Dealer>("Bill Munny");

    {
        auto c = std::make_shared<Dealer>("Casey Ball");

        auto ca = std::make_shared<Car>();
        auto cb = std::make_shared<Car>();

        a->add_site(wa);
        a->add_site(wb);
        b->add_site(wb);
        b->add_site(wc);
        c->add_site(wa);
        c->add_site(wb);
        c->add_site(wc);

        a->buy();
        a->buy();
        a->buy();
        a->buy();

        b->buy();
        b->buy();
        b->buy();

        c->buy();
        c->buy();
        c->add(ca);
        c->add(cb);

        wa->print();
        wb->print();
        wc->print();

        std::cout << *a << *b << *c << std::endl;

        a->sell();

        std::cout << *a << *b << *c << std::endl;

        wa->print();
        wb->print();
        wc->print();
    }

    wa->print();
    wb->print();
    wc->print();

    std::cout << "Car sales ended" << std::endl;
}

int main(int argc, char **argv) {
    _CrtMemState s1;
    _CrtMemCheckpoint(&s1);

    srand(time(nullptr));

    car_sales();

    _CrtMemState s2, s3;
    _CrtMemCheckpoint(&s2);
    if (_CrtMemDifference(&s3, &s1, &s2)) {
        _CrtDumpMemoryLeaks();
        _CrtMemDumpStatistics(&s3);
    }

    return 0;
}