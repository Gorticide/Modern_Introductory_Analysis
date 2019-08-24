// Introductory Analysis circa 1988 (Dolciani)
// Code by Mike Hentrich
// 2 February 2019
// Code for Computer Exercise page 52 


#include "Point.h"
#include "Line.h"

#include <iostream>
#include <cmath>

using std::cout;
using std::cin;


int main()  {
   double x1, y1, a, b, c;
   cout << "\nThis program will approximate the distance from a point to a nonvertical line.\n\n";
   cout << "Enter the coordinates x, y: ";
   cin >> x1 >> y1;
   Point p(x1, y1);
   cout << "\nEnter the coefficients of the line Ax + By + C = 0 (or Ax + By = -C)\n"
        << "Enter x-coefficient, y-coefficient, and constant: ";
   cin >> a >> b >> c;
   Line L(a, b, c);
   if (std::fabs(a - 0.0) < 0.00001 )   {   // This means "Is a == 0" ?
       cout << "\n\nThe distance is " << std::fabs(y1 + c);
   }  
   else {
       if (std::fabs(p.distance(L) - 0.0 < 0.00001)) cout << "\nThe point " << p << " is on the line " << L;
       else  
         cout << "\nThe shortest distance between the point " << p << "\nand the line with equation "  << L
              << " is " << p.distance(L);

   }
   cout << std::endl << std::endl;
}