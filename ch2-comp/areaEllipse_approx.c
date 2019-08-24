// Mike Hentrich 
// 20 February 2019
// Introductory Analysis c.1988 Chapter 2 Computer Applications p85, exercise 6

#include<stdio.h>
#include<stdlib.h>  // for GNU GCC
#include<math.h>

//#include<conio.h>   // for Microsoft version


const double PI = acos(-1);

double Rectangle_Area(int m, int number_of_rectangles, double a, double b);

void main()  {
  double sum, a, b;
  int n, m, i;

  //clrscr();
  system("clear");  // Linux
  printf("\nThis program will estimate the area of an ellipse,\n");
  printf("given lengths of major and minor axes, and using sum of n rectangles.\n");
  printf("\nEnter the length of the major axis: ");
  scanf("%lf", &a);
  a /= 2.0;
  printf("\nEnter the length of the minor axis: ");
  scanf("%lf", &b);
  b /= 2.0; 
  printf("Enter the number of rectangles: ");
  scanf("%d",&n);

  
  printf("\nWith a left end-point approximation, m = 0 to m = %d.", n - 1);
  sum = 0;
  for (i = 0; i < n; ++i)  {
      sum += 4*Rectangle_Area(i, n, a, b);
  }
  printf("\nThe area of the ellipse is approximately %.4lf square units.\n", sum);
  printf("\nWith a right end-point approximation, m = 1 to m = %d.", n);
  double left = sum;

  sum = 0;
  for (i = 1; i <= n; ++i)  {
      sum += 4*Rectangle_Area(i, n, a, b);
  }
  printf("\nThe area of the ellipse is approximately %.4lf square units.\n\n", sum);
  double right = sum;

  printf("CHECK: PI*(%.2f)*(%.2lf) = %.4lf\n", a, b, PI*a*b);
  double actual = PI*a*b;
  printf("\nComparison: |%.4lf - %.4lf| = %.4lf  and   ", actual, left, fabs(actual - left));
  printf("|%.4lf - %.4lf| = %.4lf\n\n", actual, right, fabs(actual - right));
  printf("With %d rectangles, ", n);
  if (fabs(actual - left) > fabs(actual - right))
      printf("the right end-point approximation is closer.\n\n");
  else printf("the left end-point approximation is closer.\n\n");


}

double Rectangle_Area(int m, int number_of_rectangles, double a, double b)  {

    int n = number_of_rectangles;
    // for ellipse
    return (a/(double)n) * b * sqrt(1 - pow(m/(double)n, 2));
}