/**
 * @file animals.hpp
 * @author Carlo Musolino <musolino@itp.uni-frankfurt.de>
 * @brief Example of class hierarchy. Exercise sheet 6 of Advanced C++ course Goethe University Frankfurt 
 */
#pragma once
#include <string>
#include <iostream>
namespace Animals {
    /**
     * @brief Animal base class. 
     */
    class Animal {  
        static int total_count;
        int cage_number;
        protected:
        std::string name;
        int birth_year;
        public:
        /**
         * @brief Standard constructor
         * @param n string containing the name of the animal
         * @param y integer, the year it was born
         * @param cn integer, the cage number it lives in
         */
        Animal(std::string n, int y, int cn): cage_number(cn), name(n), birth_year(y){ total_count++; };
        /**
         * @brief General access method, displays information about the animal
         * The const qualifier tells the compiler that this method does not modify
         * the class's member data
         */
        void print_data() const { 
            std::cout << "Birth year: " << birth_year << std::endl;
            std::cout << "Name: " << name << std::endl;
            std::cout << "Office number: " << cage_number << std::endl;
        }
        /**
         * @brief General access method, displays the animal's age
         * @param current_year what year is it?
         * The virtual qualifier tells the compiler that this method will
         * be redefined by derived classes
         */
        virtual void print_age(int current_year) const { 
            std::cout << name << " is " << current_year-birth_year << " years old."<< std::endl;
        }
         /**
         * @brief Default destructor
         */
        virtual ~Animal() {
            total_count--;
            std::cout << name << " has died :( . "<< "There are now " << total_count << " animals in the zoo" << std::endl;
            std::cout << "Do you see why I need to be virtual now??" << std::endl;
            
        }
    };

    class Wolf: public Animal {
        static int counter;
        public:
        Wolf(std::string n,  int y, int cn): Animal(n,y,cn) { 
            counter++; 
            std::cout << name << " was born. "<< "There are now " << counter << " wolves in the zoo" << std::endl;
        };
        void print_age(int current_year) const { 
            std::cout << name << " is " << 7*(current_year-birth_year) << " years old."<< std::endl;
        }
        virtual ~Wolf(){
            counter--;
            std::cout << name << " has died :( . "<< "There are now " << counter << " wolves in the zoo" << std::endl;
        }
    };
    int Wolf::counter = 0;
    int Animal::total_count = 0;
    /*
    * What follows is a brief rant about class inheritance in c++ . Feel free to skip it.
    *
    * tl;dr the virtual specifier is important when dealing with complex class inheritance.
    * 
    * As you can see, I declared two functions in the Base class Animal to be virtual. 
    * This essentially tells the compiler that these functions will be overridden in some derived class (e.g. Wolf). But why is this important?
    * If in your code you instantiate a Wolf object as:
    * Animals::Wolf w{"pippo",2001,101} ;
    * And then call a method :
    * w.print_age(2021);
    * Then the version of print_age found in the Wolf class independently of wether that method is declared virtual in the base Animal class.
    * If however (see the source code) you instantiate a wolf as follows:
    * Animal* w = new Wolf("Balto",2002,171);
    * and then call
    * w->print_age(2021);
    * Then the correct (Wolf) version of this function will be called if and only if you define the method to be virtual in the Animal class!
    * This is of course due to the fact that w is a pointer to Animal.
    * The same applies to the dtor of the Wolf class. It will only be called (when you define a pointer to Animal and assign it to a &Wolf) if 
    * the ~Animal (default dtor) is declared virtual.
    * 
    * A class where all the methods are virtual is called abstract, and cannot be instantiated.
    * Abstract classes are very useful for providing general interfaces which should be respected by all derived classes of a given base class.
    * 
    * But why use 
    * Base * d = new Derived();
    * When you can just instantiate a Derived object? 
    * This is to allow you to build general interfaces which do not need to know the implementation details of all the derived 
    * classes of Base.
    * For example: If you want to build a logging device to keep track of all the animals in your zoo, this might be achieved by some kind
    * of list or array of Animals. 
    * But you can't just do:
    * Animal w = Wolf(...) // Won't compile! 
    * So you achieve this with pointers. The same goes if you want to write some function which takes as argument or returns some Animal and performs some operations with it
    * The only way for this to work is if you design it to take Animal pointers ( or if you overload this function every time you have a new class derived from Animal).
    * Note that using templates here is overkill and most importantly hides the meaning of your code! If you just do:
    * template <class A>
    * A pop_animal(std::list<A>& ZooCatalogue) ;
    * You can't expect maintainers and users of your code to magically understand that A is supposed to be an Animal...
    */
}

