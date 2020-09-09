//
// Created by caleb on 8/16/20.
//

// Polymorhpic members
#include <iostream>

class Polygon {
protected:
    int width, height;
public:
    Polygon (int a, int b) : width(a), height(b) {}
    virtual int area() =0;
    void printarea() { std::cout << this->area() << '\n'; }
};

class Rectangle: public Polygon {
public:
    Rectangle(int a,int b) : Polygon(a,b) {}
    int area() { return width*height; }
};

class Triangle: public Polygon {
public:
    Triangle(int a,int b) : Polygon(a,b) {}
    int area() { return width*height/2; }
    void triFunc() { std::cout << "I am a triangle\n"; }
};

class C {
public:
    Polygon&& polygon;
};

int main1() {
    C c1{ Triangle(6, 6) };
    std::cout << c1.polygon.area() << '\n';
    //c1.polygon.triFunc(); does not work
    reinterpret_cast<Triangle*>(&c1.polygon)->triFunc();
    C c2{ Rectangle(6, 6) };
    std::cout << c2.polygon.area() << '\n';
    return 0;
}