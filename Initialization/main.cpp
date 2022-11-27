#include <iostream>
#include <array>
#include <string>

class Object {

public:
	Object() {
		std::cout << "default constructed \n";
	}
	~Object() {
		std::cout << "Object destroyed \n";
	}
	Object(Object&) {
		std::cout << "Copy constructed \n";
	}
	Object(Object&&) {
		std::cout << "Move Constructed \n";
	}
	Object operator=(Object&) {
		std::cout << "Copy Assigned \n";
	}
	Object operator=(Object&&) {
		std::cout << "Move Assigned \n";
	}


	// static data members, which are data shared between all instances of a given type.
	static int staticPublicMemberValue; //static member variables each instance of the object class will have the same member
										
	//non-static data members. Each instance of the class has its own set of those members
	int publicValue;

	static void staticPublicFunction() {
		std::cout << "static function \n";
	}

private:

	static int staticPrivateMemberValue;


	int privateValue;

	static void staticPrivateFunction() {
		std::cout << "static function \n";
	}


};

struct Data {
	int value;
	std::string text;
};


Data dataFactoryFunction(int value) {
	return { value, "factory created" };
}

int main() {


	//in theory initialization is simple : put data in the memory location of a newly created variable

	/*
	• aggregate initialization
	• constant initialization
	• default initialization
	• direct initialization
	• copy initialization
	• list initialization
	• reference initialization
	• value initialization
	• zero initialization
	*/


	int x; //Default Initialization
	int x1 = 1; //copy assignment ?
	int x2{}; //list initialization
	int x3 = {}; //copy list initialization
	auto x4 = std::make_unique<int>(10); // auto type deduction and heap smart allocation
	auto x5 = dataFactoryFunction(11); // factory method
	std::string s(10, 'a'); //calling the std string constructor with int char

	Data d{ 10,"aggregate initialized" }; //aggregate intialization

	std::array<float, 10> numbers{ 1.1, 1.2 }; //array initialization

	int arr[10]{ 1,2,3,4,5,5 };
	int arr[10] = { 1,2,3,4,5,5 };

	const char* cp{ "asd" };
	const char* cp = { "asd" };



	Object obj;//Default Initialization 
	//WILL LEAVE ALL data members of the built in type (also simple types) with indeterminate values undefined behavior !
	//this is also true for variables with automatic storage duration 
	//int x;
	//static and thread loca objects will be zero initialized with default initialization

	Data data;
	//however even with Default initialization the std::string inside Data for example will have an emptry string becaues the constructor of std::string is called;




}



//Thought about object communication and function communication 
/*
	if an object has a reference to another object then the communication channel is one way
		the object can call function of the other object and pass in data in the arguments of those function
		the exeption however is when the parent object would pass as a parameter to the function the child object a reference to itself
		then the child object can make modifications to the state of the parent object and possibly call its function with parameters

	because at the end of the day if the child object is just an object with some data int string etc and no functions there is not really
	a communication channel unless you can write to those directly like if they are public


	SUGOI

	the public functions or members variables of an object define the communication channels and interface from the context/scope in which it exists

	this is true for objects within objects and objects within just our regular main function or other function's scope

	and a function that is not a member of an object does not create such communication channels

	functions if they take pointers or reference can have multiple streams of output not only through a return value
	a void function that takes a pointer really has in/out communcation with the object whose pointer we passed as a parameter


	if there are no objects functions can establish communications channels but with with variables in the calling scope
	that are passed in as parameters and it must be a two way communication channel since they have to be pointers then ?

*/




