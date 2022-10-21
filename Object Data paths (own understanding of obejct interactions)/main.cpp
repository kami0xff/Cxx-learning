
#include <vector>
#include <string>

class A {
public:
	int x;
	std::vector<int> intList;
	std::string text;
};

class B {
private:
	int x; 
	int y; 
	std::string text;
};


class C {



};


class Outer {};

class Inner {};

int main(void) {


	return 0;
}


//basically for talk to test to be able to talk to test it needs a some kind of reference or instance of TEST
//but from the context in which TEST existed already lest say in the main() functino there is an instance of TEST
//we could already pass messages to TEST from main by just calling TEST.handlemessage(MESSAGETYPE)
//
//this was not possible yet int he talk to test object because it had nothing to call the handlemessage function
//
//Class talk to test
//TalkTest(TEST&) this
//calls the handlemessage(MESSAGETYPE) function of TEST
//
//
//
//
//the interface kamiInputEventListener in my code is the socket functionality that listens to input event messages
//or the input handler
//
//
//
//methods with parameters create this socket for the calling context to send information into the context of the object
//methods without parameters are limited to the inner state of the object its membersand methods
//it is the act of adding a parameter to a member functiont that creates a new socket for calling context to pass in information
//
//which is what the handlemessage(MESSAGETYPE) method exactly does
//
//so i think that when we think of objects its just important to think of their stateand what their calling context can do an pass information in them
//because in the end if i want to send a message from the main() function i can call handlemessage(MESSAGETYPE) from main if there is a TEST instance
//
//and i can call handlemessage(MESSAGETYPE) from within other objects if there is a reference or an instance within another objects which them become its calling context
//and by becoming the calling context it is able to pass in information into TEST
//
//calling context is what can pass information in objects










//case 1 object with all private members and no functions
//- if the constructor is private then this is never usable in any context
//
//case 2 object with all public members no functions
//- simillar to a struct just a group of data under a name that can be modified from the context in which it exists
//- could have flag members variables that are set from the outside or a message variable that is modified from the outside that serves as a way to pass information / data
//into an instance
//
//case 3 object with private members and functions to access private
//- can control read and write to the object's member variables
//-
//
//case 4 objects with private and public members and functions to access private
//- some members variables accessible from context others maybe through functions or maybe not at all
//
//
//case 5 objects with references to other objects or variables as member variables
//- data path from the object->to the outside context the opposite of what a method with parameter does or a public member variables which is context->object data path
//- since they are references they must exist in the object's outside context 
//-
//
//case 6 objects with instances of other objects as members
//- if there are instances within the object the outer object is the context of the inner object so it then depends on how the child object instance is structured
//and what kind of data paths are open.
//- if it has only public member variables then we can access then from our parent object : outer->inner
//- if it has private membersand accessor functions then we can use them to modify the child object's state which is controlled by the those accessor functions : outer -> inner
//- or the inner object has public functions with parameters that will change its state
//
//- will it be possible to pass thing that are in the context of the outer object into the inner object like main->outer object.innerObject.setX(x) : main->outer->inner
//- yes i think this is possible if either the instance of the inner object is public or if there are public functions in the outer object that are public
//- that take parameters and make use of the private instance of the inner object(creating an interface to the inner object).
//
//yes the communication is then internal, imagine two circles one within the other if the inner circle has public members or functions with parameters
//the communications outer->inner exists there is a data path
//
//and if this inner object has functions that take references to the outer object or members of the outer object then communication or a data path from
//the inner object->outer object exists.
//- if the inner object has reference members of the outer object or of the main context then
//
//its the same as when we imagine an object in the context of main but then the context is the outer object.
//
//
//case 7 objects with only no parameter methods
//- can only modify the member variables of the object.without information from the context
//-
//
//caes 8 objects taking references in their method parameters
//- data path object->context established
//
//case 9 objects not taking references in their method parameters
//- data path context->object established
//
//
//private functions of an object : just meant to be used by its other functions not meant to be used from its context
//
//
//code all these cases in a single file


