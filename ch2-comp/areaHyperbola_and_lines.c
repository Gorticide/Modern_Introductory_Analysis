// Mike Hentrich 
// 20 February 2019
// Introductory Analysis c.1988 Chapter 2 Computer Applications p85, exercise 9

#include<stdio.h>
#include<stdlib.h>  // for GNU GCC
#include<math.h>
//#include<conio.h>   // for Microsoft version

double Rectangle_Area(int m, int number_of_rectangles, double a, double b, double d);

void main()  {
  double sum, a, b, x, y, d;
  int n, m, i;

  //clrscr();
  system("clear");  // Linux
  printf("\nThis program will estimate the area of the two regions\n");
  printf("formed by a hyperbola and two vertical lines x = d and x = -d\n");
  printf("Note that d must be greater than a.\n\n");
  printf("\nEnter the length of the transverse axis: ");
  scanf("%lf", &a);
  a /= 2.0;
  printf("\nEnter a point on the hyperbola.\nEnter abscissa (x-coordinate): ");
  scanf("%lf", &x);
  printf("\nEnter ordinate (y-coordinate): ");
  scanf("%lf", &y);
  b = sqrt((a*a*y*y)/(x*x - a*a));
  d = 0.0;
  while (d < a)  {
     printf("Right boundary is x = d = ");
     scanf("%lf", &d);
     if (d < a)  {
          printf("\n%.2lf is not less than %.2lf", d, a);
          printf("\nNote that d must be greater than %.4lf.\n\n", a);
     } 
  }

  printf("Enter the number of rectangles: ");
  scanf("%d",&n);

  printf("\nWith a left end-point approximation, m = 0 to m = %d.", n - 1);
  sum = 0.0;
  for (i = 0; i < n; ++i)  {
      sum += 4*Rectangle_Area(i, n, a, b, d);
  }
  printf("\nThe area is approximately %.4lf square units.\n", sum);
  printf("\nWith a right end-point approximation, m = 1 to m = %d.", n);

  sum = 0.0;
  for (i = 1; i <= n; ++i)  {
      sum += 4*Rectangle_Area(i, n, a, b, d);
  }
  printf("\nThe area is approximately %.4lf square units.\n\n", sum);

}

double Rectangle_Area(int m, int number_of_rectangles, double a, double b, double d)  {

    int n = number_of_rectangles;
    // for hyperbola and two vertical lines x = d and x = -d
    double x = a + m*((d - a)/(double)n);

    return ((d-a)/(double)n) * b * sqrt(pow(x/a, 2) - 1);
}
