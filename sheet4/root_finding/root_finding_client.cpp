#include<iostream>
#include<math.h>
#include <iomanip> 
#include <tuple>

#include"root_finding.hpp"

using namespace Root_Finding;
using std::cout, std::endl;

int main() {
    cout << std::setprecision(11);

    double x_low = -3.;
    double x_hi  = 0.;

    double root;
    unsigned int niter;

    auto func = [](double x) -> double {return (std::pow(x,3) - 2 * x + 5);} ;

    std::tie(root,niter) = root_finding<double>(func,x_low,x_hi);
    cout << "Non recursive:" << endl << endl;
    cout << "Root: " << root << endl;
    cout << "n_iter: " << niter << endl;

    std::tie(root,niter) = root_finding_recursive<double>(func,x_low,x_hi);
    cout << "Recursive:" << endl << endl;
    cout << "Root: " << root << endl;
    cout << "n_iter: " << niter << endl;

    cout << func(0.) << "\t" << func(-1.5) << endl ;

}