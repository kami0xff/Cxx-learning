#include <thread> //c++ std threading library
#include <iostream>


//we can have multiprocessing which are two seperate processes with single threads running and communicating with each other 

//Multi threading means that a single process can have multiple threads that communicate with each other with shared memory 
	//multi threading does not run well on distributed systems
	//provides better performance than multi process communication 


void doWork() {
	std::cout << "did my work \n";
}

class Functor {
public :
	void operator()() 
	{
		for (int i = 0; i > -100; i--) 
		{
			std::cout << "from worker : " << i << "\n";
		}
	}
};

int main() {
	std::thread worker(doWork); //function name without paranthesis passes in a function pointer
	//this creates a thread worker
	//and at this point worker starts working and does the doWork function


	//here main thread will wait for the worker thread to finish / complete
	worker.join(); //this will block the current main thread until our worker thread has finished its work


	std::thread worker2(doWork); //start worker 2 thread
	worker2.detach(); //detach worker 2 to sever the connection between the main thread and woker 2 and make worker 2 run freely on its own 
	//worker2 becomes what we call a daemon process

	//and when worker2 finishes because it is no longer a child of the main thread the c++ runtime library will be responsible to reclaim 
	//the ressources of worker2 
	//some daemon processes may run until system shutdown.

	//in this example the program terminates before the worker2 detached thread is able to write to stdout
	//because worker2 and the main thread are sharing the standard c out 
	//the thread that owns the resources being shared needs to be sure to live as long as the other threads are accessing the resources it owns


	//ALSO you can join or detach a thread only once !!! 
	//if after detaching worker2 we wished to join worker2 this is not possible once detached forever detached and once joined forever joined 

	//we can test if a thread is joinable

	if (worker2.joinable()) 
	{
		std::cout << "we can join worker2\n";
		worker2.join();
	}
	else 
	{
		std::cout << "worker2 is not joinable\n";
	}

	//what happens when threads are neither joined nor detached ?
	std::thread worker3(doWork);
	//if worker 3 goes out of scope and is destroyed before it is joined or detached it will terminated the program

	//in between the creation of the worker3 thread and joining it we need to do some work on the main thread otherwise we are not getting any
	//benefits of threading


	//we wrap the work of our main thread in a try catch because if an exception occurs during the work of the main thread 
	//and then the thread is destroyed without joining or detaching then the program will terminate 
	//so it makes sure our thread will be joined with our without exception. 
	try 
	{
		for (int i = 0; i < 10; i++)
		{
			std::cout << "main thread work\n";
		}
	}
	catch(...)
	{
		worker3.join();
		throw;
	}

	worker3.join();

	//an alternative is to use RAII with a wrapper class around our thread object 
	//and in the destructor call the join() method of our thread object this will make sure that it joined before destroyed

	//we have made a thread from a function pointer for now but it is also possible to make a thread from a functor a lambda 
	//any callable object can be used. 


	//from what i see so far a functor is a callable user defined type 
	Functor f;




	return 0;
}









