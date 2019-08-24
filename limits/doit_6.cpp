/*
Computer Exercises for Limits: A Transition to Calculus circa 1966 (1990 edition)

Exercise 6 (Chapter 2)

A program that will determine the value of M such that all the terms of  
the sequence {a_n} = { 2*n^2/(n^2 + 4) } with n >= M are in the neighborhood  
of the limit 2 of radius 0.1.   
  
Use the statements "if abs(T - 2) >= 0.1 then ... and print "N", "T", "abs(T - 2)"  
(see page 38) 
*/

#include <iostream>
#include <cmath>

using namespace std;

double a(int n);

int main()   {

    double M;

    for (int i = 1; i < 20; ++i)  {
        if (abs(a(i) - 2) >= 0.1)  {
          M = i;
          cout << "n = " << i << "; a(" << i << ") = " << a(i) << "; |" 
               << a(i) << " - 2| = " << abs(a(i) - 2) << endl;
         }
     }
    cout << "\nThe value of M such that all terms of the sequence\n"
         << "{a_n} = { (2*n^2)/(n^2 + 4) } with n >= M \n"
         << "are in the neighborhood of the limit 2 of radius 0.1 is: " << M + 1 << endl;
    return 0;
}


double a(int n)   {
    return (double)(2*n*n)/(n*n + 4);
}

/******   the output is:
 hentrich@coyote:[~/work/c++/analysis_intro/limits]: 
$ ----> ./doit6
n = 1; a(1) = 0.4; |0.4 - 2| = 1.6
n = 2; a(2) = 1; |1 - 2| = 1
n = 3; a(3) = 1.38462; |1.38462 - 2| = 0.615385
n = 4; a(4) = 1.6; |1.6 - 2| = 0.4
n = 5; a(5) = 1.72414; |1.72414 - 2| = 0.275862
n = 6; a(6) = 1.8; |1.8 - 2| = 0.2
n = 7; a(7) = 1.84906; |1.84906 - 2| = 0.150943
n = 8; a(8) = 1.88235; |1.88235 - 2| = 0.117647

The value of M such that all terms of the sequence
{a_n} = { (2*n^2)/(n^2 + 4) } with n >= M 
are in the neighborhood of the limit 2 of radius 0.1 is: 9


Notice that if I had not placed (double) before (2*n*n)/(n*n + 4), then the compiler
would use integer division, and the output would be:

hentrich@coyote:[~/work/c++/analysis_intro/limits]: 
$ ----> ./doit6
n = 1; a(1) = 0; |0 - 2| = 2
n = 2; a(2) = 1; |1 - 2| = 1
n = 3; a(3) = 1; |1 - 2| = 1
n = 4; a(4) = 1; |1 - 2| = 1
n = 5; a(5) = 1; |1 - 2| = 1
n = 6; a(6) = 1; |1 - 2| = 1
n = 7; a(7) = 1; |1 - 2| = 1
n = 8; a(8) = 1; |1 - 2| = 1
n = 9; a(9) = 1; |1 - 2| = 1
n = 10; a(10) = 1; |1 - 2| = 1
n = 11; a(11) = 1; |1 - 2| = 1
n = 12; a(12) = 1; |1 - 2| = 1
n = 13; a(13) = 1; |1 - 2| = 1
n = 14; a(14) = 1; |1 - 2| = 1
n = 15; a(15) = 1; |1 - 2| = 1
n = 16; a(16) = 1; |1 - 2| = 1
n = 17; a(17) = 1; |1 - 2| = 1
n = 18; a(18) = 1; |1 - 2| = 1
n = 19; a(19) = 1; |1 - 2| = 1

The value of M such that (2*n^2)/(n^2 + 4) with n >= M 
are in the neighborhood of the limit 2 of radius 0.1 is: 20
*/


