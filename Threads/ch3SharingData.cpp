#include <thread>
#include <iostream>
#include <list>
#include <mutex>
#include <algorithm>

int main() {
	//sharing data among threads is one of the key benefits of multithreading but issues can arrise 

	//when it comes down to it all the problems from data between threads 
	//come from the mutation of the shared data if all the threads were only reading the data no problem at all

	//because we never run into scenarios where one is modifying data 
	//that is currently being read or modified by another thread 

	//invariants : statements that are always true about a particular data structure we need to be aware when breaking the invarient properties of our data 

	//Race conditions
	//in concurrency a race condition is anything where the outcome depends on the relative ordering of execution of operations on two or more threads 

	//how do we avoid them : using a protection mechanism that makes sure that only the thread making the modifications can see the state in which the invariants are broken but this has a performance cost of course 
	
	//otherwise if possible try to make the operations not brake the invariants series of indivisible changes this is called lock free programming and is hard to do right

	//another way of doing it is software transactional memory which is not yet supported by C++ (STM)

	//mutexes
	//stands for mutually exclusion, it behaves so that if any thread tries to access the data structure it needs to wait until the previous thread is finished. This makes it impossible for a thread to see a broken invariant except when it is doing its own modification 

	//before accessing a shared data structure you lock the mutex associated with that data and when finished you unlock the mutex

	//mutexes come with the potential problem of a deadlock 




	return 0;
}
	
	//more common to group these two in a class
	std::list<int> someList;
	std::mutex someMutex;

	void addToList(int newValue)
	{
		std::lock_guard<std::mutex> guard{ someMutex };
		someList.push_back(newValue);
	}

	bool listContains(int valueToFind) 
	{
		std::lock_guard<std::mutex> guard{ someMutex };
		return std::find(someList.begin(), someList.end(), valueToFind) != someList.end();
	}

	//having private members in our code makes it clear which code will have access to the data namely only the methods of the class 

	//mutexes require carefull interface design it is possible to 
	//return or pass a reference or pointer to the data which means that 
	//the data will be modifiable without locking the mutex we need to make sure that there are no backdoors 

	//so our member functions will not be able to call function with a pointer or ref to the protected data or return a pointer or ref of the protected data. also beware of functions passed at runtime like callback etc 





