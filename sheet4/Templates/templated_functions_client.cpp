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
    // it's very important to declare this a constexpr! This way the COMPILER can substitute this for the template/array declaration parameter
    constexpr int MY_ARR_SIZE = 10; // since c++ 11: https://en.cppreference.com/w/cpp/language/constexpr
    int arr[MY_ARR_SIZE] {1,2,3,4,5,6,7,8,9,10};
    cout << "Print 1-d array: " << endl << endl ;
    Templated_Functions::print_array<int,MY_ARR_SIZE>(arr); // re-iterating: we can do this because MY_ARR_SIZE is declared constexpr
    cout << endl << endl;
    //2-D array version
    constexpr int MY_OTHER_ARR_SIZE = 3; // it's very important to declare this a constexpr! This way the COMPILER can substitute this for the template parameter
    int twoD_arr[MY_OTHER_ARR_SIZE][MY_ARR_SIZE]; 
    for (int i= 0; i < MY_OTHER_ARR_SIZE; i++) for(int j = 0; j < MY_ARR_SIZE; j++)  twoD_arr[i][j] = arr[j]; 
    cout << "Print 2-d array: " << endl << endl;
    Templated_Functions::print_2d_array<int,MY_OTHER_ARR_SIZE,MY_ARR_SIZE>(twoD_arr);
    cout << endl << endl;
    // std::array version
    std::array<int,MY_ARR_SIZE> cpp_arr{11,12,13,14,15,16,17,18,19,20};
    cout << "Print C++ std::array: " << endl << endl;
    Templated_Functions::print_std_array<int,MY_ARR_SIZE>(cpp_arr);
    cout << endl << endl;
    // Bye ! 
}