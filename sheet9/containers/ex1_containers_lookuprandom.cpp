#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <ctime>
#include <chrono>
#include <iomanip>
#include <string>
#include <fstream>

#include <vector>
#include <map>
#include <deque>
#include <list>


using namespace std;

template<typename container>
void print_look_up_time(container c, int Nsamples, long long int N){
	srand(1);
	double elapsed_secs;
	clock_t begin;
	int randIdx;
	string dummy;
	cout << "looking up by traversing ..." << endl;

	begin = clock();
	auto t1 = chrono::high_resolution_clock::now();
	for (int i=0; i<Nsamples; i++) {
		randIdx = rand()%N;	// get random index from range
		auto lit = c->begin();	// set iterator to beginning of list
		for (int j=0; j<randIdx; j++) 
			lit++;	// iterate to element
		dummy = *lit;
	}
	auto t2 = chrono::high_resolution_clock::now();
	int dur_count = chrono::duration_cast<chrono::microseconds>( t2 - t1 ).count();
	elapsed_secs = ((double) dur_count)/1e6;
	printf("looking up %.0e entries by traversing took %10.7fs ( av. %7.5f ms/entry )\n\n", (double) Nsamples, elapsed_secs, elapsed_secs/Nsamples*1e3);
}


int main(int argc, char** argv)
{
	long long int N;	// number of elements
	int Nsamples;	// number of samples for looking up
	if (argc<2) {
		cout << "not enough args!" << endl;
		return 1;
	} else if (argc<3) {
		N = (int) atof(argv[1]);
		Nsamples = (int) 1e6;
	} else {
		N = (int) atof(argv[1]);
		Nsamples = (int) atof(argv[2]);
	}

	// for timing
	double elapsed_secs;
	int duration_ms;
	chrono::high_resolution_clock::time_point t1;
	chrono::high_resolution_clock::time_point t2;
	// for looking up rand pos
	//srand(time(0));	// use current time as seed for random generator
	srand(1);
	int randIdx;
	double maxtime, mintime, avtime;
	string dummy;

	//----- ARRAY -----//

	
	//-- create storage --//
	cout << "creating ARRAY ..." << endl;
	string* myarr = new string[N];
	//string myarr[N];
	//cout << myarr[0];
	// fill it
	for (long long int i=0; i<N; i++) {
		char mychar[10];
		sprintf(mychar, "0x%llx", i);
		string mystring = (string) mychar;
		myarr[i] = mystring;
	}
	
	//-- look up random entries --//
	cout << "looking up ARRAY ..." << endl;
	t1 = chrono::high_resolution_clock::now();
	for (int i=0; i<Nsamples; i++) {
		randIdx = rand()%N;	// get random index from range
		dummy = myarr[randIdx];
	}
	t2 = chrono::high_resolution_clock::now();
	duration_ms = chrono::duration_cast<chrono::microseconds>( t2 - t1 ).count();
	elapsed_secs = ((double) duration_ms)/1e6;
	printf("looking up %.0e entries from %8s took %10.7fs ( av. %7.5f ms/entry )\n\n", (double) Nsamples, "ARRAY", elapsed_secs, elapsed_secs/Nsamples*1e3);
	print_look_up_time(myarr, Nsamples, N);
	
	//string().swap(myarr);
	delete [] myarr;
	


	//----- VECTOR -----//

	//-- create storage --//
	cout << "creating VECTOR ..." << endl;
	vector<string> myvec;
	myvec.reserve(N);	// should speed up creating vector
	// fill it
	for (long long int i=0; i<N; i++) {
		char mychar[10];
		sprintf(mychar, "0x%llx", i);
		string mystring = (string) mychar;
		myvec.push_back(mystring);
	}

	//-- look up random entries --//
	srand(1);
	cout << "looking up VECTOR ..." << endl;
	t1 = chrono::high_resolution_clock::now();
	for (int i=0; i<Nsamples; i++) {
		randIdx = rand()%N;	// get random index from range
		dummy = myvec[randIdx];
	}
	t2 = chrono::high_resolution_clock::now();
	duration_ms = chrono::duration_cast<chrono::microseconds>( t2 - t1 ).count();
	elapsed_secs = ((double) duration_ms)/1e6;
	printf("looking up %.0e entries from %8s took %10.7fs ( av. %7.5f ms/entry )\n\n", (double) Nsamples, "VECTOR", elapsed_secs, elapsed_secs/Nsamples*1e3);
	print_look_up_time(&myvec, Nsamples, N);
	vector<string>().swap(myvec);

	//----- MAP -----//

	//-- create storage --//
	cout << "creating MAP ..." << endl;
	map<int,string> mymap;
	// fill it
	for (long long int i=0; i<N; i++) {
		char mychar[10];
		sprintf(mychar, "0x%llx", i);
		string mystring = (string) mychar;
		mymap[i] = mystring;
	}

	//-- look up random entries --//
	srand(1);
	cout << "looking up MAP ..." << endl;
	t1 = chrono::high_resolution_clock::now();
	for (int i=0; i<Nsamples; i++) {
		randIdx = rand()%N;	// get random index from range
		dummy = mymap[randIdx];
	}
	t2 = chrono::high_resolution_clock::now();
	duration_ms = chrono::duration_cast<chrono::microseconds>( t2 - t1 ).count();
	elapsed_secs = ((double) duration_ms)/1e6;
	printf("looking up %.0e entries from %8s took %10.7fs ( av. %7.5f ms/entry )\n\n", (double) Nsamples, "MAP", elapsed_secs, elapsed_secs/Nsamples*1e3);
	//print_look_up_time(&mymap, Nsamples, N);
	map<int,string>().swap(mymap);

	//----- LIST -----//

	//-- create storage --//
	cout << "creating LIST ..." << endl;
	list<string> mylist;
	// fill it
	for (long long int i=0; i<N; i++) {
		char mychar[10];
		sprintf(mychar, "0x%llx", i);
		string mystring = (string) mychar;
		mylist.push_back(mystring);
	}

	//-- look up random entries --//
	srand(1);
	cout << "looking up LIST ..." << endl;
	list<string>::iterator lit;	// iterator to go through list
	t1 = chrono::high_resolution_clock::now();
	for (int i=0; i<Nsamples; i++) {
		randIdx = rand()%N;	// get random index from range
		lit = mylist.begin();	// set iterator to beginning of list
		for (int j=0; j<randIdx; j++) lit++;	// iterate to element
		dummy = *lit;
	}
	t2 = chrono::high_resolution_clock::now();
	duration_ms = chrono::duration_cast<chrono::microseconds>( t2 - t1 ).count();
	elapsed_secs = ((double) duration_ms)/1e6;
	printf("looking up %.0e entries from %8s took %10.7fs ( av. %7.5f ms/entry )\n\n", (double) Nsamples, "LIST", elapsed_secs, elapsed_secs/Nsamples*1e3);
	print_look_up_time(&mylist, Nsamples, N);
	list<string>().swap(mylist);

	return 0;
}













