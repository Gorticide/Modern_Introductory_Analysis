    /* AtoG.cpp and mystuff.h by Nikolai Chernov,  February 2012

        The code in this file written by Michael William Hentrich
        February 2019
        */

#include <iostream>
#include <cmath>
#include <iomanip>
#include <vector>
#include <eigen3/Eigen/Dense>
#include <eigen3/Eigen/Eigenvalues>
#include <istream>  // to use cin.get() so as to use function "pause"
#include <limits>

#include "mystuff.h"            // Nikolai Chernov
#include "AtoG_modified.cpp"    // Chernov, then modified by Hentrich

typedef long double reals;
typedef long long integers;

typedef Matrix<reals, 6, 1> M6x1;
typedef Matrix<reals, 5, 1> M5x1;

using namespace std;
using namespace Eigen;

const reals PI = acos(-1);
const reals radians = PI/180.0;
const reals degrees = 180.0/PI;

void my_pause();
void display_equation(reals A, reals B, reals C, reals D, reals E, reals F);

int main()   {
  int code;
  M6x1 A;
  M5x1 ParG;
  char sign = '+';
  reals nA, nB, nC, nD, nE, nF;
  reals c;
  reals den_first, den_second, val_first, val_second;
  char first, second, sign_first, sign_second;

cout << "\nConversion of Algebraic parameters of a conic to its Geometric parameters\n"
     << "Algebraic parameters are coefficients A,B,C,D,E,F in the algebraic\n"
     //<< "equation     Ax^2 + 2Bxy + Cy^2 + 2Dx + 2Ey + F = 0\n\n"
     << "equation     Ax^2 + Bxy + Cy^2 + Dx + Ey + F = 0\n\n"
     << "Enter A B C D E F: ";
cin >> nA >> nB >> nC >> nD >> nE >> nF;
A(0) = nA;
A(1) = nB/(double)2;
A(2) = nC;
A(3) = nD/(double)2;
A(4) = nE/(double)2;
A(5) = nF;

AtoG_modified(A,ParG,code);                       //   determine the conic type
if (code>3) {                            //   degenerate conic
     cout << "degenerate conic ------> ";
     if (code == 4) cout << "intersecting lines\n\n";
     if (code == 5) cout << "parallel lines\n\n";
     if (code == 6) cout << "coincident lines\n\n";
     if (code == 7) cout << "single line\n\n";
     if (code == 8) cout << "single point\n\n";
     if (code == 9) cout << "imaginary ellipse\n\n";
     if (code == 10) cout << "imaginary parallel lines\n\n";
     if (code == 11) cout << "impossible equation, 1=0 or -1=0 (no solutions)\n\n";
   }


if (code==1)  {

    if (fabs(nA) >= fabs(nC)) { // y^2/(nA) + x^2/nC = 0
       first = 'y';
       val_first = ParG(1);
       den_first = nA;
       if (ParG(1) < 0) sign_first = '+';
       else sign_first = '-';
       second = 'x';
       val_second = ParG(0);
       den_second = nC;
       if (ParG(0) < 0) sign_second = '+';
       else sign_second = '-';
    }
    else {         // x^2/(nC) + y^2/nA
       first = 'x';
       val_first = ParG(0);
       den_first = nC;
       if (ParG(0) < 0) sign_first = '+';
       else sign_first = '-';
       second = 'y';
       val_second = ParG(1);
       den_second = nA;
       if (ParG(1) < 0) sign_second = '+';
       else sign_second = '-';
    }

   cout << "\nEllipse\n\n";    //  ellipse
   //cout << ParG << "\n\n";
   cout << "Algebraic to Geometric INTERPRETATION:\n\n"
        << "center: (" << ParG(0) << ", " << ParG(1) << ")\n\n"
        << "equation:    ";
   if (std::fabs(val_first - 0.0) < 0.000001)
      cout << '(' << first << "^2)/[";
   else {
     if (val_first > 0) sign = '-';
     cout << "[(" << first << ' ' << sign << ' ' << fabs(val_first) << ")^2]/[";
   }
   cout << ParG(2)*ParG(2) << "] + ";
   sign = '+';
   if (std::fabs(val_second - 0.0) < 0.000001)
      cout << '(' << second << "^2)/[";
   else {
     if (ParG(1) > 0) sign = '-';
     cout << "[(" << second << ' ' << sign << ' ' << fabs(val_second) << ")^2]/[";
   }
   cout << ParG(3)*ParG(3) << "] = 1\n\n";
   sign = '+';

  c = sqrt(ParG(2)*ParG(2) - ParG(3)*ParG(3));
  cout << "Foci: (";
   if (first == 'x') {
       cout << ParG(0) - c << ", " << ParG(1) << ") and ("
            << ParG(0) + c << ", " << ParG(1) << ")\n\n";
   }
   else {
     cout << ParG(0) << ", " << ParG(1) - c << ") and ("
          << ParG(0) << ", " << ParG(1) + c << ")\n\n";
   }
   cout << "Vertices of Major Axis:  (";
   if (first == 'x') {
       cout << ParG(0) - ParG(2) << ", " << ParG(1) << ") and ("
            << ParG(0) + ParG(2) << ", " << ParG(1) << ")\n\n";
   }
   else {
     cout << ParG(0) << ", " << ParG(1) - ParG(2) << ") and ("
          << ParG(0) << ", " << ParG(1) + ParG(2) << ")\n\n";
   }
   cout << "Endpoints of Minor Axis:  (";
   if (second == 'x') {
       cout << ParG(0) - ParG(3) << ", " << ParG(1) << ") and ("
            << ParG(0) + ParG(3) << ", " << ParG(1) << ")\n\n";
   }
   else {
     cout << ParG(0) << ", " << ParG(1) - ParG(3) << ") and ("
          << ParG(0) << ", " << ParG(1) + ParG(3) << ")\n\n";
   }
   cout << "Eccentricity e = " << c/ParG(2) << "\n\n";
   if (fabs(c/ParG(2) - 0.0) < 0.000001)  {
     cout << "This ellipse is actually a circle.\n"
          << "We can write equation in the following form:\n\n";
          sign = '+';
          if (std::fabs(val_first - 0.0) < 0.000001)
             cout << '(' << first << "^2)";
          else {
            if (val_first > 0) sign = '-';
            cout << "(" << first << ' ' << sign << ' ' << fabs(val_first) << ")^2";
          }
          cout << " + ";
          sign = '+';
          if (std::fabs(val_second - 0.0) < 0.000001)
             cout << '(' << second << "^2)";
          else {
            if (ParG(1) > 0) sign = '-';
            cout << "(" << second << ' ' << sign << ' ' << fabs(val_second) << ")^2";
          }
          cout << " = " << ParG(2)*ParG(2)
               << "\nwhere we can see by inspection that the radius is ";
          if (ParG(2) == ParG(3)) cout << ParG(3) << "\n\n";
          else cout << "error?";
       }
 }

if (code==2)  {

  if (nC < 0)  {
    first = 'x';
    second = 'y';
  }
  else
  {
    first = 'y';
    second = 'x';
  }
  cout << "\nHyperbola\n\n";  // hyperbola
  //cout << ParG << "\n\n";
  cout << "Algebraic to Geometric INTERPRETATION:\n\n"
       << "center: (" << ParG(0) << ", " << ParG(1) << ")\n\n"
       << "equation:   ";
       if (std::fabs(ParG(0) - 0.0) < 0.000001)
          cout << '(' << first << "^2)/[";
       else {
         if (ParG(0) > 0) sign = '-';
         cout << "[(" << first << ' ' << sign << ' ' << fabs(ParG(0)) << ")^2]/[";
       }
       cout << ParG(2)*ParG(2) << "] - ";
       sign = '+';
       if (std::fabs(ParG(1) - 0.0) < 0.000001)
          cout << '(' << second << "^2)/[";
       else {
         if (ParG(1) > 0) sign = '-';
         cout << "[(" << second << ' ' << sign << ' ' << fabs(ParG(1)) << ")^2]/[";
       }
       cout << ParG(3)*ParG(3) << "] = 1\n\n";
       sign = '+';

       if (fabs(nB - 0.0) < 0.00001)
       {
         if (first = 'x')
             cout << "Horizontal ";
         else cout << "Vertical ";
         cout << "Transverse Axis with vertices (";
         if (first = 'x') {
           cout << ParG(0) - ParG(2) << ", " << ParG(1) << ") and ("
                << ParG(0) + ParG(2) << ", " << ParG(1) << ")\n\n";
         }

         else {
           cout << ParG(0) << ", " << ParG(1) - ParG(3) << ") and ("
                << ParG(0) << ", " << ParG(1) + ParG(3) << ")\n\n";
          }

          c = sqrt(ParG(2)*ParG(2) + ParG(3)*ParG(3));
          cout << "Foci: (";
           if (first == 'x') {
               cout << ParG(0) - c << ", " << ParG(1) << ") and ("
                    << ParG(0) + c << ", " << ParG(1) << ")\n\n";
           }
           else {
             cout << ParG(0) << ", " << ParG(1) - c << ") and ("
                  << ParG(0) << ", " << ParG(1) + c << ")\n\n";
           }
        cout << "Asymptotes: \n";
        if (first == 'x')  {
          cout << "y = [" << ParG(3)/ParG(2) << "]x + ["
               << -ParG(0)*(ParG(3)/ParG(2)) + ParG(1)
               << "] and y = [" << -ParG(3)/ParG(2) << "]x + ["
               << ParG(0)*(ParG(3)/ParG(2)) + ParG(1) << "]\n\n";
        }
        else {
          cout << "y = [" << ParG(2)/ParG(3) << "]x + ["
               << -ParG(0)*(ParG(2)/ParG(3)) + ParG(1)
               << "] and y = [" << -ParG(2)/ParG(3) << "]x + ["
               << ParG(0)*(ParG(2)/ParG(3)) + ParG(1) << "]\n\n";
         }
       }
       cout << "Eccentricity e = " << c/ParG(2) << "\n\n";
   }

   if (code==3)
  {
     cout << "\nParabola\n\n";   //  parabola
     //cout << ParG << "\n\n";
     cout << "Algebraic to Geometric INTERPRETATION:\n\n"
          << "Vertex: (" << ParG(0) << ", " << ParG(1) << ")\n\n";
     c = ParG(2)/2;
     if (A(2) == 0 && A(0) != 0)   {
          cout << "Focus: (" << ParG(0) << ", " << ParG(1) + c << ")\n"
               << "VERTICAL Axis of Symmetry x = " << ParG(0) << "\n"
               << "HORIZONTAL Directrix y = " << ParG(1) - c << "\n\n";
          if (c > 0) cout << "The parabola opens upward with equation:\n\n";
          else cout << "The parabola opens downward with equation:\n\n";
          cout << "y ";
          if (ParG(1) < 0) sign = '+';
          else sign = '-';
          cout << sign << ' ' << fabs(ParG(1)) << " = [1/" << 4*c << "] (x ";
          if (ParG(0) < 0) sign = '+';
          else sign = '-';
          cout << sign << ' ' << fabs(ParG(0)) << ")^2, or\n"
               << "y = " << "[" << 1/(4*c) << "]x^2 + [" << (1/(4*c))*(-2*ParG(0))
               << "]x + [" << (1/(4*c))*(4*c*ParG(1)+ParG(0)*ParG(0)) << "]\n\n";

     }
     else {
            cout << "Focus: (" << ParG(0) + c << ", " << ParG(1) << ")\n"
                 << "HORIZONTAL Axis of Symmetry y = " << ParG(1) << "\n"
                 << "VERTICAL Directrix x = " << ParG(0) - c << "\n\n";
            if (c > 0) cout << "The parabola opens to the right with equation:\n\n";
            else cout << "The parabola opens to the left with equation:\n\n";
            cout << "x ";
            if (ParG(0) < 0) sign = '+';
            else sign = '-';
            cout << sign << ' ' << fabs(ParG(0)) << " = [1/" << 4*c << "] (y ";
            if (ParG(1) < 0) sign = '+';
            else sign = '-';
            cout << sign << ' ' << fabs(ParG(1)) << ")^2, or\n"
                 << "x = " << "[" << 1/(4*c) << "]y^2 + [" << (1/(4*c))*(-2*ParG(1))
                 << "]y + [" << (1/(4*c))*(4*c*ParG(0)+ParG(1)*ParG(1)) << "]\n\n";
     }
     cout << "Eccentricity e = 1 \n\n";
   }

   if (code == 4)  {
      cout << "The degenerate form of a hyperbola is two intersecting lines.\n"
           << "At the vertex of the cone, r = 0. The slopes of the intersecting lines\n"
           << "are m = ±b/a, because b corresponds to the y portion of the equation,\n"
           << "and  a corresponds to the x portion of the equation.\n\n";

      reals u, v, d, e, x, y, a, b;

      // (cos(u)*x+sin(u)*y+d)*(cos(v)*x+sin(v)*y+e) = 0
      //             u,v are directional angles of the lines
      //             d,e are distances from the origin (0,0) to the lines
      // ParG = [u,d,v,e]'
      u = ParG(0);
      d = ParG(1);
      v = ParG(2);
      e = ParG(3);
      my_pause();
      cout << "canonical equation:\n"
           << "(cos(" << u*degrees << ")*x + sin(" << u*degrees
           << ")*y + [" << d << "])\n * (cos(" << v*degrees
           << ")*x + sin(" << v*degrees << ")*y + [" << e << "]) = 0\n\n"
           << '(' << cos(u) << "*x + " << sin(u)
           << "*y + [" << d << "]) * (" << cos(v)
           << "*x + " << sin(v) << "*y + [" << e << "]) = 0\n\n"
           << "Therefore,\n\t"
           << cos(u) << "*x + " << sin(u)
           << "*y + [" << d << "] = 0 and \n\t" << cos(v)
           << "*x + " << sin(v) << "*y + [" << e << "] = 0\n\n";

     x = (-e/sin(v) + d/sin(u))/(-cos(u)/sin(u) + cos(v)/sin(v));
     y = (-cos(u)/sin(u))*x - d/sin(u);

     cout << "Setting y = y, and solving for x, we have x = " << x
          << "\nthen substituting " << x << " for x in either equation,\n"
          << "then solving for y, we have y = " << y << "\n\n";

     my_pause();
     cout << "\nIf you complete the squares for the general equation,\n";
     display_equation(nA, nB, nC, nD, nE, nF);
     cout << ",\nyou can factor the difference of squares to derive:\n";

     cout << "y = [" << -cos(u)/sin(u) << "]*x";
     if (-d/sin(u) < 0) cout << "- " << fabs(-d/sin(u));
     else cout << " + " << -d/sin(u);
     cout << " and y = [" << -cos(v)/sin(v) << "]x";
     if (-e/sin(v) < 0) cout << "- " << fabs(-e/sin(v));
     else cout << " + " << -e/sin(v);
     cout << "\n\n";

     b = fabs(cos(u));
     a = fabs(sin(u));

     cout << "Note that |cos(" << u << ")| = |" << cos(u) << "| = " << fabs(cos(u))
          << "\nand |cos(" << v << ")| = |" << cos(v) << "| = " << fabs(cos(v))
          << "\n\nSimilarly, "
          << "sin(" << u << ")| = |" << sin(u) << "| = " << fabs(sin(u))
          << "\nand |sin(" << v << ")| = |" << sin(v) << "| = " << fabs(sin(v))
          << "\n\nThe slopes of the lines are " << b/a << " and " << -b/a
          << endl << endl;
    my_pause();

    cout << "\nWe can extract the actual components b^2 and a^2 with brute force:\n"
          << "\nPoint of intersection: (" << x << ", " << y << ")\n\n"
          << "equation:   ";

    reals den_first, den_second, val_first, val_second;
    char sign_first, sign_second;

    if (nC < 0) {  // x^2/(-nC) - y^2/nA = 0
       first = 'x';
       val_first = x;
       den_first = -nC;
       if (x < 0) sign_first = '+';
       else sign_first = '-';
       second = 'y';
       val_second = y;
       den_second = nA;
       if (y < 0) sign_second = '+';
       else sign_second = '-';
    }
    else {         // y^2/(-nA) - x^2/nC
       first = 'y';
       val_first = y;
       den_first = -nA;
       if (y < 0) sign_first = '+';
       else sign_first = '-';
       second = 'x';
       val_second = x;
       den_second = nC;
       if (x < 0) sign_second = '+';
       else sign_second = '-';
    }

// I do not want to print zeros:
   if (std::fabs(val_first - 0.0) < 0.000001)
                  cout << '(' << first << "^2)/";
   else  {
         cout << "[(" << first << ' ' << sign_first << ' '
              <<  val_first << ")^2]/";
   }
   cout << den_first << " - ";
   if (std::fabs(val_second - 0.0) < 0.000001)
         cout << '(' << second << "^2)/";
   else {
        cout << "[(" << second << ' ' << sign_second << ' '
             <<  val_second << ")^2]/";
   }
   cout << den_second << " = 0 \n\n";

 }

   if ((code == 5) || (code == 7) )  {
        cout << "The degenerate form of a parabola is a line or two parallel lines.\n\n";

    }

   if (code == 5)  {
         cout << "The graph of the equation ";
         display_equation(nA, nB, nC, nD, nE, nF);
         cout << " is two parallel lines.\n\n";
         cout << "The equations of the two parallel lines are: \n\n";
         if (fabs(nA - 0.0) < 0.00001)  {
           cout << "y = " << (-nE + sqrt(nE*nE - 4*nC*nF))/(2*nC)
                << " and y = " << (-nE - sqrt(nE*nE - 4*nC*nF))/(2*nC);
         }
         else {
           cout << "x = " << (-nD + sqrt(nD*nD - 4*nA*nF))/(2*nA)
                << " and x = " << (-nD - sqrt(nD*nD - 4*nA*nF))/(2*nA);
         }
         cout << endl << endl;
   }

   if (code == 6)  {
     cout << "Coincident lines lie one on top of the other.\n\n";
     cout << "The graph of the equation ";
     display_equation(nA, nB, nC, nD, nE, nF);
     cout << " is two coincident lines.\n\n";
     cout << "The equation of both lines is:   ";
     if (fabs(nA - 0.0) < 0.00001)
       cout << "y = " << -nE/(2*nC);
     else
       cout << "x = " << -nD/(2*nA);
    cout << endl << endl;
   }

   if (code == 7)  {

            cout << "For this conic section, the coefficients A = B = C = 0 in the general equation.\n"
                 << "Thus, the resulting general equation is of the form Dx + Ey + F = 0\n\n";
            cout << "In this case, the equation is ";
            display_equation(nA, nB, nC, nD, nE, nF);

            cout << "\n\nThe graph is a single line with the equation y = ";
            if (fabs(-nD/nE - 0.0) < 0.00001) {}  // do not display x variable when coefficient is 0
            else cout << '[' << -nD/nE << "]*x ";
            if (-nF/nE < 0) sign = '-';
            else sign = '+';
            cout << sign << ' ' << fabs(-nF/nE) << "\n\n";
   }

   if (code == 8)  {
    reals val_first, val_second;
    char sign_first, sign_second;
       cout << "The degenerate form of a circle or an ellipse is a singular point.\n"
            << "At the vertex of the cone, the radius is 0, r = 0.\n\n";

     cout << "If you complete the squares for the general equation,\n";
     display_equation(nA, nB, nC, nD, nE, nF);
     //  Ax^2 + 2Bxy + Cy^2 + 2Dx + 2Ey + F = 0
     // We must multiply ParAin(1), ParAin(3), and ParAin(4) by 2
     if (ParG(0) < 0) {
         val_first = fabs(ParG(0));
         sign_first = '+';
     }
     else {
         val_first = ParG(0);
         sign_first = '-';
     }
     if (ParG(1) < 0) {
         val_second = fabs(ParG(1));
         sign_second = '+';
     }
     else {
         val_second = ParG(1);
         sign_second = '-';
     }
     cout << ",\n\nyou will find that the derived equation is:\n\n";
     if (fabs(val_first - 0.0) < 0.000001) cout << "[x^2]/";
     else {
       cout << "[(x " << sign_first << ' ' <<  val_first << ")^2]/";
     }
     cout << ParG(2)*ParG(2) << " + ";
     if (fabs(val_second - 0.0) < 0.000001) cout << "[y^2]/";
     else {
       cout << "[(y " << sign_second << ' ' <<  val_second << ")^2]/";
     }
     cout << ParG(3)*ParG(3) << " = 0 \n\n"
          << "Since the sum of two squares is 0 only when each square is 0,\n"
          << "the graph is the point (" << ParG(0) << ", " << ParG(1) << ").\n\n";
  }
   if (code == 9)  {
       cout << "Since sum of squares cannot be negative for real numbers,\n"
            << "the equation is not satisfied for any pair of real numbers.\n"
            << "Therefore, in R^2, the graph is the empty set.\n\n";
   }

   if (code == 10) {
     reals val;
     if (fabs(nA - 0.0) < 0.00001)  {
       val = nE/(2*nC);
       if (val < 0) sign = '-';
       if (val > 0) sign = '+';
       if (fabs(val - 0.0) < 0.00001) cout << "y^2 = ";
       else cout << "(y " << sign << ' ' << val << ")^2 = ";
       cout << (nE*nE - 4*nC*nF)/(4*nC*nC);
     }
     else {
         val = nD/(2*nA);
         if (val < 0) sign = '-';
         if (val > 0) sign = '+';
         if (fabs(val - 0.0) < 0.00001) cout << "x^2 = ";
         else cout << "(x " << sign << ' ' << val << ")^2 = ";
         cout << (nD*nD - 4*nA*nF)/(4*nA*nA);
     }
     cout << "\n\nSince the sum of a square cannot be negative, this equation, \n";
     display_equation(nA, nB, nC, nD, nE, nF);
     cout << ", is not satisfied for any real number ";
     if (fabs(nA - 0.0) < 0.00001) cout << "y.";
     else cout << "x.";
     cout << "\n\nFor R^2, the graph is the empty set.\n\n";

   }

   if (code == 11)  {
       cout << "The equation is ";
       display_equation(nA, nB, nC, nD, nE, nF);
       cout << endl << endl;
       cout << nF << " = 0 " << "is an impossible equation: the empty set (no solutions).\n\n";
   }
}

void my_pause ()  {

    //do  {
        cout << "Press ENTER [ maybe twice? ] to continue.";

        // Clears the input stream.
        cin.clear();

        /* This will tell the console to wait for the maximum
       number of characters that can be entered into the
       input stream or for a newline character, hence, the
       <ENTER> key.
    */
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    //  } while (cin.get() != '\n');
   cin.get();
}

void display_equation(reals A, reals B, reals C, reals D, reals E, reals F)  {
        char sign = '+';

        if (fabs(A - 0.0) < 0.00001) {}
        else cout << A << " x^2 ";
        if (fabs(B - 0.0) < 0.00001) {} // do not display zeros
        else {
            if (B < 0) sign = '-';
            else sign = '+';
            if (fabs(A - 0.0) < 0.00001) sign = ' ';
            cout << sign << ' ' << fabs(B) << "xy ";
        }

        if (fabs(C - 0.0) < 0.00001) {} // do not display zeros
        else {
            if (C < 0) sign = '-';
            else sign = '+';
            if ( (fabs(A - 0.0) < 0.00001) &&  (fabs(B - 0.0) < 0.00001) )  {
                 cout << fabs(C) << " y^2 ";
               }
            else cout << sign << ' ' << fabs(C) << "y^2 ";
        }
        if (fabs(D - 0.0) < 0.00001)  {} // do not display zeros
        else {
            if (D < 0) sign = '-';
            else sign = '+';
            if  ( (fabs(A - 0.0) < 0.00001) &&  (fabs(B - 0.0) < 0.00001)
                && (fabs(C - 0.0) < 0.00001) )  sign = ' ';
            cout << sign << ' ' << fabs(D) << "x ";
        }

        if (fabs(E - 0.0) < 0.00001)  {} // do not display zeros
        else {
            if (E < 0) sign = '-';
            else sign = '+';
            if ( (fabs(A - 0.0) < 0.00001) &&  (fabs(B - 0.0) < 0.00001)
                && (fabs(C - 0.0) < 0.00001) && (fabs(D - 0.0) < 0.00001) )
                  sign = ' ';
            cout << sign << ' ' << fabs(E) << "y ";
        }

        if (fabs(F - 0.0) < 0.00001)  { cout << "= 0\n\n"; } // do not display zeros
        else {
            if (F < 0) sign = '-';
            else sign = '+';
            if ( (fabs(A - 0.0) < 0.00001) &&  (fabs(B - 0.0) < 0.00001)
                && (fabs(C - 0.0) < 0.00001) && (fabs(D - 0.0) < 0.00001)
                && (fabs(E - 0.0) < 0.00001) )
                sign = ' ';
            cout << sign << ' ' << fabs(F) << " = 0";
        }
}
