#include<iostream>
#include<math.h>
#include <iomanip> 
#include <tuple>

#include"root_finding.hpp"

using namespace Root_Finding;
using std::cout, std::endl;

int main() {
    cout << std::setprecision(16);

    double x_low = -3.;
    double x_hi  = 0.;

    double root;
    unsigned int niter;

    /* Define a lambda (c++ 11): https://en.cppreference.com/w/cpp/language/lambda
    * constructs a function local (on-stack) function object.
    * The square brackets are used to capture in-scope variables, the arrow syntax is for return type
    * We also use the auto type declaration (c++ 11 ) : https://en.cppreference.com/w/cpp/language/auto
    * auto means that the compiler needs to be able to deduce the type from the initialisation --> You ALWAYS need
    * to initialise a variable declared as auto.
    */
    auto func = [](double x) -> double {return (pow(x,3) - 2 * x + 5);} ;
    cout << "f(x) = x^3 - 2x + 5" << endl;
    /* std::tie creates a tuple of references : https://en.cppreference.com/w/cpp/utility/tuple/tie
    * This is why we use std::make_tuple in the function return statement! 
    */
    std::tie(root,niter) = root_finding<double>(func,x_low,x_hi);
    cout << "Non recursive:" << endl;
    cout << "Root: " << root << endl;
    cout << "n_iter: " << niter << endl << endl;

    std::tie(root,niter) = root_finding_recursive<double>(func,x_low,x_hi);
    cout << "Recursive:" << endl;
    cout << "Root: " << root << endl;
    cout << "n_iter: " << niter << endl << endl;

    cout << "Root up to a bunch of significant digits (according to Mathematica): " << -2.09455148154233 << endl ;

    x_low = 1.7; x_hi=5.;
    auto func2 = [](double x) -> double {return (pow(x,5) - 7 * pow(x,3) + 9);} ;

    std::tie(root,niter) = root_finding<double>(func2,x_low,x_hi);
    cout << "Non recursive:" << endl;
    cout << "Root: " << root << endl;
    cout << "n_iter: " << niter << endl << endl;

    std::tie(root,niter) = root_finding_recursive<double>(func2,x_low,x_hi);
    cout << "Recursive:" << endl;
    cout << "Root: " << root << endl;
    cout << "n_iter: " << niter << endl << endl;

    cout << "Root up to a bunch of significant digits (according to Mathematica): " << 2.5398163645687731251 << endl ;

    x_low = 1.; x_hi=5.;

    /*
    * Basic (and quite useless) example of exception handling ,try doing the same without the try-catch
    */
    try{
        std::tie(root,niter) = root_finding<double>(func2,x_low,x_hi);
    } catch (RootFinderError) {
        cout << "Oops, my bad." << endl;
    }

}
