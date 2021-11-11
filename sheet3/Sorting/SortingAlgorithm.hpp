/**
 * @file SortingAlgorithm.hpp 
 * @author Carlo Musolino (musolino@itp.uni-frankfurt.de)
 * @brief Implementation of various sorting algorithms  
 */

#ifndef _MY_SORTING_HPP_
#define _MY_SORTING_HPP_

#include <cmath>
#include <iostream>
#include <vector>
#include <string>
#include <memory>
#include <algorithm>
#include <cassert>
#include <list>

namespace MySorting{
// =============================================================== 
//function declarations, our sorting algorithms! 
// =============================================================== 
/**
 * @brief implementation of the Radix (or bucket) sort algorithm
 * @param data input/output vector
 */
void radix_sort(std::vector<int>& data);
/**
 * @brief implementation of the Bubble sort algorithm
 * @param data input/output vector
 */
template <typename T> void bubble_sort(std::vector<T>& data);
// =============================================================== 
// Some utilities needed by the two main functions
// =============================================================== 
/**
 * @brief swaps two elements of a vector
 * @param data input/output vector
 * @param i first index
 * @param j second index
 */
template <typename T> inline void swap_elements(std::vector<T>& data,int i,int j);
/**
 * @brief returns k-ths Least Significant Bit from input integer
 * @param N input integer
 * @param k which bit?
 */
inline bool LSB(const int N,const int k);
/**
 * @brief Main driver routine for radix sort, does all the book-keeping with the two bins
 * @param b0 reference to bin-0
 * @param b1 reference to bin-1
 * @param k depth
 */
void radix_sort_driver(std::list<int> &b0, std::list<int> &b1, int k);
}
// =============================================================== 
//function definitions
// =============================================================== 
// First some utilities, all pretty self-explanatory
template <typename T> void print_vector(const std::list<T>& x) {
    for(auto& val : x) std::cout << val << "\t";
    std::cout << std::endl;
}
template <typename T> void print_vector(const std::vector<T>& x) {
    for(auto& val : x) std::cout << val << "\t";
    std::cout << std::endl;
}
inline bool MySorting::LSB(const int N, const int k = 1 ){
    return ( N & ( 1 << (k-1) ) ); // ... some bit-wise dark magic 
}
template <typename T> void MySorting::swap_elements(std::vector<T>& data,int i,int j){
    T tmp = data[i];
    data[i] = data[j];
    data[j] = tmp;
}
// =============================================================== 
// Driver for radix sorter, this is where we do most of the work
void MySorting::radix_sort_driver(std::list<int>& b0, std::list<int>& b1, int k)
{   
    // loop over bin 0, check for elements that need to be moved  
    for(auto it = b0.begin();it != b0.end(); it ++) {
        auto val = *it;
        if(LSB(val,k)) {
            b1.push_front(val); // we append to the front, this is why we have to use std::list !
            b0.erase(std::remove(b0.begin(),b0.end(),val),b0.end()); // C++ magic that removes the element from the bin
            it--; // this is vital, can you figure out why??
        }
    }
    // loop over bin 1, check for elements that need to be moved  
    for(auto it = b1.begin();it != b1.end(); it ++) {
        auto val = *it;
        if(!(LSB(val,k))) {
            b0.push_back(val);
            b1.erase(std::remove(b1.begin(),b1.end(),val),b1.end());
            it--;
        }
    }
}
// =============================================================== 
// User interface for radix and bubble sort
// =============================================================== 
void MySorting::radix_sort(std::vector<int>& data){
    using bucket = std::list<int>; // just convenient, now you know :) 
    bucket b0,b1;
    // Initial run through the data, assign each number to a bin
    for( auto& val : data) LSB(val) ? b1.push_back(val) : b0.push_back(val) ; // range-based for loop (--std=c++11 or newer)
    // main loop, we need to go all the way to the size of an int in bits ! ( why? )
    for (int i = 1; i<=8*sizeof(int); i++) {
        radix_sort_driver(b0,b1,i); // separate function with the ugly stuff
        }
    //move data to output 
    data.clear();
    for(auto & val: b0) data.push_back(val);
    // sanity check!
    assert(!b1.size());
}
template<typename T> void MySorting::bubble_sort(std::vector<T>& data){
    int n = data.size();
    bool did_swap = true; // we stop after a whole scan of the data where we do nothing 
    while(did_swap){
        did_swap = false;
        int new_n; 
        for (int i=1; i < n; i++){
            if(data[i-1]>data[i]){
                swap_elements(data,i-1,i);
                new_n = i; // for i > new_n we don't need to check! 
                did_swap = true;
            }
        }   
        n = new_n; // set for-loop range to new_n
    }
}
// =============================================================== 
// =============================================================== 
// END OF FILE 
// =============================================================== 
// =============================================================== 
#endif