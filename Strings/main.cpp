#include <iostream>
#include <string>

int main() {
	const char* const stringptr = "pointa"; //compiler tells us that a char* to a literal string needs to be const char*;
	//the rules for const on pointers 
	//const applies to the left if it can and then looks to the right if it cannot best to use east const convention.
	//first const applies to char meaning we are pointing to constant values
	//second const applies to * meaning we cannot change what our pointer points to 
	std::cout << stringptr << "\n";

	std::string str = "pointa";
	char stringarr[] = "hi";
	char stringarr2[10]{}; //does {} 0 initialize ??

	//stringptr = &stringarr;

	//SSO
	//if we make an std::string with less than 15 characters it is equivalent to a C string in terms of performance
	//dynamic allocation occurs only after 15

	return 0;
}


//Things to learn C++ algorithms
//C++ STL
//Temporaries in functions and returns as well as RVO 
//copy semantics/ comparison semantics