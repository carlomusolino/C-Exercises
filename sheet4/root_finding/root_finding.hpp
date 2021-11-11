#ifndef _MY_ROOT_FINDING__
#define _MY_ROOT_FINDING__


#include<iostream>
#include<cassert>
#include<string>
#include<tuple>

namespace Root_Finding{

    constexpr long int MAX_ITER = 1000000;
    constexpr double DEFAULT_TOL = 1e-10;

    struct RootFinderError {
        std::string err;
        RootFinderError(std::string err_msg) : err(err_msg){ std::cout << err << std::endl;};
    };

    template <typename T> std::tuple<T,unsigned int> root_finding(T (*func)(T),T x_low,T x_hi, const T tol=static_cast<T>(DEFAULT_TOL)){
        // pre-requirement assertion
        if((func(x_low) * func(x_hi))>0) 
        {   
            std::string errmsg = "The provided limits do not meet the requirement f(xl) * f(xh) < 0.";
            throw(RootFinderError{errmsg});
        }
        T x_m;
        T err = 1.;
        int n_iter = 0;
        while((err>tol)&&(n_iter<MAX_ITER)){
            x_m = 0.5 * (x_hi + x_low);
            if((func(x_m) * func(x_hi))<0){
                x_low = x_m;
            } else {
                x_hi =x_m;
            }
            err = fabs(func(x_m));
            n_iter++;
        }
        if(err>tol) {
            std::string errmsg = "Exceeded maximum number of iterations.";
            throw(RootFinderError{errmsg});
        }
        return std::make_tuple(x_m,n_iter);
    }


    template <typename T> std::tuple<T,unsigned int> root_finding_recursive( T (*func)(T),T x_low,T x_hi, const T tol=static_cast<T>(DEFAULT_TOL)){

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