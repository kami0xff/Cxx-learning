#include <iostream>
#include <vector>

//the command pattern is a method call wraped inside an object such that it can be passed parametrized and then passed to 
//a function 
// 
// simillar things :  “callback”, “first-class function”, “function pointer”, “closure”, or “partially applied function” 
// 
//gang of 4 book : "Commands are an object-oriented replacement for callbacks."
//
//

//use case example remapable input for game 
// else if (isPressed(BUTTON_Y)) fireGun();
// for exmple you want to not hard code a function action if the user presses a certain key in this case we are hardcoding the firegun() action to y
// but we want something more flexible here something we can swap out this is a perfect place for the command pattern

//an execute function set virtual 

//our interface 
class ICommand {
public:
	virtual ~ICommand() {}
	virtual void execute() = 0; //this syntax makes this class into an abstract base class 
	//the virtual destructor is needed for c++ interfaces which i did not understand 100%
};


//we then make our commands that implement the interface
class JumpCommand : public ICommand
{
public:
	virtual void execute() { std::cout << "calling jump()\n"; }
};

class FireCommand : public ICommand
{
public:
	virtual void execute() { std::cout << "bang bang firing gun command is called \n"; }
};


//we adapt the input handler class instead of hard coded functions in the input handle function now it has 
//4 member variables for the commands of each button which can be changed at runtime or construction of the InputHandler object
//
class InputHandler
{
public:
	void handleInput();

private:
	ICommand* buttonX_;
	ICommand* buttonY_;
	ICommand* buttonA_;
	ICommand* buttonB_;
};


void InputHandler::handleInput()
{
	if (isPressed(BUTTON_X)) buttonX_->execute();
	else if (isPressed(BUTTON_Y)) buttonY_->execute();
	else if (isPressed(BUTTON_A)) buttonA_->execute();
	else if (isPressed(BUTTON_B)) buttonB_->execute();
}

//instead of 

void InputHandler::handleInput()
{
	if (isPressed(BUTTON_X)) jump();
	else if (isPressed(BUTTON_Y)) fireGun();
	else if (isPressed(BUTTON_A)) swapWeapon();
	else if (isPressed(BUTTON_B)) lurchIneffectively();
}


//where each input used to be a direct function call now there is a layer of inderection and this layer comes from the 
//fact that we added an interface if we just hard coded a JumpCommand FireCommand objects etc for each input the old problem would have been the same 
//but because we can use this JumpCommand FireCommad asif they were ICommands in our code now FireCommand can be assigned to any button 
//that is the power of the flexibility that interfaces bring. 

//so in the case of us wanting some kind of remaping of functions the command pattern seems to be a good match 
//allows us to not hardcode functions to certain actions or events. in scenarios when we have EVENT -> ACTION and we want 
//flexibility of what action to chose for an event

//

//right now there is another big problem in the code which i could not percieve the fist time going through this 
//with our command actions we are assuming coupling with the gamecharacter the user is in control with its even not clear what we are 
//assuming coupling with.

//we again add a piece of indirection / abstraction in between
class GameActor {
public:
	void jump() { std::cout << "calling jump()\n"; }
	void fireGun() { std::cout << "bang bang firing gun command is called \n"; }
};

//now the command takes in a gameactor which will perform the command
class ICommand2 {
public:
	virtual ~ICommand2() {}
	virtual void execute(GameActor& actor) = 0;
};

class JumpCommand2 : public ICommand2
{
public:
	virtual void execute(GameActor& actor) {
		actor.jump();
	}
};

class FireCommand2 : public ICommand2
{
public:
	virtual void execute(GameActor& actor) {
		actor.fireGun();
	}
};

ICommand2* InputHandler::handleInput()
{
	if (isPressed(BUTTON_X)) return buttonX_;
	if (isPressed(BUTTON_Y)) return buttonY_;
	if (isPressed(BUTTON_A)) return buttonA_;
	if (isPressed(BUTTON_B)) return buttonB_;

	// Nothing pressed, so do nothing.
	return NULL;
}


//the command pattern has a good use case for AI producing commands for different actors in the game 
//also it can be an easy way to have a grannullar series of action and possibly undo them 
// 
//for undo redo systems its very usefull because it gives us a granular type for commands we can buid lists of them which can be usefull

//by passing an actor as a parameter to a function we decoupled the command from the actor 
//but if we passed the actor as a parameter of the constructor then on the contrary we would couple a command type with a specific actor
//which might be desirable in some cases. 

//actor as a parameter to the function execute is like we can use this JumpCommand object on every single actor in the game 
//actor as a constructor parameter then its like we can use this particular JumpCommand object on a single actor in the game 


//this is a variation of the command pattern rather than the handler holding onto a single command object that will call its execute function 
//whenever the right button is pressed 

//the variation in its input handling code will create a new command object everytime some button or event occurs Commands becoming like a unit
//that occurs at a specific point in time i think chess is a good exmple you would do this to record everytime you moved your knight for example 
//and at the end of the game you would have the list of everytime you moved your knight and its positions. in this variation commands become one use 
//only this comes at our advantage in the following case


//we add the undo function to our interface. 
class ICommand3
{
public:
	virtual ~ICommand3() {}
	virtual void execute() = 0; //these are pure virutal functions meaning they MUST be implemented. 
	virtual void undo() = 0;
};

class Unit {
public:
	void moveTo(int x, int y) {};
};

//we modify our command add fields to remember the initial state 
//and implement the undo function to revert to the initial state. 
class MoveUnitCommand : public ICommand3
{
public:
	MoveUnitCommand(Unit* unit, int x, int y)
		: unit_(unit),
		xBefore_(0),
		yBefore_(0),
		x_(x),
		y_(y)
	{}

	virtual void execute()
	{
		// Remember the unit's position before the move
		// so we can restore it.
		xBefore_ = unit_->x();
		yBefore_ = unit_->y();

		unit_->moveTo(x_, y_);
	}

	virtual void undo()
	{
		unit_->moveTo(xBefore_, yBefore_);
	}

private:
	Unit* unit_;
	int xBefore_, yBefore_;
	int x_, y_;
	//you don't want to store the previous position state in the Unit 

};

//we added more state to the class with xBefore and yBefore

//will need to implement this in my level editor and inventory management system 
//this notion of undo and redo. 


int main() {
	//simillar to a callback 
	
	std::vector<int> vecint{ 1,2,3 };

	auto callback{ []() {std::cout << "call me back";} };
	auto callback2{ [vecint]() {vecint.} };
	callback();

}

//something async with a callback ?
void fetch() {



}