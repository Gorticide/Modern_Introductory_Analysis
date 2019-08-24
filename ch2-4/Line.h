#ifndef LINE_H
#define LINE_H

#include<iostream>
#include "Point.h"

typedef double Real;

class Point;
class Line {
public:
    Line();
    Line(const Line &src);    // copy constructor
    Line(Point p1, Point p2);                        // Line through 2 points 
    //Line(Point p, Real xdir, Real ydir);             // Line through p with tangent (x,y) 
    Line(Real a, Real b, Real c);
    //Point intersect(Line line); 
    Real distance(Point p); 

    Real A();                                 // Get coefficient of x
    Real B();                                 // Get coefficient of y
    Real C();                                 // Get constant
    friend std::ostream &operator<<(std::ostream &os, Line &line);

private:
    Real _A;                                          // Ax + By + C = 0
    Real _B;
    Real _C;
};

#endif