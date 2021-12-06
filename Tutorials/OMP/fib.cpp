#include <iostream>
#include <chrono>
#include "fibonacci.hpp"

using std::cout, std::endl;
using namespace Fibonacci;
int main(){
    constexpr const int MY_LARGE_N = 45;
    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
    cout << fib(MY_LARGE_N) << endl;
    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
    std::cout << "Time difference = " << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() << "[µs]" << std::endl;

    begin = std::chrono::steady_clock::now();
    #pragma omp parallel 
    {
    #pragma omp single
    {
    cout << fib_omp(MY_LARGE_N) << endl; 
    }
    }
    end = std::chrono::steady_clock::now();
    std::cout << "Time difference = " << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() << "[µs]" << std::endl;
}