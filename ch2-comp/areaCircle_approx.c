
// Mike Hentrich 
// 20 February 2019
// Introductory Analysis c.1988 Chapter 2 Computer Applications p85, exercise 1

#include<stdio.h>
#include<stdlib.h>  // for GNU GCC
#include<math.h>

//#include<conio.h>   // for Microsoft version


const double PI = acos(-1);

double Rectangle_Area(int m, int number_of_rectangles, double radius);

void main()  {
  double sum, radius;
  int n, m, i;

  //clrscr();
  system("clear");  // Linux
  printf("\nThis program will estimate the area of a circle,\ngiven length of radius, using sum of n rectangles.\n");
  printf("Enter the number of rectangles: ");
  scanf("%d",&n);
  printf("\nEnter the length of the radius: ");
  scanf("%lf", &radius);
  
  printf("\nWith a left end-point approximation, m = 0 to m = %d.", n - 1);
  sum = 0;
  for (i = 0; i < n; ++i)  {
      sum += Rectangle_Area(i, n, radius);
  }
  printf("\nThe area of the circle is approximately %.4lf square units.\n", 4*sum);
  printf("\nWith a right end-point approximation, m = 1 to m = %d.", n);
  double left = 4*sum;

  sum = 0;
  for (i = 1; i <= n; ++i)  {
      sum += Rectangle_Area(i, n, radius);
  }
  printf("\nThe area of the circle is approximately %.4lf square units.\n\n", 4*sum);
  double right = 4*sum;

  printf("CHECK: PI*(%.2f)^2 = %.4lf\n", radius, PI*radius*radius);
  double actual = PI*radius*radius;
  printf("\nComparison: %.4lf - %.4lf = %.4lf  and   ", left, actual, left - actual);
  printf("%.4lf - %.4lf = %.4lf\n\n", actual, right, actual - right);
  printf("With %d rectangles, ", n);
  if (left - actual > actual - right) 
      printf("the right end-point approximation is closer.\n\n");
  else printf("the left end-point approximation is closer.\n\n");


}


double Rectangle_Area(int m, int number_of_rectangles, double radius)  {
    
    int n = number_of_rectangles;
    double r = radius;
    // for circle
    return (r/(double)n) * sqrt(r*r - pow(m*r/(double)n, 2));
}