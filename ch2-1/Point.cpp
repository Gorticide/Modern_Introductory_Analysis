#include<iostream>
#include<cmath>

#include "Point.h"

Point::Point()                // Scope resolutin operator ::
    {}                        // constructor does nothing

Point::Point(Real x, Real y)  {
    _x = x;                        // Member function has access to private members
    _y = y;
}

Real Point::x() {
    return _x;
}

Real Point::y()  {
    return _y;
}

Real Point::distance(Point p)  {
   Real dx = _x - p._x;         // _x refers to the _x of "this" object 
   Real dy = _y - p._y;         // p._y refers to the _y of the other object p.
                                 // Notice access of the private data member 
                                 // p._y by another object of the same class.
   return std::sqrt(dx*dx + dy*dy);
}

Real Point::distance(Line L)  {
    return L.distance(*this);      //  Let Line do the work. 
}

int Point::operator==(const Point &other)
{
    return (_x == other._x && _y == other._y);
}

std::ostream &operator<<(std::ostream &os, Point &p)
{
      os << '(';
      os << p._x;
      os << ", " << p._y << ')';
    return os;
}