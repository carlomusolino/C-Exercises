
#include <cmath>
#include <iostream>
#include <iomanip>
#include "truncation_errors.hpp"


using namespace truncation_tests;
using namespace std;

template<class T>
auto f1 = [] (const T& a, const T& b) { return pow((a+b)*(a-b),2);};

template<class T>
auto f2 = [] (const T& a, const T& b) { 
    return pow(pow(a,2)+pow(b,2),2) - 4*pow(a*b,2);
};

template<class T>
auto f3 = [] (const T& a, const T& b) { return pow(pow(a,2)-pow(b,2),2);};

int main(){
    cout << setprecision(17) ; 
    cout << "To 16 <float>: " << summation<float>(16) << endl;
    cout << "To 16 <double>: " << summation<double>(16) << endl;
    cout << "To 16 <long double>: " << summation<long double>(16) << endl;
    cout << endl;
    cout << "To 512 <float>: " << summation<float>(512) << endl;
    cout << "To 512 <double>: " << summation<double>(512) << endl;
    cout << "To 512 <long double>: " << summation<long double>(512) << endl;
    cout << endl;
    cout << "To 333 <float>: " << summation<float>(333) << endl;
    cout << "To 333 <double>: " << summation<double>(333) << endl;
    cout << "To 333 <long double>: " << summation<long double>(333) << endl;
    cout << endl;
    cout << "To 100k <float>: " << summation<float>(100000) << endl;
    cout << "To 100k <double>: " << summation<double>(100000) << endl;
    cout << "To 100k <long double>: " << summation<long double>(100000) << endl;
    cout << endl;
    double a = 1e08 + 2;
    double b = 1e08 - 1;
    cout << endl;
    cout << "f1: " << f1<double>(a,b) << endl;
    cout << "f2: " << f2<double>(a,b) << endl;
    cout << "f3: " << f3<double>(a,b) << endl;
    cout << endl;
    cout << "a^2 = " << pow(a,2) << endl; 
    cout << "b^2 = " << pow(b,2) << endl; 
    cout << "(a^2 + b^2)^2 = " << pow(pow(a,2)+pow(b,2),2) << endl; 
    cout << "ab = " << a*b << endl; 
    cout << "4 ab^2 = " << 4*pow(a*b,2) << endl;
}
