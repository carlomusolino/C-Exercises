/*  @author: Arijit Dutta
 *  @created: 09.01.2022
 *  @modified: 09.01.2022
 */
#include <iostream>
#include <iomanip>
#include <vector>

template<typename T>
std::vector<std::vector<T>> gaussInversion(std::vector<std::vector<T>>& A, const int& N) {
	/** generate augmented matrix (A|I) **/
	std::vector<std::vector<double>> A_I (N,std::vector<double>(2*N));
	for (int r = 0; r < N; r++) {
		for (int c = 0; c < N; c++) { A_I[r][c] = A[r][c]; }
		for (int c = N; c < 2*N; c++) {
			if (c == (r + N)) { A_I[r][c] = 1; }
			else { A_I[r][c] = 0; }
		}
	}
	std::cout << "Augmented matrix (A|I):" << std::endl;
	for(int r = 0; r < N; r++) {
		for(int c = 0; c < 2*N; c++) {
			std::cout << std::setw(15) << A_I[r][c] << '\t';
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;

	/*** pivot ***/
	double tol = 1.e-10; // tolerance
	for (int c = 0; c < N; c++) {
		int pivot = c;
		for (int r = c+1; r < N; r++) { 
			if (std::abs(A_I[r][c]) > std::abs(A_I[pivot][c])) { 
				pivot = r; 
			} 
		}
		for (int n = 0; n < 2*N; n++) { 
			T swap = A_I[c][n]; 
			A_I[c][n] = A_I[pivot][n];
			A_I[pivot][n] = swap;
		}

		if (abs(A_I[c][c]) <= tol) {
			std::cout << "Matrix is nearly singular!" << std::endl;
		}
	}
	std::cout << "Augmented matrix after pivoting (A|I)_P:" << std::endl;
	for(int r = 0; r < N; r++) {
		for(int c = 0; c < 2*N; c++) {
			std::cout << std::setw(15) << A_I[r][c] << '\t';
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
	
	/********** triangulate ***********/
	for (int r = 0; r < N; r++) {
		for (int n = r+1; n < N; n++) {
			if (A_I[r][r] != 0) {
				T coeff = A_I[n][r] / A_I[r][r];
        		for (int c = 0; c < 2*N; c++) {
					A_I[n][c] -= (coeff * A_I[r][c]);
            	}
			} else {
				std::cout << "Matrix not invertible" << std::endl;
				exit(EXIT_FAILURE);
			}
    	}
	}
	std::cout << "Pivoted augmented matrix after triangulation [(A|I)_P]_T:" << std::endl;
	for (int r = 0; r < N; r++) {
        for (int c = 0; c < 2*N; c++) {
				std::cout << std::setw(15) << A_I[r][c] << '\t';
    	}
		std::cout << std::endl;
	}
	std::cout << std::endl;
    /************** solve for unit matrix *************/
    for (int r = N-1; r >= 0; r--) {
        T d = A_I[r][r];
		if (d != 0) {
        	for (int c = r; c < 2*N; c++) { A_I[r][c] /= d; }
    		for (int n = r-1; n >= 0; n--) {
				if (A_I[n][r] != 0) { 
					T coeff = A_I[n][r];
        			for (int c = r; c < 2*N; c++)
            			A_I[n][c] -= (coeff * A_I[r][c]);
				}
			}
		} else {
			std::cout << "Matrix not invertible" << std::endl;
			exit(EXIT_FAILURE);
		}
	}
	std::cout << "Final form of augmented matrix:" << std::endl;
	for(int r = 0; r < N; r++) {
		for(int c = 0; c < 2*N; c++) {
			std::cout << std::setw(15) << A_I[r][c] << '\t';
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;

	std::vector<std::vector<double>> Ainv (N,std::vector<double>(N));
	for(int r = 0; r < N; r++) {
		for(int c = 0; c < N; c++) {
			Ainv[r][c] = A_I[r][c+N];
		}
	}
	return Ainv;
}

int main() {
	std::cout << "Enter dimension of the (square) matrix : ";
	int N;
	std::cin >> N;

	std::cout << "Enter matrix elements row-wise (datatype double). A :" << std::endl;
	std::vector<std::vector<double>> A(N,std::vector<double>(N));
	for(int r = 0; r < N; r++) {
		for(int c = 0; c < N; c++) {
			std::cin >> A[r][c];
		}
	}

	auto Ainv = gaussInversion(A, N);
	std::cout << "Matrix inverse. A^-1 :" << std::endl;
	for(int r = 0; r < N; r++) {
		for(int c = 0; c < N; c++) {
			std::cout << std::setw(15) << Ainv[r][c] << '\t';
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;

	std::cout << "Check inverse. A * A^-1:" << std::endl;
	std::vector<std::vector<double>> I(N,std::vector<double>(N,0.0));
	for(int r = 0; r < N; r++) {
		for(int c = 0; c < N; c++) {
			for(int k = 0; k < N; k++)
				I[r][c] += (A[r][k] * Ainv[k][c]);
			std::cout << std::setw(15) << I[r][c] << '\t';
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;

	return 0;
}
