  /* compute 
    ⌠b
    │ xn
    ⌡a
  here with simple calculus and return the result 
  
  
  double(*f)(double x)
  The above tells the compiler that the parameter f is a pointer to function. 
  The pointed function takes a double input and returns a double. 
  Therefore the mathematical functions like sin, cos, atan etc 
  can be easily passed into the function for integral.
  */

#include <iostream>
#include <cmath>
#include <iomanip>

double integral(double(*f)(double x), double a, double b, int n);
double x2(double x);

using std::cout;
using std::cin;

int main()
{
    double b;
    int n;
    cout.precision(5);
    //cout << integral(cos, 0, M_PI / 2, 10);
    // enter right bound
    cout << "\nEnter right bound: ";
    cin >> b;
    cout << "\nEnter the number of rectangles: ";
    cin >> n;
    cout << "\nFUNCTION: x^2\n";
    cout << integral(x2, 0, b, n);
    return 0;
}

double integral(double(*f)(double x), double a, double b, int n) {
    double step = (b - a) / n;  // width of each small rectangle
    double area = 0.0;  // signed area
    for (int i = 0; i < n; i ++) {
        area += f(a + (i + 0.5) * step) * step; // sum up each small rectangle
    }
    return area;
}

double x2(double x)   {
    return x*x;
}