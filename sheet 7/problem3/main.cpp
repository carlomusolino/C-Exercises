// solves ex 2 on sheet 9
#include <iostream>
#include <algorithm>	// std::min

template<typename T>
class Buffer {
	public:
		Buffer( size_t bsize );		// ctor gets size
		Buffer( Buffer& b_old );		// copy ctor
	   ~Buffer();					// dtor

		Buffer& operator>> (T &output);	// out streaming operator
		Buffer& operator<< (T input);	// in streaming operator

		bool checkIfEmpty()				// checks if empty
			{ return isEmpty; }
		bool checkIfFull()				// checks if full
			{ return isFull; }

		void print( size_t maxlen = 5);		// prints the buffer and state nicely readable
		size_t getSize()	// get size
			{ return size; }
		size_t getPos()		// get position
			{ return pos; }
		void reset()		// reset buffer content to empty
			{ pos = 0; isEmpty = true; isFull = false; }
		void resize( size_t newsize );		// resizes the Buffer
	private:
		size_t size;		// size of the Buffer
		T* arr;				// pointer to Buffer array
		size_t pos;			// position in Buffer
		bool isEmpty;		// states if empty
		bool isFull;		// states if full
};

//---- CTOR/DTOR ----//

template<typename T> Buffer<T>::Buffer( size_t bsize )
// constructor for Buffer class
{
	size = bsize;
	pos  = 0;
	// allocate new array -> ptr to arr
	if ( bsize>0 ) {
		arr = new T[size];
		isEmpty = true;
		isFull  = false;
	} else {
		std::cout << "invalid size_t " << size << " on construction." << std::endl;
	}
}

template<typename T> Buffer<T>::Buffer( Buffer& b_old )
// copy ctor for Buffer class
{
	size = b_old.size;
	// take position
	pos = b_old.pos;
	// allocate array for new buffer
	arr = new T[size];
	// copy buffer
	for ( size_t i=0; i<pos; i++ ) {
		arr[i] = b_old.arr[i];
	}
	// set status of new buffer
	if ( pos == 0 ) { isEmpty = true; isFull = false; }
	else if ( pos == size ) { isEmpty = false; isFull = true; }
	else { isEmpty = false; isFull = false; }
}

template<typename T> Buffer<T>::~Buffer()
// destructor
{
	delete arr;
}


//---- OPERATORS ----//

template<typename T> Buffer<T>& Buffer<T>::operator>> (T &output)
// out streaming operator
{
	if ( !isEmpty ) { // something is in
		pos--;
		output = arr[pos];
		// check if isFull correctly set
		if ( isFull ) { isFull = false; }
		// check if empty now
		if ( pos-1<0 ) { isEmpty = true; }
	} else { // empty
		std::cout << "buffer is empty" << std::endl;
	}
	return *this;
}

template<typename T> Buffer<T>& Buffer<T>::operator<< (T input)
// in streaming operator
{
	if ( !isFull ) {	// free space in buffer
		arr[pos] = input;	// put into buffer
		// check if isEmpty correct
		if ( isEmpty ) { isEmpty = false; }
		// check whether isFull
		if ( pos+1>=size ) { isFull = true; }
		pos++;
	} else { // isFull
		std::cout << " buffer is full" << std::endl; 
	}
	return *this;
}


//---- MEMBER FUNCS ----//

template<typename T> void Buffer<T>::print( size_t maxlen )
// prints the buffer and state nicely readable
{
	std::cout << "    size " << size << std::endl;
	std::cout << "     pos " << pos << std::endl;
	std::cout << " isEmpty " << isEmpty << std::endl;
	std::cout << "  isFull " << isFull << std::endl;

	if ( maxlen>size ) { maxlen = size; }
	// print buffer	
	if ( pos>0 ) {	// buffer is not empty
		std::cout << "  buffer \" ";
		if ( pos>maxlen ) {	// to large...
			for ( size_t i=0; i<maxlen/2; i++ ) {
				std::cout << arr[i] << " ";
			}
			std::cout << "... ";
			for ( size_t i=pos-maxlen/2; i<pos; i++ ) {
				std::cout << arr[i] << " ";
			}
		} else {	// printable
			for ( size_t i=0; i<pos; i++ ) {
				std::cout << arr[i] << " ";
			}
		}
		std::cout << "\"" << std::endl;
	} else { // buffer empty
		std::cout << " (empty buffer) " << std::endl;
	}
	std::cout << std::endl;
}

template<typename T> void Buffer<T>::resize( size_t newsize )
// resizes buffer
{
	T* temp = new T[newsize]; // create temporary object
	// copy content
	for ( size_t i=0; i<std::min(newsize,size); i++ ) {
		temp[i] = arr[i];
	}
	// redirect arr 
	arr  = temp;
	size = newsize;
	pos  = std::min(pos, newsize);
	return;
}

// ------------------------------------------- //

int main()
{
	// initialize buffer
	int myint, myint1, myint2;
	Buffer<int> mybuffer(2);
	std::cout << "initial state" << std::endl;
	mybuffer.print();
	mybuffer << 1 << 2 << 3;
	mybuffer.print();

	mybuffer>> myint1 >> myint2;
	std::cout << myint1 << myint2 << std::endl;
	mybuffer.print();
/*
	// testing the buffer in-streams
	std::cout<< std::endl << "testing buffer in-streaming" << std::endl;

	mybuffer << 1;
	mybuffer.print();
	
	mybuffer << 2;
    mybuffer.print();

	mybuffer << 3;
    mybuffer.print();

	// testing the buffer out-streams
	std::cout<< std::endl << "testing buffer out-streaming" << std::endl;

	int myint;
	mybuffer >> myint;
	std::cout << "read out is "<< myint<<std::endl;
	mybuffer.print();
	mybuffer >> myint;
	std::cout << "read out is "<< myint<<std::endl;
	mybuffer.print();
*/
/*
	std::cout << "Testing copy constructor:" << std::endl;
	mybuffer << 1 << 2;
	std::cout << "buffer" << std::endl;
	mybuffer.print();

	Buffer<int> mybuffer2(mybuffer);
	std::cout << "buffer2 (copy constructed)" << std::endl;
	mybuffer2.print();

	std::cout << "removed one element from buffer" << std::endl;
	mybuffer >> myint;
	std::cout << "buffer" << std::endl;
	mybuffer.print();
	std::cout << "buffer2" << std::endl;
	mybuffer2.print();
*/
/*
	std::cout << "Testing reset:" << std::endl;
	mybuffer << 1 << 2;
	mybuffer.print();
	mybuffer.reset();
	mybuffer.print();
*/
/*
	std::cout << "Testing state checkers:" << std::endl;
	mybuffer.print();
	std::cout << "is buffer empty? " << mybuffer.checkIfEmpty() << std::endl;
	std::cout << "is buffer full?  " << mybuffer.checkIfFull() << std::endl;
	std::cout << "buffer load is   " << mybuffer.getPos() << std::endl<< std::endl;

	mybuffer << 1;
	mybuffer.print();
	std::cout << "is buffer empty? " << mybuffer.checkIfEmpty() << std::endl;
	std::cout << "is buffer full?  " << mybuffer.checkIfFull() << std::endl;
	std::cout << "buffer load is   " << mybuffer.getPos() << std::endl<< std::endl;

	mybuffer << 2;
	mybuffer.print();
	std::cout << "is buffer empty? " << mybuffer.checkIfEmpty() << std::endl;
	std::cout << "is buffer full?  " << mybuffer.checkIfFull() << std::endl;
	std::cout << "buffer load is   " << mybuffer.getPos() << std::endl<< std::endl;
*/
/*
	std::cout << "Testing resize:" << std::endl;
	mybuffer << 1 << 2;
	mybuffer.print();
	mybuffer.resize(25);
	mybuffer.print(20);
	mybuffer.resize(1);
	mybuffer.print();
	mybuffer.resize(7);
	mybuffer.print();
*/
	return 0;
}








