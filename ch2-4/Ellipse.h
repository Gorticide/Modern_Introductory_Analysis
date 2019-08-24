// This is the file Ellipse.h
#ifndef ELLIPSE_H
#define ELLIPSE_H

#include<iostream>

typedef double Real;   //This means that Real is a synonym for double.
class Point;

class Ellipse {
     public:     // "public" means accessible to the outside 
                 // world, i.e., the parts
                 // of the program outside this class.

    Ellipse();  // Declare a function Ellipse() with no 
              // arguments.  This is actually a special 
              // function called a class constructor 
              // that creates an object of the class Ellipse.

    Ellipse(Real a2, Real b2);     // Constructor that creates an object using 
                                   // the values a2 and b2.

   
    Ellipse(Real A, Real B, Real C);   // Ax^2 + By^2 = C
    
    Real distance(Point p);    // Member function that computes the shortest distance 
                               // between the ellipse and a point. It returns a Real.

    Real a();
    Real b();
    Real c();
    Real A();
    Real B();
    Real C();

    friend std::ostream &operator<<(std::ostream &os, Ellipse &e);

    private:
      Real _a;   // [x^2]/[_a^2] + [y^2]/[_b^2] = 1
      Real _b;
      Real _c;   // c^2 = a^2 - b^2
      Real _A;
      Real _B;
      Real _C;
      int hcf(int p, int q, int r);
      int lcm(int x, int y, int z);
};

#endif