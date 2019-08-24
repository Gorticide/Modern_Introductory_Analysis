// This is the file Point.h
#ifndef POINT_H
#define POINT_H

#include<iostream>
#include "Line.h"

typedef double Real;   //This means that Real is a synonym for double.

class Line;   // Declaration of class Line, which has not 
              // yet been defined. But we need to tell 
              // class Point that it exists because
              // class Point uses it.

class Point{
public:     // "public" means accessible to the outside 
            // world, i.e., the parts
            // of the program outside this class.

    Point();  // Declare a function Point() with no 
              // arguments.  This is actually a special 
              // function called a class constructor 
              // that creates an object of the class Point.

    Point(Real x, Real y);     // Constructor that creates an object using 
                               // the values x and y.
    
    Real distance(Point p);    // Member function that computes the distance 
                               // to another point from this point. It 
                               // returns a Real.
    
    Real distance(Line L);     // Member function that computes the distance 
                               // to a line.  
                               
    Real x();                  // Get x-coordinate of point.

    Real y();                  // Get y-coordinate of point.
    int operator==(const Point &other);
	friend std::ostream &operator<<(std::ostream &os, Point &p);

private:           // Accessible only to class objects.

    Real _x;       // x-coordinate.
    Real _y;       // y-coordinate.
};                 // Only place a ";" follows a bracket "}" after class definition



#endif