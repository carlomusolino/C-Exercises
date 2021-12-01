#include <bitset>
#include <iostream>
#include <climits>

/** Discussion:
 * Truncation errors occur for 1/333 and 1/100000 
 * since the numbers are infinitely long in binary representation 
 * or more binary digits are needed for the number in 
 * the binary representation.
 * Convince yourself by running the code.
 */

template <typename T>
void show_binrep(const T& a)
{
   const char* beg = reinterpret_cast<const char*>(&a);
   const char* end = beg + sizeof(a);
   while(beg != end)
      std::cout << std::bitset<CHAR_BIT>(*beg++) << ' ';
   std::cout << '\n';
}



int main(){
   
   double a=1/double(16), b =  1/double(512), c=1/double(333), d=1/double(100000);
   std::cout << "binary representation of 1/16 " << std::endl;
   show_binrep(a);
   std::cout << "binary representation of 1/512 " << std::endl;
   show_binrep(b);
   std::cout << "binary representation of 1/333 " << std::endl;
   show_binrep(c);
   std::cout << "binary representation of 1/100000 " << std::endl;
   show_binrep(d);
   
   return 0;

}

