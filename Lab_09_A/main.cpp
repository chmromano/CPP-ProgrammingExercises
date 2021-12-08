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

    Point(const Point &point_) : x(point_.x), y(point_.y) {};

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

    Circle(const Point &point_, double radius_ = 0.0) : Point(point_), radius(radius_) {};

    Circle(const Circle &circle_) : Point(circle_), radius(circle_.radius) {};

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

    Square(const Point &point_, double width_ = 0.0, double height_ = 0.0) :
            Point(point_), width(width_), height(height_) {};

    Square(const Square &square_) : Point(square_), width(square_.width), height(square_.height) {};

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

    vector<shared_ptr<Point>> vect;
    vect.push_back(make_shared<Point>(1.0, 1.0));
    vect.push_back(make_shared<Circle>(2.0, 2.0, 2.0));
    vect.push_back(make_shared<Square>(5.0, 5.0, 2.0, 2.0));

    shared_ptr<Point> p;

    p = make_shared<Point>();
    p->input("Point:");
    vect.push_back(p);

    p = make_shared<Circle>();
    p->input("Circle:");
    vect.push_back(p);

    p = make_shared<Square>();
    p->input("Square:");
    vect.push_back(p);

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