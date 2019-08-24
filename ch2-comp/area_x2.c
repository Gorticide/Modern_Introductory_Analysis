// Mike Hentrich 
// 20 February 2019
// Introductory Analysis c.1988 Chapter 2 Computer Applications p85, exercise 8

#include<stdio.h>
#include<stdlib.h>  // for GNU GCC
#include<math.h>

//#include<conio.h>   // for Microsoft version


const double PI = acos(-1);

double Rectangle_Area(int m, int number_of_rectangles, double boundary);
double integral(double(*f)(double x), double a, double b, int n);
double x2(double x);

void main()  {
  double sum, b;
  int n, m, i;

  //clrscr();
  system("clear");  // Linux
  printf("\nThis program will estimate the area of the region bounded,\n");
  printf("by the graph of y = x^2, the x-axis, and a vertical line.\n\n");
  printf("\nRight boundary is x = ");
  scanf("%lf", &b);
  printf("Enter the number of rectangles: ");
  scanf("%d",&n);

  
  printf("\nWith a left end-point approximation, m = 0 to m = %d.", n - 1);
  sum = 0;
  for (i = 0; i < n; ++i)  {
      sum += Rectangle_Area(i, n, b);
  }
  printf("\nThe area is approximately %.4lf square units.\n", sum);
  printf("\nWith a right end-point approximation, m = 1 to m = %d.", n);
  double left = sum;

  sum = 0;
  for (i = 1; i <= n; ++i)  {
      sum += Rectangle_Area(i, n, b);
  }
  printf("\nThe area is approximately %.4lf square units.\n\n", sum);
  double right = sum;

  double actual = integral(x2, 0, b, n);
  printf("\nChecking function x^2 with integral(x^2, 0, %.4lf, %d):\n", b, n);
  printf("Area = %.4lf\n\n", actual);

  printf("\nComparison: |%.4lf - %.4lf| = %.4lf  and   ", actual, left, fabs(actual - left));
  printf("|%.4lf - %.4lf| = %.4lf\n\n", actual, right, fabs(actual - right));
  printf("With %d rectangles, ", n);
  if (fabs(actual - left) > fabs(actual - right))
      printf("the right end-point approximation is closer.\n\n");
  else printf("the left end-point approximation is closer.\n\n");


}

double Rectangle_Area(int m, int number_of_rectangles, double boundary)  {

    int n = number_of_rectangles;
    double b = boundary;
    // for x^2
    double width = b/(double)n;
    double height = pow((m*b)/(double)n, 2);

    return width * height;
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

/*   If we use the middle point of the rectangle to compute the f(x) 
     for the rectangle height, we get better accuracy.
*/