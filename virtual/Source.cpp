
#include <iostream>
//the virtual keyword can only be aplied to non static MEMBERS it specifies that the member is virtual and supports 
//dynamic dispatch

//virtual functions are member functions whose behavior can be overriden in derived classes 

class A {
public:
	//as we can see here there is an error
	//virtual static void globalFunction() {
	//	std::cout << "mr global \n";
	//}


	//for this non static member there is no error
	virtual void overrideMe() {
		std::cout << "make me do something else \n";
	}

	void cantOverrideMe() {
		std::cout << "can't override me\n";
	}

};

class B : public A {
public:

	void overrideMe() {
		std::cout << "overriden in class B \n";
	}

	void cantOverrideMe() {
		std::cout << "well it looks like i can still override you\n";
	}
};


//As opposed to non-virtual functions, the overriding behavior is preserved even if there is no compile-time
//information about the actual type of the class


//we can make pure virtual functions by declaring a function and putting a = 0 at the end this enforced the subclasses to implement the virtual method 
//if they want to create an instance. 

//
int main() {
	B b{};
	b.cantOverrideMe();
	
}