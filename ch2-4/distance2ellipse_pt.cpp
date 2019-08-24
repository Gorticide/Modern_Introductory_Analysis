#include<iostream>
#include<cmath>

#include "Point.h"
#include "Ellipse.h"

using std::cout;
using std::cin;

Ellipse get_ellipse();

int main()  {
   double x1, y1;
   cout << "\nThis program will approximate the distance from a point to an ellipse.\n\n";
   cout << "Enter the coordinates x, y: ";
   cin >> x1 >> y1;
   Point p(x1, y1);
   Ellipse ellipse = get_ellipse();
         
   cout << "\nThe shortest distance between the point " << p << "\nand the ellipse with equation\n"  
        << ellipse << " is:\n  shortest distance =  " << ellipse.distance(p) << "\n\n";
}

Ellipse get_ellipse()  {
   int choice;

   cout << "\nWhich form is the equation of the ellipse? \n\n";
   cout << "\t\t(1) Ax^2 + By^2 = C : [A, B, and C]\n"
        << "\t\t(2) [x^2]/[a^2]+ [y^2]/[b^2] = 1 : [a^2 and b^2]\n\nEnter choice [1 or 2]: ";
   cin >> choice;

   switch(choice)   {
       case 1:
       {
         Real A, B, C;
         cout << "\nEnter the coefficients of the ellipse  Ax^2 + By^2 = C : [A, B, and C]\n\n"
              << "Enter [x^2]-coefficient, [y^2]-coefficient, and constant: ";
         cin >> A >> B >> C;
         Ellipse e(A, B, C);
         return e;
       }

       case 2:
       {
        Real a2, b2;
        cout << "For [x^2]/[a^2]+ [y^2]/[b^2] = 1 : [Enter a^2 and b^2]\n\n"
             << "Enter the squares as explained, not the square roots:   ";
        cin >> a2 >> b2;
        Ellipse e(a2, b2);
        return e;
       }
  }

}