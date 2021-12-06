#pragma once

namespace truncation_tests{
    template <typename T>
    T summation(const int N ) { 
        T sum = 0;
        #pragma omp parallel for reduction(+:sum)
        for (int i=1; i<N; i++){
            sum += static_cast<T>(1./i);
        }
        return sum;
    }

}