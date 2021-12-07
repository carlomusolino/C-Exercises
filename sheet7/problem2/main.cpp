#include <iostream>
#include <fstream>
#include <algorithm>
#include <chrono>
#include <random>
#include <string>


// some global variables used by all functions
const int n_numbers = 100000 ;    // how many numbers are in the list
const int n_digits = 7 ;        // how many digits the numbers have
int max_number = std::pow(10, n_digits) - 1 ;   // the largest number with given number of digits
std::vector<int> Numbers(n_numbers) ;           // array that holds the numbers

int number_to_find = 990 ;     // the number that needs to be found by the binary search algorithm


void initialize();  // fills vector Numbers with n_numbers random uniformly distributed numbers in the range of [0,max_number]

int fstream_binary_search( int target, std::fstream &input);   // performs binary search in a given file

int main() {
  initialize();

  std::fstream myList ;

  // fill file with numbers
  myList.open("numbers.dat", std::ios::out | std::ios::trunc ) ;
  std::string s_out ;
  for(int i=0; i<n_numbers ; i++){
    s_out = std::to_string( Numbers[i] ) + "\n" ;
    myList.width(n_digits + 1);  // assure that line length is always the same. i.e. number of digits plus eol char
    myList << s_out ;
  }
  myList.close();



  // perform search in generated file and measure the time with chrono
  myList.open("numbers.dat", std::ios::in ) ;
  std::chrono::high_resolution_clock::time_point t1 = std::chrono::high_resolution_clock::now();
  int gefunden = fstream_binary_search( number_to_find, myList );
  std::chrono::high_resolution_clock::time_point t2 = std::chrono::high_resolution_clock::now();
  int dur_count = std::chrono::duration_cast<std::chrono::microseconds>( t2 - t1 ).count();
  double dur_sec = ((double) dur_count)/1e6;
  std::cout << "Binary search in fstream " << gefunden << " Time: " << dur_sec << "s" << std::endl ;
  myList.close();

}




void initialize(){
  // obtain a seed, initialize a random number generator and initialize a uniform distribution
  unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
  std::mt19937_64 gen(seed);
  std::uniform_int_distribution<int> random(0, max_number);

  // fill the vector with random numbers and sort them
  Numbers.clear();
  for(int i=0; i<n_numbers ; i++){
    Numbers.push_back( random(gen) );
  }
  Numbers[6] = number_to_find ;  // insert the number to find, this makes testing easier
  std::sort(Numbers.begin(), Numbers.end() );


}


int fstream_binary_search( int target, std::fstream &input){
  if( !input.is_open() ) { // check if file is there
    std::cout << " ERROR! (fstream_binary_search): no input filestream. " << std::endl ;
    return -2;
  }

  std::string str ;         // to read a line from file
  std::streampos pos ;      // cursor position in file
  int left, right, middle ; // position in file (line number)
  int value;                // number stored at current position (middle)

  // iterative binary search algorithm
  left = 0 ;            // starting positions
  right = n_numbers ;

  while( left <= right ){
    middle = left + (right-left)/2 ; // which line is the next
    pos = middle * ( n_digits+1 ) ;  // each line is n_digits+1 characters long.
    input.seekg( pos );              // set cursor position at beginning of current line
    input >> str ;                   // read in the current line. operator >> stops at eol
    value = std::stoi( str );        // convert str to int

    if( value == target ){
      return middle;           // target found. return its position
    } else {
      if( value > target ){    // target is smaller than value at current position, look in the right half of list
	right = middle - 1;
      } else {
	left = middle + 1 ;    // target is greater than value at curr pos, look in left half of list
      }
    }

  }

  return -1 ;   // if target is not found, while loop ends without return
}

