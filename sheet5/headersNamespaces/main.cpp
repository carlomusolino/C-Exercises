#include "matrices.hpp"

int main() {
	srand(time(NULL)); // initialised outside (once and for all)
	std::vector< std::vector< int > > A(4,std::vector< int >(4,555));// remember to always initialise your vectors. Very important if using parallelisation!!
	mat::randMat(A);
	
	std::cout << "First matrix (A) :" << std::endl; 
	mat::printMatrix(A);

	std::vector< std::vector< int > > B(4,std::vector< int >(4,555));
	mat::randMat(B);
	
	std::cout << "Second matrix (B) :" << std::endl; 
	mat::printMatrix(B);


	std::vector< std::vector< int > > C = mat::matMul<int>(A,B);
	std::cout << "Matrix product (C = A . B) :" << std::endl; 
	mat::printMatrix(C);

	return 0;
}
