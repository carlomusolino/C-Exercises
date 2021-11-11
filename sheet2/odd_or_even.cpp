#include <iostream>
using std::cout, std::cin;
// Enter integer to run program, q exit quit foo pippo to exit
int main(){
    int arg;
    while (cin >> arg) cout << ((arg%2) ? "odd!\n" : "even!\n");
};