#include<iostream>
#include<string>
#include<memory>

#include "animals.hpp"

using namespace Animals;
using std::cout, std::endl;

int main(){

    { // unnamed scope, just like any other scope in C++ 
    std::unique_ptr<Animal> mywolf { new Wolf("pippo",2008,101) };
    
    mywolf->print_data();
    mywolf->print_age(2021);
    } // the destructors will be called here, but in what order?? 


}