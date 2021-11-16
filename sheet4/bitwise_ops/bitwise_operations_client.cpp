#include <iostream>
#include "bitwise_operations.hpp"
using namespace Bitwise_Operations;
using namespace std;
int main(){
    int n = 17;
    int m = 7;
    cout << "n = " << n << "\t" << ", m = " << m << endl;
    cout << "n + m = " << "\t";
    cout << bitwise_add(n,m) << endl;
    cout << "n x m = " << "\t";
    cout << bitwise_mult(n,m) << endl;
}