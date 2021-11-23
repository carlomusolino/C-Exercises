/*
 * @file matrices.cpp
 * @author Arijit Dutta <dutta@itp.uni-frankfurt.de>
 * Solution to exercise 3 of sheet 5 for Advanced C++ course. Goethe University Frankfurt am Main.
 * Last checked 23.11.21 
 */
#include "matrices.hpp"

using namespace mat;

/* function to write a matrix (2d vector) 
 * with random entries in the range [0,10]
 * which is passed as an argument.
 */
void mat::randMat(std::vector< std::vector< int > >& matrix) {
	for(auto& row : matrix) { // iterate over rows of the matrix. Notice the '&'. This is necessary for assignment
		for(auto& col : row) { // iterate over elements of the vector 'row'
			col = rand() % 11; // rand() generates random integers between 0 and RAND_MAX. It is better to not use this for serious development.
		}
	}
}

/* function to multiply two 2d vectors
 * checks for dimensional consistency
 * throws an error otherwise
 * returns a 2d vector
 */
template <typename T> 
std::vector< std::vector < T > > mat::matMul(std::vector< std::vector < T > >& A, std::vector< std::vector < T > >& B) {
	if( A[0].size() != B.size()) { throw std::domain_error("No. of columns in A must be equal to no. of rows in B"); }

	std::vector< std::vector< T > > C(A.size(), std::vector< T >(B[0].size(),0)); //expecting a typecast
	for(int i = 0; i < C[0].size(); i++) // Its good to use the classic C++ for loop in this case IMHO.
		for(int j = 0; j < C.size(); j++)
			for(int k = 0; k < B.size(); k++)
				C[i][j] += (A[i][k] * B[k][j]);

	return C;
}

template std::vector< std::vector <int> > mat::matMul(std::vector< std::vector <int> >&,  std::vector< std::vector <int> >&); // explicit template instantiation. Price to pay for having a separate header file

/* function to pretty print a 2d vector */
template <typename T> 
void mat::printMatrix(const std::vector< std::vector< T > >& matrix) {
	std::cout << "-----------------------------------" << std::endl;
	for(auto row : matrix) {// iterate of rows. Notice the '&'. This is necessary for assignment
		for(auto col : row) {
			std::cout << col << '\t';
		}
		std::cout << std::endl;
	}
	std::cout << "-----------------------------------" << std::endl;
}
template void mat::printMatrix(const std::vector< std::vector<int > >&);
