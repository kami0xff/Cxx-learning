#include <iostream>

class Pet {
	
public: 
	int m_legs;

	Pet(int legs) : m_legs{ legs } {}


	//the final keyword specifies that a virtual function cannot be overriden in a derived class or that a class cannot be derived from. 
	//class A final {};
	//void fund() |<- this is what they call a declarator| final {}
	
	virtual int walk(int steps) final {
		return steps * 10;
	}

};


//public vs private inheritance ?

class Parrot : public Pet {

public:

	Parrot() : Pet(2) {}
	//fly really
	//cannot override because of the final keyword in the Pet class

	//override keyword specifies that a virtual function overrides another virtual function
	//it only appear in member functions
	//override specifier ensures that the function is virtual and is overriding a virtual function from a base class

	int walk(int flaps) override {
		return flaps * 5;
	}

	

};

