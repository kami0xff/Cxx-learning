


#include <iostream>
#include "items.h"

int main() {

	//the middle man between the constructor of your class and the code that needs a new object. 
	//when an object we are trying to create relies on other objects being created as well 
	//this might require a factory method that will create the objects it needs and pass them in the constructor

	Item dagger{ 1, 2, 3 };
	Item sword(1, 2, 3);



	return 0;
}
