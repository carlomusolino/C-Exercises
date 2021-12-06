/**
 * @file fibonacci.hpp
 * @author Carlo Musolino <musolino@itp.uni-frankfurt.de>
 * Just some examples of OMP Task-Based parallelism
 */
#ifndef __MY_FIB_HPP__
#define __MY_FIB_HPP__
#include "omp.h"
namespace Fibonacci{

    int fib(const int n){
        if (n<2) return n;
        int x,y;
        x = fib(n-1);
        y = fib(n-2);
        return x+y;
    }

    int fib_omp(const int n){
        if (n<2) return n;
        int x,y;
        #pragma omp task shared(x)
        {
        x = fib(n-1);
        }
        #pragma omp task shared(y)
        {
        y = fib(n-2);
        }
        #pragma omp taskwait
        return x+y;
    }
}

#endif