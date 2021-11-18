/**
 * @file root_finding.hpp
 * @author Carlo Musolino <musolino@itp.uni-frankfurt.de>
 * Solution to exercise 2 of sheet 4 for Advanced C++ course. Goethe University Frankfurt am Main.
 * Last checked 11.11.21 
 */
#ifndef _MY_ROOT_FINDING__
#define _MY_ROOT_FINDING__


#include<iostream>
#include<cassert>
#include<string>
#include<tuple>

namespace Root_Finding{
    /*
    * "using" alias-declaration (c++ 11): https://en.cppreference.com/w/cpp/language/type_alias
    * It's like typedef but you can make it templated for extra style points
    */
    template <class T> 
    using my_func_type=T (*)(T);
    // define some constants
    constexpr long int MAX_ITER = 10000; // max number of iterations for Root finding algorithm
    constexpr double DEFAULT_TOL = 1e-10; // default tolerance
    /**
     * @brief just a struct that prints an error message, a bad excuse to use throw
     */
    struct RootFinderError {
        std::string err;
        RootFinderError(std::string err_msg) : err(err_msg){ std::cerr << err << std::endl;};
    };
    /**
     * @brief First version of root_finding algorithm.
     * @param func pointer to function accepting one argument and returning a value of the same templated type. This is the function whose root we wish to find
     * @param x_low low end of the initial bracket, templated type
     * @param x_hi high end of the initial bracket, templated type
     * @param tol optional parameter to set the tolerance, defaults to DEFAULT_TOL
     * Loop up to a maximum of MAX_ITER times looking for the root of the input function func. Returns a std::tuple containing the root and the number of iterations performed.
     * Throws an error if the initial bracketing values are invalid or if convergence to the desired tolerance cannot be achieved.
     */
    template <typename T> std::tuple<T,unsigned int> root_finding(my_func_type<T> func,T x_low,T x_hi, const T tol=static_cast<T>(DEFAULT_TOL)){
        // pre-requirement assertion
        if((func(x_low) * func(x_hi))>0) 
        {   
            std::string errmsg = "The provided limits do not meet the requirement f(xl) * f(xh) < 0.";
            throw(RootFinderError{errmsg});
        }
        T x_m;
        T err = fabs(x_hi-x_low);
        int n_iter = 0;
        while((err>tol)&&(n_iter<MAX_ITER)){
            x_m = 0.5 * (x_hi + x_low);
            if((func(x_m) * func(x_hi))<0){
                x_low = x_m;
            } else {
                x_hi =x_m;
            }
            err = fabs(x_hi-x_low);
            n_iter++;
        }
        if(err>tol) {
            std::string errmsg = "Exceeded maximum number of iterations.";
            throw(RootFinderError{errmsg});
        }
        return std::make_tuple(x_m,n_iter); //std::make_tuple returns a tuple initialised from the values, to be compared with std::tie which returns a tuple of references !
    }

    /**
     * @brief Recursive version of root_finding algorithm.
     * @param func pointer to function accepting one argument and returning a value of the same templated type. This is the function whose root we wish to find
     * @param x_low low end of the initial bracket, templated type
     * @param x_hi high end of the initial bracket, templated type
     * @param tol optional parameter to set the tolerance, defaults to DEFAULT_TOL
     * Loop up to a maximum of MAX_ITER times looking for the root of the input function func. Returns a std::tuple containing the root and the number of iterations performed.
     * Throws an error if the initial bracketing values are invalid or if convergence to the desired tolerance cannot be achieved.
     */
    template <typename T> std::tuple<T,unsigned int> root_finding_recursive(my_func_type<T> func,T x_low,T x_hi, const T tol=static_cast<T>(DEFAULT_TOL)){

        if((func(x_low) * func(x_hi))>0) 
        {   
            std::string errmsg = "The provided limits do not meet the requirement f(xl) * f(xh) < 0.";
            throw(RootFinderError{errmsg});
        }
        T x_m = 0.5 * (x_hi + x_low);
        T err = fabs(func(x_m));
        int tmp;
        static int n_iter = 0;
        if((err>tol)&&(n_iter<MAX_ITER)) {
            n_iter++;
            if((func(x_m) * func(x_hi))<0){
                std::tie(x_m,tmp) = root_finding_recursive(func,x_m,x_hi,tol); 
                
            } else {
                std::tie(x_m,tmp) = root_finding_recursive(func,x_low,x_m,tol); 
            }
        }
        err = fabs(func(x_m)); // recalculate the error once we re-emerge on the other side! 
        if(err>tol) {
            std::string errmsg = "Exceeded maximum number of iterations.";
            throw(RootFinderError{errmsg});
        }
        return std::make_tuple(x_m,n_iter);
    }
}

#endif 
