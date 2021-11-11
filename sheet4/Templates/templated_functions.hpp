/**
 * @file templated_functions.hpp
 * @author Carlo Musolino <musolino@itp.uni-frankfurt.de>
 * Solution to exercise 1 of sheet 4 for Advanced C++ course. Goethe University Frankfurt am Main.
 * Last checked 11.11.21 
 */
#ifndef _MY_TEMPLATE_FUNCTIONS__
#define _MY_TEMPLATE_FUNCTIONS__

#include<iostream>
#include<array>

namespace Templated_Functions {
    template <class T> inline T product(T& x, T& y){
        return ( x * y ); 
    }
    template <class T, unsigned int N> void print_array( T arr[N]){
        for(int i=0; i<N; i++) std::cout << arr[i] << "\t";
        std::cout << std::endl;
    }

    template<class T, unsigned int N, unsigned int M> void print_2d_array(T arr[N][M]) {
        for(int i=0; i<N; i++) for(int j=0; j<M; j++){
            std::cout << arr[i][j] << "\t";
            if(j==M-1) std::cout<<std::endl<<std::endl;
        }
    }

    // Bonus clip: the C++ way of doing this
    template<typename T, unsigned int N> inline void print_std_array(std::array<T,N>& arr){
        for( const auto& val : arr ) std::cout << val << "\t";
        std::cout << std::endl;
    }
}
#endif