// Christopher Romano

#include <iostream>
#include <vector>
#include <memory>

using namespace std;

// Point class ---------------------------------------------------------------------------------------------------------

class Point {
private:
    double x;
    double y;
public:
    Point(double x_coord = 0.0, double y_coord = 0.0) : x(x_coord), y(y_coord) {};

    virtual ~Point() = default;

    virtual void input(const char *prompt) {
        cout << prompt << endl;
        cout << "Enter X: ";
        cin >> x;
        cout << "Enter Y: ";
        cin >> y;
    };

    virtual void output() const {
        cout << "Coordinates: (" << x << "," << y << ")" << endl;
    };

    virtual double area() const { return 0.0; };

    void move(double delta_x, double delta_y) {
        x += delta_x;
        y += delta_y;
    };
};


// Circle class --------------------------------------------------------------------------------------------------------

class Circle : public Point {
private:
    double radius;

public:
    Circle(double x_coord = 0.0, double y_coord = 0.0, double radius_ = 0.0) :
            Point(x_coord, y_coord), radius(radius_) {};

    void input(const char *prompt) override {
        Point::input(prompt);
        cout << "Enter radius: ";
        cin >> radius;
    };

    void output() const override {
        cout << "Circle's area: " << area() << " ";
        Point::output();
    };

    double area() const override { return pi * radius * radius; };

    // Circle(const Point &point_, double radius_ = 0.0) : Point(point_), radius(radius_) {}; TEST

    static const double pi;
};

const double Circle::pi = 3.14159265359;


// Square class --------------------------------------------------------------------------------------------------------

class Square : public Point {
private:
    double width;
    double height;
public:
    Square(double x_coord = 0.0, double y_coord = 0.0, double width_ = 0.0, double height_ = 0.0) :
            Point(x_coord, y_coord), width(width_), height(height_) {};

    void input(const char *prompt) override {
        Point::input(prompt);
        cout << "Enter width: ";
        cin >> width;
        cout << "Enter height: ";
        cin >> height;
    };

    void output() const override {
        cout << "Square's area: " << area() << " ";
        Point::output();
    };

    double area() const override { return width * height; };
};


// Main ----------------------------------------------------------------------------------------------------------------

void print(const vector<shared_ptr<Point>> &v);

int main() {

    srand(time(nullptr));

    vector<shared_ptr<Point>> vect;

    for (int i = 0; i < 5; i++) {
        shared_ptr<Point> p;
        int rnd = rand() % 3;
        if (rnd == 0) {
            p = make_shared<Point>();
            p->input("Point:");
        } else if (rnd == 1) {
            p = make_shared<Circle>();
            p->input("Circle:");
        } else if (rnd == 2) {
            p = make_shared<Square>();
            p->input("Square:");
        }
        vect.push_back(p);
    }

    print(vect);

    sort(vect.begin(), vect.end(),
         [](const shared_ptr<Point> &p1, const shared_ptr<Point> &p2) { return p1->area() < p2->area(); });

    cout << "Sorted:" << endl;
    print(vect);

    return 0;
}

void print(const vector<shared_ptr<Point>> &v) {
    for (auto &p: v) {
        p->output();
    }
}