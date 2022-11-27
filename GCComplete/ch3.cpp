#include <iostream>



//in c++ ordered containers used push_back()
//whilst unordered container like std::map or set use insert()

//way i want to organize all my classes
//class 
	//members
	//constructor destructors operators
	//protected and private internal functions
	//public interface
	
//don't add code that can fail or throw exceptions in constructors 

//avoid intricate relationships inside class hierarchy
//keep class hierarchies as flat as possible 
//be aware of inheritance and composition
//dont' abuse virtual functions
//use interface classes and factories 
//Encapsulate components most likely to change


//avoid hidden code and nontrivial operations
	//no need to do some crazy stuff in destructors for example 
	//avoid copy constructors and operator overloads that perform non trivial operations

//beware the behavior of the c++ compiler is to silently generate a copy constructor and a copy assignment operator and destructor for you and your class if you don't create them yourself however in some cases this might not be desirable. if you don't provide a constructor the compiler will also generate a default constructor for you class and all of these generated things are always public.

//keep hierarchies flat keep single responsibility in mind and avoid blob classes. 

//inheritance versus composition
	//inheritance is used when an object has evolved from another object a child is an evolution of a parent object 

	//Composition is when an object is composed of multiple discrete components 

//virtual functions are powerfull but abused long chains of overloaded virtual functions 


//when you decide to make a function virtual what you are communicating is that you inted for your class to be inherited by other classes. and the virtual functions serve as an interface for what other programmers can change by overriding them 

//Interface classes are those that contain nothing but pure virtual functions they form the top level in any class hierarchy 
//pure virtual functions must be implemented by the inheriting subclass

//Whenever possible or needed you should have systems depend on these interfaces instead of implementation classes 

//you can have many inmplementation classes behind an interface if the calling code should not care which specific implementation it is using and that is confirming to the interface


//Factories functions that will build objects and return the by value 
//hey this actually makes sense if you need a lot done to build an object like fetch textures etc 

//abstract factory can define the interface for creating objects with multiple parts - a constructor creates a single object. A factory creates and assembles these objects into a working mechanism. 

//factories tend to enforce orderly construction of complicated objects
//delayed instantiation you can keep a factory object in a queue or stack 
//and delay calling its build methods until something happpens 

//factories and interaces work hand in hand 
class SaveGameScreenFactory : public IScreenFactory
{
public:
	SaveGameScreenFactory();
	virtual IScreenElements* const BuildScreenElements() const;
	virtual ScreenBackground* const BuildScreenBackground() const;
	virtual IScreenLogic* const BuildScreenLogic() const;
};
//each method of the factory returns interface objects so the calling code is decoupled from the implementation of the se objects

//Try to look for the parts that are most likely to change when implementing a system. Interfaces for example are a big thing to allow 
//extensions if you code some of your class to depend on an interface you can add as many implementations of that interface as you like and the code that depends on the interface will still work and maybe work with more implementations and you don't have to change that class that depends on the other each time you add a new implementation 

//its ideal to isolate implementation that is likely to change
//major systems should be as decoupled from one another as possible 
	//this is not saying that all coupling should be avoided 
	//a monster with an orbiting fireball could be coupled to that fireball object 

//Interfaces and factories and other techniques are the tools to enable you to do this. 

//initialization methods that take streams as parameters to allow creation of objects from memory streams or network streams don't put this in a constructor ! 

//C and C++ parameters gets pushed onto the memory stack from right to left
//local variables get pushed onto the stack in their order of appearance.

//row ordering cache access can speed up accesses to large data structures
//The CPU reads and writes memory aligned data much faster than other data.
//be carefull of memory alignment and byte boundaries on your data structures 

//writing a memory manager : multi threaded memory manger vs single threaded in our games we can build a memomry manager that can work with more assumptions about how and when memory allocations occur. 
//another good reason to add our own memory manager is to add more debuggin and loging features 
//if we decide to write our own memory manger we should keep the following points in mind 
// 1) chose the data structure that matches our memory allocation scenario hash table or tree based if we traverse it a lot to find free blocks 
// and if we hardly every traverse it then a linked list should be fine
//	
// 2)  protect from race conditions due to multithreaded access if needed 

// 3) add debug info like __FILE__ and __LINE__ to the memory blocks in debug mode so you can track where the allocation was made 


//Random Number Generator 
//ANSI rand() is not so good single stream of random number 
//


//in the book he shows a header class declaration for the mersenne twister turns out 
//its already in the standard in the #include<random> header so why not use that for now ?
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

//Memory pools 
//usefull for requent small allocations and deallocations
//the idea is to allocate a large chunge of memory up front which is then 
//divided in chunks of even sies and each chunk has a pointer to the next chunk
//creating a single linked list of memory chunks
//good use case for this is for object we construct and destroy extremely often 
//the fact that we have allocated the memory upfront will save a lot of time by reducing the number of system calls ood idea overall for game objects i think should add it to my project 


