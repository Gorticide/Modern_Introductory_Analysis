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

Line getline();

int main()  {
   double x1, y1;
   cout << "\nThis program will approximate the distance from a point to a nonvertical line.\n\n";
   cout << "Enter the coordinates x, y: ";
   cin >> x1 >> y1;
   Point p(x1, y1);
   Line L = getline();

   if (std::fabs(L.A() - 0.0) < 0.00001 )   {   // This means "Is a == 0" ?
       cout << "\n\nThe distance is " << std::fabs(y1 + L.C());
   }  
   else {
       if (std::fabs(p.distance(L) - 0.0 < 0.00001)) cout << "\nThe point " << p << " is on the line " << L;
       else  
         cout << "\nThe shortest distance between the point " << p << "\nand the line with equation "  << L
              << " is " << p.distance(L);

   }
   cout << std::endl << std::endl;
}

Line getline()  {
   char choice;
   double a, b, c;

   cout << "\nDo you have the equation of the line or the coordinates of two points?\n\n";
   cout << "\t\t(L) Coefficients A, B, C for line Ax + By + C = 0\n"
        << "\t\t(P) Coordinates for 2 points\n\nEnter choice [L or P]: ";
   cin >> choice;

   switch(choice)   {
       case 'L': case 'l':
       {
         cout << "\nEnter the coefficients of the line Ax + By + C = 0 (or Ax + By = -C)\n"
              << "Enter x-coefficient, y-coefficient, and constant: ";
         cin >> a >> b >> c;
         Line L(a, b, c);
         return L;
       }

       case 'P': case 'p':
       {
        double x1, y1;
        cout << "Enter the coordinates x1, y1: ";
        cin >> x1 >> y1;
        Point r(x1, y1);
        cout << "\nEnter the coordinates x2, y2: ";
        cin >> x1 >> y1;
        Point s(x1, y1);
        Line L(r, s);
        return L;
       }
  }

}