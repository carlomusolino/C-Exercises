/*
 * @file matrices.hpp
 * @author Arijit Dutta <dutta@itp.uni-frankfurt.de>
 * Solution to exercise 3 of sheet 5 for Advanced C++ course. Goethe University Frankfurt am Main.
 * Last checked 23.11.21 
 */
#ifndef _MATRICES__
#define _MATRICES__
#include <iostream>
#include <vector>

namespace mat {
	void randMat(std::vector< std::vector< int > >&);
	template <typename T> 
	std::vector< std::vector < T > > matMul(std::vector< std::vector < T > >&, std::vector< std::vector < T > >&);
	template <typename T> 
	void printMatrix(const std::vector< std::vector< T > >&);
}
#endif
