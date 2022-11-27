#include <iostream>
#include <thread>
void t1Main() {
	std::cout << "hello from thread\n";
}

int main() {
	//identifying threads 
	std::thread t1(t1Main);
	std::cout << "This is my thread unique id : " << t1.get_id() << "\n";
	t1.join();

	std::cout << "this is the main thread id : " << std::this_thread::get_id() << "\n";

	//could be used in associative containers 
	//std::hash<std::thread::id>
	//there is also this thread get id this can be usefull to check which thread is which and specify takss in algorithms 

	//allows us to associate data or behavior to specific threads 

	//so far we have only seen purely independent threads 
	//sometimes its desirable to share data among threads while they're running

	//i guess in my networked game there will be shared data between the threads namely the game state 


	return 0;
}