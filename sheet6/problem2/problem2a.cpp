#include <iostream>
#include <cstdio>
#include <limits>


using namespace std;


int main ()
{
   printf("size of float       %ld\n", sizeof(float) );
   printf("size of double      %ld\n", sizeof(double) );
   printf("size of long double %ld\n\n", sizeof(long double) );

   printf(" float        digits10      :  %d \n", numeric_limits<float>::digits10);
   printf(" double       digits10      :  %d \n", numeric_limits<double>::digits10);
   printf(" long double  digits10      :  %d \n\n", numeric_limits<long double>::digits10);

   int counter;
   for(int i=0; i<4; i++){

      if(i==0) counter = 16;
      if(i==1) counter = 512;
      if(i==2) counter = 333;
      if(i==3) counter = 100000;

      float        f = 1.0/counter;
      double       d = 1.0/counter;
      long double ld = 1.0/counter;

      float        sum_f = 0;
      double       sum_d = 0;
      long double sum_ld = 0;
      
      /** Adding numbers up to 1.0 */
      for (int j=0; j<counter; j++)
      {
         sum_f  += f;
         sum_d  += d;
         sum_ld += ld;
      }
      printf("Summing over  1/%d\n",counter);
      printf("result of summing over       float:   sum = %.6f\n",sum_f);
      printf("result of summing over      double:   sum = %.15f\n",sum_d);
      printf("result of summing over long double:   sum = %.18Lf\n\n",sum_ld);

   }

   return 0;
}
