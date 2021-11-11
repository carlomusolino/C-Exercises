/**
 * @file bitwise_ops.hpp
 * @author Carlo Musolino <musolino@itp.uni-frankfurt.de>
 * Solution to exercise 3 of sheet 4 for Advanced C++ course. Goethe University Frankfurt am Main.
 * Last checked 11.11.21 
 */
#ifndef _MY_BITWISE_OPERATIONS__
#define _MY_BITWISE_OPERATIONS__

namespace Bitwise_Operations{
    /**
     * @brief add two integers using only bitwise operations
     * @param n first addend
     * @param m second addend
     * The sum is just a bitwise xor. However one needs save the carry (bitwise and shifted left by one bit)
     * and add it to the result. The function achieves this by using recursion 
     */
    int bitwise_add(int n, int m){
        static int count = -1; // count is static because the function recursively calls itself
        int sum = n ^ m;
        int carry = (n & m) << 1 ; // shift the carry left by one ! 
        count ++ ;
        if (count < 8 * sizeof(int)) sum = bitwise_add(sum,carry);
        return sum;
    }
    /**
     * @brief Return kth-Least Significant Bit of input integer n
     * @param n input integer
     * @param k shift 
     * Needed by bitwise_mult. Performs some dark magic trick to return all 0 bits or all 1 bits according 
     * to the value of n's kth LSB.
     */
    int LSB(int n, int k){ return ( (n & ( 1 << k))?~0:0 ) ; } // Advanced Dark magic 
    /**
     * @brief multiply two integers using only bitwise operations
     * @param n first integer number
     * @param m second integer number
     * We sum together (using bitwise_add) partial products obtained by a bitwise and of n and the kth 
     * bit of m, shifted by k.
     */
    int bitwise_mult(int n, int m) {
        int result = 0; 
        for ( int k =0; k < 8 * sizeof(int); k++) result = bitwise_add(result,((n&LSB(m,k))<<k)); // Advanced Dark Magic pt.2 
        return result;
    }
}
#endif