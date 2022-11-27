

//what's in a game 
//application layer 
	//hardware and the operating system
//game logic layer 
	//managing game state and its mutations
//game view layer 
	//presenting the game state with graphics and sound

//game logic layer receives the commands 
//eg keyboard inputs

//events and state changes are sent by the game logic layer to the view layer 

//but events can also be sent by the view to the game logic layer for instance user movement inputs 

//this book presents an MVC with application layer like 
//event driven architecture.

//THIS IS SOMETHING I NEED TO FINISH
//you can create the system to read a configuration file to match controls with commands.Then all you have to do is modify this data file, and you’ll have completely configurable controls

//you can't directly change the game state when reading a user input like pressing W it should send a configured event to the game logic system / layer


//main loop 3 major components
	//grabbing and queuing player input
	//ticking game logic 
	//presenting the game state to al lthe game views 
		//rendering / playing sounds / sending state over network

//important application layer code 
	//system clock : important for animations audio 
	//string handling 
	//DLLS
	//Threads and thread synchronization
	//Network communications 
	//Initializations
	//main loop 
	//shutdown

//Game objects and game object data strutures 
	//the data structure needs to allows for quick lookup and quick modification of object state
	//and allow for a flexible number of properties for each object 

	//all properties stored in a string idea from ultima online you would then parse the string to apply properties and edit the string to apply or remove them (specific functions to add or remove properties from string)

	//ECS

	//I can just have chung with array of entities 
	//with an arra of objects which contain a string with properties the string idea is nice since it does not require any kind of oop for networking this might be shit tho and each property will needs its own string functions lookup property prefix in the string like @health=100|#|

	//when the game logic makes changes in the game state a number of system need to respond to this change so either for every type of change we need tight coupling with other game system or we use events. Its much simpler to have an event system 
	// with event types and data associated to such event types 

	//The different systems register with the event manager to listen for events that they'l react to. 
	//Event based architectures then to make game systems more clean and it is the glue that ties 
	//everything together

	//The application layer holds the event registry 
	//and subsystems register to listen to events they are concerned with

	//inter process dependencies / Process manager
	//molotov example one process tracking the parabolic
	//movement of any game object until it collides with something and another process managing the firebal explosion 

	//Command Interpreter
	//game logic not linked directly to view/input layer
	//input layer -> command -> game logic interpret command and makes modifications to the state

	//LOD culling methods to optimize the number of "usefull" rendered polygons don't render everything in the view frustum 

//audio 
	//sound effects music and speach 

//process manager in the game view layer as well as the game logic layer

//user configurable options like moues sensitivity etc 

//the event based logic/view architecture lends itself well to networked games what needs to be done is attach more game views to the same logic/state
//multiple events should be sent together as a packet across the network 

//anti hacking filters 
//perhaps need to read a bit on directX



#include <iostream>
#include <random>
int main() {
	//need to use a different see each time otherwise the mersenne twistter will produce the same sequence each time
	std::mt19937 m_mt;
	std::uniform_int_distribution dist{ 1, 10 };
	
	std::cout << "hello world\n";
	for (int count{ 1 }; count <= 40; ++count)
	{
		std::cout << dist(m_mt) << '\t'; // generate a random number

		// If we've printed 5 numbers, start a new row
		if (count % 5 == 0)
			std::cout << '\n';
	}

}