#include "vec_types.hpp"
#include <vector>
#include <iostream>

using namespace FourVectors;
using std::cout, std::endl;

int main(){

    Vect<double,upper_t> v1({1,0,1,0});
    Vect<double,upper_t> v2({0,2,2,0});

    cout << v1[0] << endl;

    //Vect<double,upper_t> w = VectSum(v1,v2);
    //Vect<double,lower_t> wrong = VectSum(v1,v2);
    Vect<double,upper_t> w = v1+v2;
    cout << w[2] << endl;

    Vect<double,lower_t> z({1,0,2,0});

    Scalar s = VectContraction(z,v1+v2).eval() ; 
    cout << s.val() << endl ;


}