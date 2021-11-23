/*
 * @file stringSort.cpp
 * @author Arijit Dutta <dutta@itp.uni-frankfurt.de>
 * Solution to exercise 1 of sheet 5 for Advanced C++ course. Goethe University Frankfurt am Main.
 * Last checked 22.11.21 
 */
#include <iostream>
#include <string>
#include <vector>
#include <algorithm> // STL for sorting etc.

bool compStr(std::string A, std::string B) { return A.length() < B.length(); } // See what I did there ? A logical expression automatically evaluates to bool 

bool compStrLex(std::string A, std::string B) { return A < B; } // string comparison: look it up https://www.cplusplus.com/reference/string/string/operators/

int main(int argc, char* argv[]) {
	std::vector<std::string> X;
	for(int i = 1; i < argc; i++)
		X.push_back(argv[i]);

	std::cout << "Original string :" << std::endl;
	for(int i = 0; i < argc; i++)
		std::cout << X[i] << " ";
	std::cout << std::endl << std::endl;

	std::cout << "Sorted by length of words :" << std::endl;
	std::sort(X.begin(), X.end(), compStr); // look it up https://en.cppreference.com/w/cpp/algorithm/sort
	for(int i = 0; i < argc; i++)
		std::cout << X[i] << " ";
	std::cout << std::endl << std::endl;

	std::cout << "Sorted l e x i c o g r a p h i c a l l y :" << std::endl;
	std::sort(X.begin(), X.end(), compStrLex);
	for(int i = 0; i < argc; i++)
		std::cout << X[i] << " ";
	std::cout << std::endl << std::endl;
	return 0;
}
// needs better commenting for Doxy.. too lazy
