#include <iostream>
#include <exception>

using namespace std;

int main()
{
	int x;
	// make failbit to throw exception
	cin.exceptions(ios::failbit);

	try {
		cout << "Enter an integer" << endl;
		cin >> x;
		if(std::cin.peek() != '\n') {// Modified by Arijit
			throw std::iostream::failure("real number ");
        } else { std::cout << "Input = " << x << std::endl; }
	}
	catch (ios_base::failure &fb) {
		cout << "Exception caught: " << fb.what() << endl;
		cin.clear();
	}

	return 0;
}
