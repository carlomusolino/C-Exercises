/*
 * @file lambdas.cpp
 * @author Arijit Dutta <dutta@itp.uni-frankfurt.de>
 * Solution to exercise 2 of sheet 5 for Advanced C++ course. Goethe University Frankfurt am Main.
 * Last checked 22.11.21 
 */
#include <iostream>

auto templatedSum = []<class T>(T a, T b) { return a + b; }; // a templated lambda expression without capture
auto sum = templatedSum(2,3); // evaluation of the above lambda expression with int(s)
auto capture = [sum]<class T>(T b) { return sum + b; }; // C++ doesn't support templated capture till now. Replace 'sum' by 'templatedSum' and it will cry foul!
auto captureRef = [&sum]<class T>(T b) { return sum = b; };

int main() {
	// check the behaviour of 'auto' by changing the arguments
	std::cout << "Templated add 2.3 + 3.2 = " << templatedSum(2.3,3.2) << std::endl;
	std::cout << "Boring add 2 + 3 = " << sum << std::endl;
	std::cout << "Capture add [2 + 3] + 4.5 = " << capture(4.5) << std::endl;
	std::cout << "Capture by reference [2 + 3] = " << captureRef(23.2) << std::endl;

	return 0;
}
