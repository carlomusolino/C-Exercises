#include <array>
#include <iostream>

#include "templated_functions.hpp"

using std::cout, std::endl;

int main() {
    // Templated product function
    int i = 10; int j = 15;
    double x = 10. ; double y = 15. ;
    cout << "Integers! " << Templated_Functions::product<int>(i,j) << endl;
    cout << "Doubles! " << Templated_Functions::product<double>(x,y) << endl;
    cout << endl << endl;
    // Array printing shenanigans 
    constexpr int MY_ARR_SIZE = 10; // it's very important to declare this a constexpr! This way the COMPILER can substitute this for the template parameter
    int arr[MY_ARR_SIZE] {1,2,3,4,5,6,7,8,9,10};
    cout << "Print 1-d array: " << endl << endl ;
    Templated_Functions::print_array<int,MY_ARR_SIZE>(arr);
    cout << endl << endl;
    /* DISCLAIMER: 
    * The author does not endorse usage of 2D c-style arrays in any sort of code that is not 
    * meant as an entry to the Obfuscated C contest.
    * https://www.ioccc.org/
    */
    constexpr int MY_OTHER_ARR_SIZE = 3; // it's very important to declare this a constexpr! This way the COMPILER can substitute this for the template parameter
    int twoD_arr[MY_OTHER_ARR_SIZE][MY_ARR_SIZE]; 
    for (int i= 0; i < MY_OTHER_ARR_SIZE; i++) for(int j = 0; j < MY_ARR_SIZE; j++)  twoD_arr[i][j] = arr[j]; 
    cout << "Print 2-d array: " << endl << endl;
    Templated_Functions::print_2d_array<int,MY_OTHER_ARR_SIZE,MY_ARR_SIZE>(twoD_arr);
    cout << endl << endl;
    // Bonus clip
    std::array<int,MY_ARR_SIZE> cpp_arr{11,12,13,14,15,16,17,18,19,20};
    cout << "Print C++ array: " << endl << endl;
    Templated_Functions::print_std_array<int,MY_ARR_SIZE>(cpp_arr);
    cout << endl << endl;
    // Bye ! 
}