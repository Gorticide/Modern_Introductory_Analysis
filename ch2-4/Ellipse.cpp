#include<iostream>
#include<cmath>

#include "Ellipse.h"
#include "Point.h"

Ellipse::Ellipse()                // Scope resolutin operator ::
    {}                        // constructor does nothing

int Ellipse::lcm(int x,int y, int z)
{
        long max,lcom, count, flag=0;
        if(x>=y&&x>=z)
                max=x;
        else if(y>=x&&y>=z)
                max=y;
        else if(z>=x&&z>=y)
                max=z;
        for(count=1;flag==0;count++)
        {
                lcom=max*count;
                if(lcom%x==0 && lcom%y==0 && lcom%z==0)
                {
                        flag=1;
                }
        }
        return lcom;
}
 
int Ellipse::hcf(int p, int q, int r)
{
        int gcf=1,flag=0, count;
        for(count=1; flag==0;count++)
        {
                if(p%count==0&&q%count==0&&r%count==0)
                        gcf=count;
                if(count>p&&count>q&&count>r)
                {
                        flag=1;
                }
        }
        return gcf;
}
 
 
Ellipse::Ellipse(Real a2, Real b2)  {     // Member function has access to private members
  _a = std::sqrt(a2);                        
  _b = std::sqrt(b2);
  
  if (b2 <= a2)  {
      _c = std::sqrt(a2-b2);
  }
  else {
    _c = std::sqrt(b2-a2);
  }
    int g = hcf((int)(a2*b2), (int)a2, (int)b2);
    _A = b2/(double)g;
    _B = a2/(double)g;
    _C = (a2 * b2)/(double)g;
}

Ellipse::Ellipse(Real A, Real B, Real C)  {
    _a = std::sqrt(C/A);
    _b = std::sqrt(C/B);

    if (A <= B) {
         _c = std::sqrt(_a*_a - _b*_b);
    }
    else {
       _c = std::sqrt(_b*_b - _a*_a);
     }

    _A = A;
    _B = B;
    _C = C;
}

Real Ellipse::a()  {
    return _a;
}

Real Ellipse::b()  {
    return _b;
}

Real Ellipse::c()  {
    return _c;
}

Real Ellipse::A()  {
    return _A;
}

Real Ellipse::B()  {
    return _B;
}

Real Ellipse::C()  {
    return _C;
}

Real Ellipse::distance(Point p)   {
    
    double d_max = 10000.0;

    if ( std::fabs(p.x() * p.y()) - 0.0 > 0.000001 )  {

        int increments = 50;
        double x_min = -(_a) + 0.0001;
        double x_max = _a;
        double x_range = x_max - x_min;
        double dx = x_range / increments;
        
        for (int i = 0; i <= increments; ++i)  {
            double x = x_min + i*dx;
            double y = std::sqrt( (_C - _A*x*x)/_B);
            double d = std::sqrt( (y - p.y()) * (y - p.y()) + (x - p.x()) * (x - p.x()) );
            if (d < d_max)  d_max = d;
            y = -y;
            d = std::sqrt( (y - p.y()) * (y - p.y()) + (x - p.x()) * (x - p.x()) );
            if (d < d_max)  d_max = d;
        }
    }
    else {
        if ( std::fabs( p.y() - 0.0 ) < 0.000001)  d_max = std::fabs( std::fabs(p.x()) - _a);
        else if ( std::fabs( p.x() - 0.0 ) < 0.000001)  d_max = std::fabs( std::fabs(p.y()) - _b);
    }
    //Real distance = (double)((int)(d_max*100 + 0.5)/100);
    int temp = (int)(d_max*100. + ((d_max < -0.005)? -.5 : .5));
    Real distance = (double)temp / 100.0;
    return distance;
}

std::ostream &operator<<(std::ostream &os, Ellipse &e)
{
      os << e.A() << "*x^2 + " << e.B() << "*y^2 = " << e.C();
      if (e.A() <= e.B() )  {
           os << "  <====>  [x^2]/[" << e.a() * e.a() << "] + [y^2]/[" << e.b() * e.b() << "] = 1";
      }
      else {
           os << "  <====>  [y^2]/[" << e.b() * e.b() << "] + [x^2]/[" << e.a() * e.a() << "] = 1";
      }
    

    return os;
}