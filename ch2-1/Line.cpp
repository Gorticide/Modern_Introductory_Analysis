#include "Line.h"
#include<iostream>
#include<cmath>

Line::Line() {}

Line::Line(const Line &src)  {
    _A = src._A;
    _B = src._B;
    _C = src._C;
}

Line::Line(Point p1, Point p2)  {
    // Construct a Line through points p1 and p2.
    if (p1.x() == p2.x())  {      // Vertical line
        _A = 1;
        _B = 0;
        _C = -p1.x();
    }
    else  {
        _A = p2.y() - p1.y();
        _B = p1.x() - p2.x();
        _C = p1.y() * p2.x() - p2.y() * p1.x();
    }
}

Line::Line(Real a, Real b, Real c)  {
    _A = a;
    _B = b;
    _C = c;
}

Real Line::A() {
    return _A;
}

Real Line::B()  {
    return _B;
}

Real Line::C() {
    return _C;
}


Real Line::distance(Point point)   {       // Returns the distance from point to the line.
    return std::fabs(_A*point.x() + _B*point.y() + _C)/sqrt(_A*_A + _B*_B);
}

std::ostream &operator<<(std::ostream &os, Line &line)
{
      os << line._A << "*x";
      if (line._B < 0.0) os << " - ";
      else os << " + ";
      os << std::fabs(line._B) << "*y";
      if (line._C < 0.0) os << " - ";
      else os << " + ";
      os << std::fabs(line._C);
      os <<  " = 0  <===>  ";
      os << line._A << "*x";
      if (line._B < 0.0) os << " - ";
      else os << " + ";
      os << std::fabs(line._B) << "*y";
      os << " = ";
      if (line._C >= 0.0) os << " - ";
      os << std::fabs(line._C);
      
    return os;
}