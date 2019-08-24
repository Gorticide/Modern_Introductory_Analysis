/*
  Solution to Exercise 4 of Computer Exercises
  Limits: A Transition to Calculus circa 1966, 1990 edition pp.179-181

A program that will generate the first thirteen terms of the Fibonacci sequence,
{a(n)} such that a(1) = 1, a(2) = 1, and for n >= 3,
a(n) = a(n - 2) - a(n - 1)

(i.e., any term after the second term is the sum of the two preceding terms).
*/

#include <iostream>
#include <vector>
#include <map>                        // header needed for the container: map

using namespace std;

long fibo_iterative(long n);
long fibo_recursive(long n);
long fibo_vector(long n);
long fibo_map( long n );
long mem_fibo(long i, std::map<long, long>& m);
void printFibonacci(long(*f)(long n), long n);

int main()  {

	long x;
	cout << "Comparing speeds of Fibonacci Procedures: " << endl;

	cout << "Enter n ----> ";
	cin >> x;
    cout << endl;

  cout << "Using fibo_iterative(" << x << "): ";
	printFibonacci(fibo_iterative, x);
	cout << "Using fibo_recursive(" << x << "): ";
	printFibonacci(fibo_recursive, x);
	cout << "fibo_vector(" << x << "): ";
	printFibonacci(fibo_vector, x);
	cout << "fibo_map(" << x << "): ";
	printFibonacci(fibo_map, x);
}

long fibo_iterative(long n) {

	if (n==1) return 1;
	if (n==2) return 1;
	long a = 1;
	long b = 1;
	long c;
	for(int k=2; k < n; k++) {
		c = a+b;
		a = b;
		b = c;
	}
    return c;
}

long fibo_recursive(long n) {
	if (n==1) return 1;
	if (n==2) return 1;
	return fibo_recursive(n-1) + fibo_recursive(n-2);
}


long fibo_vector(long n)
{
  vector<long> results( n );
  results[ 0 ] = 0;      // adapting to structure of vector type, starts at 0
	results[ 1 ] = 1;
	if ( (n==1) || (n==2) ) return 1;
    for ( int i = 2; i < n; i++ )
        results[i] = results[i - 1] + results[i - 2];
    return results[ n - 1 ] + results[ n - 2 ];
}


long fibo_map (long i) {
    // key (Fibonacci index) - value (Fibbonaci number)
    std::map<long, long> memo;

    // initialize the first two Fibonacci numbers
    memo.insert(std::pair<long,long>(0, 0));
    memo.insert(std::pair<long,long>(1, 1));

    return mem_fibo(i, memo);
}

long mem_fibo(long i, std::map<long, long>& m) {

    // if value with key == i does not exist in m: calculate it
    if (m.find(i) == m.end()) {

        // the recursive calls are made only if the value doesn't already exist
        m[i] = mem_fibo(i - 1, m) + mem_fibo(i - 2, m);
    }

    // if value with key == i exists, return the corresponding value
    return m[i];
}


void printFibonacci(long(*f)(long n), long n)  {
	cout <<  "\nThe first " << n << " terms of the Fibonacci sequence:\n";

    for (int i = 1; i <= n; i++)  {
		cout << f(i) << " ";
	}
	cout << endl << endl;
}

/*
 long(*f)(long n)
 The above tells the compiler that the parameter f is a pointer to function.
 The pointed to function takes a long integer input and returns long integer.
 I will then be able to call each version of fibo_* whn printing terms of Fibonacci sequence.
 */
