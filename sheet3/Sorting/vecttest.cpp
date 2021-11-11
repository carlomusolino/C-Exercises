#include <vector>
#include <iostream>
#include <algorithm>
#include <list>

using std::vector, std::cout, std::endl, std::list;

bool isBig(int num){ return num>10;}
template <typename T> void print_vector(const list<T>& x) {
    for(auto& val : x) cout << val << "\t";
    cout << endl;
}
bool LSB(const int N, const int k = 1 ){
    return ( N & ( 1 << (k-1) ) );
}
int main(){
    list<int> a = { 1, 2, 3, 4, 5, 6, 7};
    list<int>::iterator it;

    print_vector<int>(a);
    for(auto& val: a){
        if(val%2) {
            it = std::remove(a.begin(),a.end(),val);
            a.erase(it,a.end());
        }
    }
    //
    print_vector<int>(a);
    
    cout << LSB(6,3) << endl;
}