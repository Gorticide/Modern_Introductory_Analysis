#include <iostream>
#include <cmath>


int main()  {

  // 1e-12 limits subdivision size, h, to 0.000001 (1e-06)
  double acceptedDiff = 1e-12;
  int degree, t;
  int coefficient;
  double x, x1, x2; // endpoints of interval to be searched
  double h;  // subdivision size
  double y, y1 = 0;

  std::cout << "\nWhat is the degree of your polynomial? ";
  std::cin >> degree;

  int *P = new int[degree + 1];

  for (int j = degree; j >= 1; j--) {
    std::cout << "coefficient of x^" << j << ": ";
    std::cin >> coefficient;
    P[j] = coefficient;
  }
  std::cout << "\nconstant term: ";
  std::cin >> coefficient;
  P[0] = coefficient;
  std::cout << "\nendpoints of interval to be searched: ";
  std::cin >> x1 >> x2;
  std::cout << "\nsubdivision size (minimum: 0.000001 == 1e-06): ";
  std::cin >> h;

  t = 0;

  for (double x = x1; x < x2+h/2; x+=h)  {
    y = P[degree];
    for (int j = degree; j >= 1; j--)  {
      // std::cout << y << " * " << x << " + " << P[j - 1];
      y = y*x + P[j - 1];  // synthetic division
     // std::cout << " = " << y << "\n";
    }

    if ( fabs(y - 0.0) > acceptedDiff )  {  // if y != 0
      if ( ( fabs(y*y1 - 0.0) < acceptedDiff )  || (y*y1 > 0.0)  )  {
            y1 = y;
          }
      else
       if (y*y1 < 0)  {
        std::cout << "\nThere is a zero between " << x - h
                  << " and " << x << ".\n";
        y1 = y;
        t = 1;
      }
    }
    else {
      std::cout << "\n" << x << " is a zero.\n";
      t = 1;
      y1 = y;
    }
  }
  if (t == 0)  {
    std::cout << "\nNo zeros found.\n\n";
  }
  else std::cout << "\n\n";

  delete [] P;
}
