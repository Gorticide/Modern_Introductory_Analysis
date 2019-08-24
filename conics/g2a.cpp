/*        <- Output -><----- Input ----->

   Conversion of Geometric parameters of a conic to its Algebraic parameters

   Geometric parameters depend on the type of the conic (see below)

   Algebraic parameters are coefficients A,B,C,D,E,F in the algebraic
   equation     Ax^2 + 2Bxy + Cy^2 + 2Dx + 2Ey + F = 0

   Input:  code is the code of the conic type (see below)
           ParG is the vector of Geometric parameters (see below)

   Output: ParA = (A,B,C,D,E,F)' is the vector of Algebraic parameters

   code:   1 - ellipse  2 - hyperbola  3 - parabola
           4 - intersecting lines  5 - parallel lines
           6 - coincident lines    7 -single line
           8 - single point        9 - imaginary ellipse
          10 - imaginary parallel lines
          11 - "impossible" equation, 1=0 or -1=0 (no solutions)

           Geometric parameters are determined only for 
               the most common types of conics:

   1. Ellipses:  canonical equation  x^2/a^2 + y^2/b^2 = 1
                 a>b or a=b are the major and minor semi-axes

       ParG = [Xcenter, Ycenter, a, b, AngleOfTilt]'

   2. Hyperbolas:  canonical equation  x^2/a^2 - y^2/b^2 = 1
                 a  is the distance from the center to each vertex
                 b  is the vertical distance from each vertex to asymptotes

       ParG = [Xcenter, Ycenter, a, b, AngleOfTilt]'

   3. Parabolas:  canonical equation  y^2 = 2px
                 p  is the distance from the focus to the directix

       ParG = [Xcenter, Ycenter, p, AngleOfTilt]'

   4. Intersecting lines:  canonical equation  (cos(u)*x+sin(u)*y+d)*(cos(v)*x+sin(v)*y+e) = 0
                   u,v are directional angles of the lines
                   d,e are distances from the origin (0,0) to the lines

       ParG = [u,d,v,e]'

        Nikolai Chernov,  February 2012
        The code in this file written by Michael William Hentrich
        February 2019
*/

#include <iostream>
#include <cmath>
#include <iomanip>
#include <vector>
#include <eigen3/Eigen/Dense>
#include <eigen3/Eigen/Eigenvalues>

#include "mystuff.h"
#include "GtoA_modified.cpp"
#include "GtoA.cpp"


typedef long double reals;
//typedef double reals;

typedef long long integers;
//typedef double reals;

typedef Matrix<reals, 6, 1> M6x1;
typedef Matrix<reals, 5, 1> M5x1;

using namespace std;
using namespace Eigen;

void set_parameters(M6x1 A, reals &nA, reals &nB, reals &nC, reals &nD, reals &nE, reals &nF);
void display_equation( reals nA, reals nB, reals nC, reals nD, reals nE, reals nF);

// helper functions for parabola (code 3)
void get_set_parabola(M5x1 &g, char ori);
M2x1 get_vertex_via_lines(char ori, reals c);  // will prompt for directrix AND axis of symmetry
M2x1 get_vertex_via_point(char ori, reals c);  // will prompt for focus or vertex
M2x1 get_vertex_via_focus(char ori, reals c, M2x1 focus); 
reals get_c(char ori, M2x1 vertex, M2x1 focus);  // orientation not necessary but used anyway
reals get_c(char ori);
M5x1 get_parameters_via_point_and_directrix(char ori);  // will use focus and directrix or 
                                                           // axis of symmetry depending on
                                                           // given orientation

const reals PI = acos(-1);
const reals radians = PI/180.0;
const reals degrees = 180.0/PI;


int main()   {
  int code;
  M6x1 ParA;
  M5x1 G;
  char sign = '+';
  reals nA, nB, nC, nD, nE, nF;
  reals c, line;
  char orientation;
  char point_type;

cout << "\nConversion of Geometric parameters of a conic to its Algebraic [General] Equation\n";
     //<< "Algebraic parameters are coefficients A,B,C,D,E,F in the algebraic\n"
     //<< "equation     Ax^2 + Bxy + Cy^2 + Dx + Ey + F = 0\n\n"
     //<< "equation     Ax^2 + 2Bxy + Cy^2 + 2Dx + 2Ey + F = 0\n\n"
 /*    << "Geometric parameters are determined only for the most common types of conics:\n\n"
     << "1. Ellipses:  canonical equation  x^2/a^2 + y^2/b^2 = 1 \n\t\t"
     << "a>b or a=b are the major and minor semi-axes:\nParG = [Xcenter, Ycenter, a, b, AngleOfTilt]\n\n"
     << "2. Hyperbolas:  canonical equation  x^2/a^2 - y^2/b^2 = 1 \n\t\t"
     << "a  is the distance from the center to each vertex \n\t\t"
     << "b  is the vertical distance from each vertex to asymptotes \n"
     << "ParG = [Xcenter, Ycenter, a, b, AngleOfTilt]\n\n"
     << "3. Parabolas:  canonical equation  y^2 = 2px \n\t\t"
     << "p  is the distance from the focus to the directix \n"
     << "ParG = [Xcenter, Ycenter, p, AngleOfTilt] \n\n"
     << "4. Intersecting lines:\ncanonical equation  (cos(u)*x+sin(u)*y+d)*(cos(v)*x+sin(v)*y+e) = 0 \n\t\t"
     << "u,v are directional angles of the lines \n\t\t"
     << "d,e are distances from the origin (0,0) to the lines \n"
     << "ParG = [u,d,v,e] \n\n";
*/
    cout << "\n1 (Ellipse),\n2 (Hyperbola),\n3 (Parabola),\n4 (Intersecting Lines)\n"
         << "Enter code: ";
    cin >> code;

    if (code > 4) cout << "Geometric parameters are determined only for the most common types of conics\n\n";
    if (code == 4)  {
      /*  CHANGED FORM:
      
        -------------------------------original canonical form ------------------------     
        reals u, d, e, v; 
        cout << "Under construction\n\n"
             << "Intersecting lines:  canonical equation  (cos(u)*x+sin(u)*y+d)*(cos(v)*x+sin(v)*y+e) = 0 \n\t\t"
             << "u,v are directional angles of the lines \n\t\t"
             << "d,e are distances from the origin (0,0) to the lines \n\t\t"
             << "ParG = [u,d,v,e] \n\n";
        cout << "Enter u: ";
        cin >> u;
        G(0) = u;
        cout << "Enter d: ";
        cin >> d;
        G(1) = d;
        cout << "Enter v: ";
        cin >> v;
        G(2) = v;
        cout << "Enter e: ";
        cin >> e;
        G(3) = e;
        GtoA(ParA, G, 4)
        -----------------------------------------------------------------------
        New Form :
         CHANGING FORM to two given lines in form D1*x + E1*y + F1 = 0
         and D2*x + E2*y + F2 = 0 with point of intersection:
         Xcenter = (-F1*E2 - E1*(-F2))/(D1*E2 - E1*D2)
         Ycenter = (-F2 - D2*Xcenter)/E2 

         There are two cases which will be handled in a clever manner.
         If D1 == D2 and E1 == -E2, then a = -|E1| and b = |D1|.
         If D1 == -D2 and E1 == E2, then b = -|D1| and a = |E1|
         Feed G to GtoA:
         G(0) = Xcenter
         G(1) = Ycenter
         G(2) = a
         G(3) = b
         On the other end (in GtoA) we will handle the two cases a < 0 or b < 0.
 */
      reals D1, D2, E1, E2, F1, F2, X, Y, a, b;
      cout << "\nEnter the equations of the two intersecting lines in\n"
           << "in form D1*x + E1*y + F1 = 0 and D2*x + E2*y + F2 = 0.\n"
           << "If the equation is in the form Dx + Ey = F, be sure to enter -F.\n\n";
      cout << "Enter D1: ";
      cin >> D1;
      cout << "Enter E1: ";
      cin >> E1;
      cout << "Enter F1: ";
      cin >> F1;
      cout << endl << "Enter D2: ";
      cin >> D2;
      cout << "Enter E2: ";
      cin >> E2;
      cout << "Enter F2: ";
      cin >> F2;   
      X = (-F1*E2 - E1*(-F2))/(D1*E2 - E1*D2);
      Y = (-F2 - D2*X)/E2;


     if ( ( (D1 == D2) && (E1 == -E2) ) ||  ( (D1 == -D2) && (E1 == E2) ) )
      {
        if ( (D1 == D2) && (E1 == -E2) ) {
             a = -fabs(E1); 
             b = fabs(D1);
        }
        if ( (D1 == -D2) && (E1 == E2) )   {
          b = -fabs(D1);
          a = fabs(E1);
        }

        // Initialize values in G:
         G(0) = X;
         G(1) = Y;
         G(2) = a;
         G(3) = b;
        cout << "\nThe point of intersection of the lines with equations\n";
        display_equation(0, 0, 0, D1, E1, F1);
        cout << "  and";
        display_equation(0, 0, 0, D2, E2, F2);
        cout << "\nis the point (" << X << ", " << Y << ").\n\n";
        GtoA_modified(ParA, G, 4, ' ');
        set_parameters(ParA, nA, nB, nC, nD, nE, nF);
        cout << "The General Equation for these intersecting lines is\n";
        display_equation(nA, nB, nC, nD, nE, nF);
      }
      else cout << "\nThese are not intersecting lines!\n\n";
      
   }

    if (code == 1) {
       reals Xcenter, Ycenter, a2, b2, AngleOfTilt; 
       cout << "\nEllipses:  canonical equation  x^2/a^2 + y^2/b^2 = 1 \n\t\t";
       cout << "a>b or a=b are the major and minor semi-axes: ";
       cout << "ParG = [Xcenter, Ycenter, a, b, AngleOfTilt]\n\n";
       cout << "Enter Center (h, k): ";
       cin >> Xcenter >> Ycenter;
       G(0) = Xcenter;
       G(1) = Ycenter;

     cout << "\nIs the major axis vertical or horizontal?\n"
          << " y^2/a^2 + x^2/b^2 = 1 (vertical)\n  x^2/a^2 + y^2/b^2 = 1  (horizontal)\n"
          << "enter v or h: ";
    cin >> orientation;
    if ((orientation == 'v') || (orientation == 'V') ) {
     cout << "\nEnter a^2 (a to the second power): ";
     cin >> a2;
     G(2) = sqrt(a2);
     cout << "\nEnter b^2 (b to the second power): ";
     cin >> b2;
     G(3) = sqrt(b2);
    }
    else {
     cout << "\nEnter a^2 (a to the second power): ";  // switching behind the scenes
     cin >> a2;
     G(3) = sqrt(a2);
     cout << "\nEnter b^2 (b to the second power): ";
     cin >> b2;
     G(2) =sqrt(b2);
    }

       cout << "\nEnter Angle of Tilt [enter 0 for no tilt] in degrees: ";
       cin >> AngleOfTilt;
       G(4) = AngleOfTilt * radians;
       GtoA_modified(ParA, G, 1, orientation);
       set_parameters(ParA, nA, nB, nC, nD, nE, nF);
       cout << "The General Equation for this ellipse is \n";
       display_equation(nA, nB, nC, nD, nE, nF);
    }

    if (code == 2) {
       reals Xcenter, Ycenter, a2, b2, AngleOfTilt; 
       cout << "Hyperbolas:  canonical equation  y^2/a^2 - x^2/b^2 = 1 \n\t\t"
            << "a  is the vertical distance from the center to each vertex \n\t\t"
            << "b  is the horizontal distance from each vertex to asymptotes \n\t\t"
            <<  "if x^2/a^2 - y^2/b^2 = 1\n\t\t"
            << "a  is the horizontal distance from the center to each vertex\n\t\t"
            << "b  is the vertical distance from each vertex to asymptotes\n"
            << "ParG = [Xcenter, Ycenter, a, b, AngleOfTilt]\n\n";
     cout << "Enter Center (h, k): ";
     cin >> Xcenter >> Ycenter;
     G(0) = Xcenter;
     G(1) = Ycenter;
     cout << "\nIs the transverse axis vertical or horizontal?\n"
          << " y^2/a^2 - x^2/b^2 = 1 (vertical)\n  x^2/a^2 - y^2/b^2 = 1  (horizontal)\n"
          << "enter v or h: ";
    cin >> orientation;
    if ((orientation == 'v') || (orientation == 'V') ) {
     cout << "\nEnter a^2 (a to the second power): ";
     cin >> a2;
     G(2) = sqrt(a2);
     cout << "\nEnter b^2 (b to the second power): ";
     cin >> b2;
     G(3) = sqrt(b2);
    }
    else {
     cout << "\nEnter a^2 (a to the second power): ";  // switching behind the scenes
     cin >> a2;
     G(3) = sqrt(a2);
     cout << "\nEnter b^2 (b to the second power): ";
     cin >> b2;
     G(2) =sqrt(b2);
    }

     cout << "\nEnter Angle of Tilt [enter 0 for no tilt] in degrees: ";
     cin >> AngleOfTilt;
     G(4) = AngleOfTilt * radians;
     GtoA_modified(ParA, G, 2, orientation);
     set_parameters(ParA, nA, nB, nC, nD, nE, nF);
     cout << "The General Equation for this hyperbola is \n";
     display_equation(nA, nB, nC, nD, nE, nF);
     
    }

    if (code == 3)  {
       reals Xcenter, Ycenter, AngleOfTilt, p; 
       cout << "Parabolas:  canonical equations\n  y^2 = 2px = 4cx <----> x = [1/(4c)]y^2\n"
            << " (horizontal axis of symmetry, vertical directrix)\n\t"
            << "p = 2c  is the distance from the focus to the directix \n"
            << "x^2 = 2py = 4cy <----> y = [1/(4c)]x^2 \n (vertical axis of symmetry, horizontal directrix)" 
            << "\n ParG = [Xcenter, Ycenter, p, AngleOfTilt] \n\n"
            <<"Is the axis of symmetry vertical (y = x^2) or horizontal (x = y^2)?\n"
            << "Enter v or h: ";
       cin >> orientation;
       get_set_parabola(G, orientation);
       GtoA_modified(ParA, G, 3, orientation);
       set_parameters(ParA, nA, nB, nC, nD, nE, nF);
       cout << "The General Equation for this parabola is \n";
       display_equation(nA, nB, nC, nD, nE, nF);
    }
    cout << endl << endl;  
}

void set_parameters(M6x1 A, reals &nA, reals &nB, reals &nC, reals &nD, reals &nE, reals &nF)  {
  nA = A(0);
  nB = 2*A(1);
  nC = A(2);
  nD = 2*A(3);
  nE = 2*A(4);
  nF = A(5);
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

void get_set_parabola(M5x1 &g, char ori)  {
    int info_type;
    reals c, theta, x0, y0;
    M2x1 focus, vertex;

    cout << "\n\nWhat information is given?  [choose type 1, 2, 3, or 4]:\n"
            << "(1) common distance (c) between focus and vertex (vertex and directrix)\n"
            << "AND [focus OR vertex]\n"
            << "(2) common distance (c) between focus and vertex (vertex and directrix)\n"
            << " AND directrix AND axis"
            << "\n(3) vertex and focus (will compute p = 2c with c = focus - vertex)\n"
            << "(4) vertex or focus AND directrix\n\n\t"
            << "Enter type of information given [1, 2, 3, or 4]: ";
       cin >> info_type;
       
       switch(info_type)  {

           case 1:    
               cout << "\n\nEnter distance between vertex and focus \n"
                    << " (= distance between vertex and directrix): ";
               cin >> c;
               vertex = get_vertex_via_point(ori, c);
               g(2) = 2*c;
               g(0) = vertex(0);
               g(1) - vertex(1);
               break;

           case 2:
               cout << "\n\nEnter distance between vertex and focus\n"
                    << " (= distance between vertex and directrix): ";
               cin >> c;            
               g(2) = 2*c;
               vertex = get_vertex_via_lines(ori, c);  
               g(0) = vertex(0);
               g(1) = vertex(1); 
               break;

          case 3:
               cout << "\nEnter coordinates (h, k) of vertex [h k]: ";
               cin >> x0 >> y0;
               vertex << x0, y0;
               g(0) = vertex(0);
               g(1) = vertex(1);
               cout << "\nEnter coordinates of focus: ";
               cin >> x0 >> y0;
               focus << x0, y0;
               c = get_c(ori, vertex, focus);
               g(2) = 2*c;
               break;

          case 4:  
               g = get_parameters_via_point_and_directrix(ori);  
               break;
       }

        cout << "\nEnter Angle of Tilt [enter 0 for no tilt] in degrees: ";
        cin >> theta;
        g(3) = theta * radians;
}

M2x1 get_vertex_via_lines(char ori, reals c)  {       // must get directrix AND axis of symmetry
     reals dir_line, axis_line;
     M2x1 vertex;

     cout << "\nEnter ";

     if (ori == 'v' || ori == 'V')  {
        cout << "horizontal directrix y = ";
        cin >> dir_line;
        cout << "vertical axis of symmetry x = ";
        cin >> axis_line;
        vertex(0) = axis_line;   // vertex intersects vertical axis of symmetry
        vertex(1) = dir_line + c;  // add vertical distance c from horizontal directrix
       }
      else {
          cout << "vertical directrix x = ";
          cin >> dir_line;
          cout << "horizontal axis of symmetry y = ";
          cin >> axis_line;
          vertex(0) = dir_line + c;  // add horizontal distance c from vertical directrix
          vertex(1) = axis_line;       // vertex intersects horizontal axis of symmetry

     }
     return vertex;
}


M2x1 get_vertex_via_point(char ori, reals c)  {
    char point_type;
    reals x0, y0;

    cout << "\n\nDo we know the focus or the vertex?\n"
            << "Enter point type [f for 'focus', v for 'vertex']: ";
    cin >> point_type;
    if (point_type == 'f' || point_type == 'F')  {
       M2x1 F; 
       cout << "\nEnter the coordinates of the focus: ";
       cin >> x0 >> y0;
       F << x0, y0;
       return get_vertex_via_focus(ori, c, F); 
    }
    else {
        M2x1 V;
        cout << "\nEnter the coordinates (h, k) of the vertex [h k]:  ";
        cin >> x0 >> y0;
        V << x0, y0;
        return V; 
    }
    
}

M2x1 get_vertex_via_focus(char ori, reals c, M2x1 focus)  {  
    M2x1 vertex;
    if (ori == 'v' || ori == 'V') {
        vertex(0) = focus(0);
        vertex(1) = focus(1) - c;
    }
    else {
        vertex(1) = focus(1);
        vertex(0) = focus(0) - c;
    }
    return vertex;
}

reals get_c(char orient, M2x1 vertex, M2x1 focus)  {

     if (orient == 'v' || orient == 'V') {                       // vertical distance
      // if (focus(1) < vertex(1))   return focus(1) - vertex(1);
      // else return focus(1) - vertex(1);
      return focus(1) - vertex(1);
     } 
     else  {                                                     // horizontal distance
       //  if (focus(0) < vertex(0))  return vertex(0) - focus(0);
        // else 
        return focus(0) - vertex(0);
     } 
}

M5x1 get_parameters_via_point_and_directrix(char ori)   {

 // must get directrix or axis of symmetry
     char point_type;
     reals directrix, x0, y0;
     M2x1 point;
     M5x1 Geom;
  
    if (ori == 'v' || ori == 'V')  {
        cout << "horizontal directrix y = ";
        cin >> directrix;
     }
     else {
         cout << "vertical directrix x = ";
         cin >> directrix;
     }
     
     cout << "\n\nDo you know the focus or the vertex?\n"
            << "Enter point type [f for 'focus', v for 'vertex']: ";
       cin >> point_type;
       if (point_type == 'v' || point_type == 'V')  {    // given VERTEX
           cout << "Enter Vertex (h, k): ";
           cin >> x0 >> y0;
           point << x0, y0;
           Geom(0) = point(0);
           Geom(1) = point(1);
           if (ori == 'v' || ori == 'V')  {   // working with ordinates (vertical axis)
              if (point(1) > directrix) Geom(2) = 2*(point(1) - directrix);   // p = 2*c
              else Geom(2) = 2*(directrix - point(1));
           }
           else {               // working with abscissas  (horizontal axis)
              if (point(0) > directrix) Geom(2) = 2*(point(0) - directrix);   // p = 2*c
              else Geom(2) = 2*(directrix - point(0));
           }
       }
       else {                                             // given FOCUS
           if (ori == 'v' || ori == 'V') {
               cout << "Directrix is horizontal, perpendicular to vertical axis of symmetry.\n"
                    << "Enter Focus coordinates: ";
               cin >> x0 >> y0;
               point << x0, y0;
               Geom(0) = point(0);
               Geom(1) = (point(1) + directrix)/2;
           }
           else {
               cout << "Directrix is vertical, perpendicular to horizontal axis of symmetry.\n"
                    << "Enter Focus coordinates: ";
               cin >> x0 >> y0;
               point << x0, y0;
               Geom(0) = (point(0) + directrix)/2;
               Geom(1) = point(1);
           }
           if (ori == 'v' || ori == 'V')  {   // working with ordinates (vertical axis)
             // if (point(1) > directrix) Geom(2) = point(1) - directrix;   // p = 2*c
             // else Geom(2) = point(1) - directrix;
             Geom(2) = point(1) - directrix;
           }
           else {               // working with abscissas  (horizontal axis)
             // if (point(0) > directrix) Geom(2) = point(0) - directrix;   // p = 2*c
             // else Geom(2) = point(0) - directrix;
             Geom(2) = point(0) - directrix;
           }
       }
        return Geom;      
}

 