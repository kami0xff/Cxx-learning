#include <iostream>
class Base {
public:
	int x;
	Base(int a) : x{ a } {}
	void print() { std::cout << x; }
	void print(Base* const) { std::cout << this->x; }
};

int main() {

	Base instance(99); //are
	Base x = Base(33); //these two equivalent ?? it looks like it

	instance.print(); //this is passed as an hidden argument to the print function 
	//otherwise we would not know which member x in memory to use 
	//the this pointer is a constant pointer of type Base * const
	//and it points to where in memory this instance of the object is stored
	//the compiler hides this away from us. 
	instance.print(&instance);


	x.print();

	return 0;

}