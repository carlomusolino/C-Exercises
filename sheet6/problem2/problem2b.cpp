#include <iostream>
#include <cstdio>
#include <cmath>
#include <limits>

using namespace std;


//   ((a+b)(a-b))²
template <typename T> 
T first (const T a, const T b)  { return pow( (a+b)*(a-b), 2 ); }

//   (a²+b²)² - 4(ab)²
template <typename T> 
T second (const T a, const T b)  { return pow( a*a + b*b, 2 ) - 4.0*pow(a*b,2); }

//   (a² - b²)²
template <typename T> 
T third (const T a, const T b)  { return pow( a*a - b*b, 2 ); }


int main() 
{

   printf("\nDOUBLE:\n");
   printf("   minimal value :  %e \n", numeric_limits<double>::min());
   printf("   maximal value :  %e \n", numeric_limits<double>::max());
   printf("   digits        :  %d \n", numeric_limits<double>::digits);
   printf("   digits10      :  %d \n", numeric_limits<double>::digits10);
   printf("\n\n");




   double a = 1.0e8 +2;
   double b = 1.0e8 -1;
   printf("CALCULATION:\nwith  a = %.1f,   b = %.1f\n\n", a, b);
   printf("   ((a+b)(a-b))²      =  %.17e\n" ,first(a,b) );
   printf("   (a²+b²)² - 4(ab)²  =  %.17e\n" ,second(a,b));
   printf("   (a² - b²)²         =  %.17e\n" ,third(a,b) );



   // Show Calculation in Detail:
   printf("\n\nSHOW CALCULATION IN DETAIL:\n");
   printf("   (a+b)              =  %.17e\n" , a+b );
   printf("   (a-b)              =  %.17e\n" , a-b );
   printf("   (a+b)(a-b)         =  %.17e\n" , (a+b)*(a-b) );
   printf("   ((a+b)(a-b))²      =  %.17e\n\n" ,first(a,b) );

   printf("   (a*a)              =  %.17e\n" , a*a );
   printf("   (b*b)              =  %.17e\n" , b*b );
   printf("   (a*a)+(b*b)        =  %.17e\n" , (a*a)+(b*b) );
   printf("   (a²+b²)²           =  %.17e   <--- attention\n" , pow((a*a)+(b*b), 2) );
   printf("   4*(a*b)²           =  %.17e   <--- attention\n" , 4.0*pow(a*b,2) );
   printf("   (a²+b²)² - 4(ab)²  =  %.17e\n\n" ,second(a,b));

   printf("   (a*a)              =  %.17e\n" , a*a );
   printf("   (b*b)              =  %.17e\n" , b*b );
   printf("   (a² - b²)          =  %.17e\n" , a*a-b*b );
   printf("   (a² - b²)²         =  %.17e\n\n" ,third(a,b) );

   return 0;
}

