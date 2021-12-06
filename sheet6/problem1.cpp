#include <iostream>
#include <string>
#include <stdio.h>
using namespace std;

class Animal
{

// Can only be accessed by base member functions
private:
    string name;
    int cageNumber;

// Can be accessed by both base member functions and derived classes
protected:
	int birthYear;

public:
    // Constructor
    Animal(string new_name, int new_cage, int new_birth_year)
    {	
    	name = new_name;
    	cageNumber = new_cage;
    	birthYear = new_birth_year;
    } 

    // Print animal's age given current year
    void printAge(int year)
    {
        int animal_age = year - birthYear;
        printf("Age of animal: %i \n", animal_age);  
        
    }

    // Print all properties of the animal
    void printData()
    {
        std::cout << "Animal nickname: " << name << endl;
        printf("Occupies cage number %i\n",  cageNumber );
        printf("Born on year %i\n",  birthYear );
    
    }

};


// Public Inheritence
class Wolf: public Animal
{
private:
	static int counter;
public:
    // Constructor
    Wolf(string new_name, int new_cage, int new_birth_year) : Animal(new_name, new_cage, new_birth_year)
    {
        cout << "New wolf added. " << endl;
        counter++;
        printf("Number of wolves: %i \n", counter); 

    }

	// Destructor
    ~Wolf() 
    {
        cout << "Wolf removed. " << endl;
        counter--;
        printf("Number of wolves: %i \n", counter);    
    }
    
    // Overriden member function
    void printAge(int year)
    {
        int animal_age = (year - birthYear)*7;
        printf("Age of animal: %i \n", animal_age);  
        
    }
        
    
};


int Wolf::counter = 0;

int main()
{	// Create an Animal instance and print its age and details
    Animal firstAnimal("George", 10, 2005);
    firstAnimal.printData();
    firstAnimal.printAge(2021);

	cout << endl;

	// Create a Wolf instance and print its age
	Wolf firstWolf("Sparky", 4, 2010);
	firstWolf.printData();
	firstWolf.printAge(2021);
	
	cout << endl;

	// Create a scond Wolf instance
	Wolf secondWolf("Toto", 4, 2013);
	
	cout << endl;
    
    return 0;
}
