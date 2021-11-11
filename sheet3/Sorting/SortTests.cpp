#include "SortingAlgorithm.hpp"
#include <stdlib.h>
#include <time.h>

using namespace MySorting;

// test some "subroutines"
using std::cout, std::endl, std::vector;

inline void initialise_rand(vector<int>& X, const int N);
//template <typename T> void print_vector(const std::vector<T>& x);

int main(){
    vector<int> X {4, 2, 6, 1, 3, 19, 198 ,1992, 74, 7};
    vector<int> Y = X;
    vector<int> Z = X;

    radix_sort(Y);
    bubble_sort(Z);
    cout << "Original data:" << endl;
    print_vector<int>(X);
    cout << "Radix Sort:" << endl;
    print_vector<int>(Y);
    cout << "Bubble sort:" << endl;
    print_vector<int>(Z);
}

inline void initialise_rand(vector<int>& X, const int N){
    srand(time(NULL));
    for (int i=0; i<N; i++) X.push_back(rand()%10) ;
}


