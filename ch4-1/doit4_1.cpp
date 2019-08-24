  /* 
    Introductory Analysis
    Chapter 4, section 1

    Mike Hentrich   22 April 2019
  
  1. Write a program to find ( f(3 + h) - f(3) ) / h
     when h = 0.1, 0.01. 0.001. and 0.0001 for f(x) = x^2

  2. Modify and run the program in Exercise 1 for each function.
     (a)   f(x) = x^2 -1
     (b)   f(x) = (x - 1)^2
     (c)   f(x) = 4/x
     (d)   f(x) = sqrt(x - 1)
 
  NOTE:

  double(*f)(double x)
  The above tells the compiler that the parameter f is a pointer to a function. 
  The pointed-to function takes a double input and returns a double. 
  */

#include <iostream>
#include <cmath>
#include <iomanip>
#include <string>
#include <vector>

using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::vector;

double Dx(double(*f)(double x), double dx);
double x2(double x);
double a(double x);
double b(double x);
double c(double x);
double d(double x);


int main()
{
    // Store equations which define functions
    vector<string> Strings;

   //Store pointers to functions:
    vector<double(*)(double)> Functions;
    
    // Load up the vector with pointers to functions
    // and load the vector with function definitions
    Functions.push_back(x2);
    string eqn = "f(x) = x^2";
    Strings.push_back(eqn);

    Functions.push_back(a);
    eqn = "f(x) = x^2 - 1";
    Strings.push_back(eqn);

    Functions.push_back(b);
    eqn = "f(x) = (x - 1)^2";
    Strings.push_back(eqn);

    Functions.push_back(c);
    eqn = "f(x) = 4/x";
    Strings.push_back(eqn);

    Functions.push_back(d);
    eqn = "f(x) = sqrt(x - 1)";
    Strings.push_back(eqn);
 
    cout.precision(5);
    for (auto i : Strings)   
        cout << "\nFUNCTION: " << i << endl;
    
    cout << endl << endl;
 
    int count = 0;

    for (auto i : Functions)   {
        double h = 0.1;
        
        cout << "\nFunction:  " << Strings[count] << "\n\n";
        while (h > 0.0001) {
            cout << "( f(3 + dx) - f(3) ) / dx  = ( f(" << 3 + h 
                 << ") - f(3) ) / " << h << endl
                 << " = (" << i(3 + h) << " - " << i(3) << ") / " 
                 << h << " = " << i(3+h) - i(3) << " / " << h
                 << endl << " = " << Dx(i, h);
            cout << endl << endl;
            h *= 0.1;
        }
        count++;
    }
    return 0;
}

double Dx(double(*f)(double x), double dx) {
    
  return  ( f(3 + dx) - f(3) ) / dx;

}

double x2(double x)   {
    return x*x;
}

double a(double x)  {
    return x*x - 1;
}

double b(double x)  {
    return (x - 1)*(x - 1);
}

double c(double x)  {
     return 4/x;
}

double d(double x)  {
    return sqrt(x - 1);
}
