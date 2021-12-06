#include<iostream>
#include <chrono>
#include "chebyshev_poly_templates.hpp"

using namespace TemplatedChebyshev;
using std::cout, std::endl;
int main(){
    constexpr int MY_LARGE_N = 50;
    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
    cout << Tn<MY_LARGE_N>(0.) << endl;
    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
    std::cout << "Time difference = " << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() << "[µs]" << std::endl;

    begin = std::chrono::steady_clock::now();
    cout << Tn_notemp<double>(0.,MY_LARGE_N) << endl;
    end = std::chrono::steady_clock::now();
    std::cout << "Time difference = " << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() << "[µs]" << std::endl;
}
