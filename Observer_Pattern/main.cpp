
#include <iostream>
#include <vector>

//you can't throw a rock at a computer without an application built using the model-view-controller architecture
//underlying this architecture is the Observer Pattern. 

//observers are so important java has it built in the language java.util.observer and C# with the event keyword
//it is one of the most widely used and widely known of the original Gang of four patterns. 

//lets think of an achievement system for our game. There are many achievements for all kinds of behaviors this is haaaard to program 
//due to all the behaviors to monitor 
//example events that could trigger achievements : “Kill 100 Monkey Demons”, “Fall off a Bridge”, or “Complete a Level Wielding Only a Dead Weasel”.

//“Fall off a Bridge” is somehow tied to the physics engine, but do we really want to see a call to unlockFallOffBridge() 
//right in the middle of the linear algebra in our collision resolution algorithm? This is terrible we want our code decoupled 
//but achievements are tied to all kinds of different aspects of gameplay so how can we avoid this coupling. 

//This is what the observer pattern does It lets one piece of code announce to the world that something 
//interesting happened without actually caring who receives the notification.


/*
void Physics::updateEntity(Entity& entity)
{
	bool wasOnSurface = entity.isOnSurface();
	entity.accelerate(GRAVITY);
	entity.update();
	if (wasOnSurface && !entity.isOnSurface())
	{
		notify(entity, EVENT_START_FALL);
	}
}
*/

//in my own example you would have something like 
//the player state class saying hey the player is about to die idk who cares but this is happening !
//this allows us to implement the achievement system such that it is completely detached to the physics engine for example we could delete 
//the whole achievement system and the physics engine would not even care. 


class Subject {
	std::vector<Observer&> observers;
	int numObservers = 0;
public:
	virtual void addObserver(Observer& observer) = 0;
	virtual void removeObserver(Observer& observer) = 0;
	virtual void notify(Entity& entity, Event const event) = 0;
};

class PlayerHealthEvent : private Subject{

	//subscribers
	//should it be a set such that each observer is unique 
	//like is there a case when i would want multiple observers of the same type maybe in a mmorpg this scenario could occur. 
	std::vector<Observer&> observers;
	int numObservers = 0;


	void addObserver(Observer& observer) {
		observers.push_back(observer);
		numObservers++;
	}
	void removeObserver(Observer& observer) { //need to start using east const convention so that const applies always to what is left
		//find it and remove it
		//observers.find
	}

	void notify(Entity& entity, Event const event) {
		if (numObservers == 0) {
			return;
		}
		for (Observer& observer : observers) {
			observer.onNotify(entity, event);
		}
	}

};

class Entity {
public:
	Entity() = default;
};


//the subject being observed is going to send out the notifications it will
//hold a vector of Observers but lets say we have many observers we don't want our player instance to hold 100 objects in this vector that would not be very memory inefficient
//rather we want references to the observers. so a vector of pointers or references to the observers is what we go for
class PlayerState : Entity{
public:
	int positionX;
	int positionY;
	int health = 20;
	int armor;

	Subject playerHealthEvent;

	PlayerState() {}


};


//the SUBJECT Presents an API for observers to SUBSCRIBE to its event notifications
//and the way this is structure is so genious because its completely decoupled. 
//the only sort of coupled part is that our player class now has to think about when to notify certain events 
//


enum Event {
	LOW_HEALTH_EVENT,
	CRITICAL_STRIKE_EVENT,
};

//observer interface 
//abstract class because of the pure virtual function onNotify
class Observer {
public:
	virtual ~Observer() {};
	virtual void onNotify(const Entity& entity, Event event) = 0;
};

//we make our playerstate observer implement the interface
class PlayerStateObserver : Observer{
	//subscriber object 
public:
	void onNotify(const Entity& entity, Event event) {
		switch (event) {

		case LOW_HEALTH_EVENT:
			std::cout << "you are about to die\n";
			break;

		case CRITICAL_STRIKE_EVENT:
			std::cout << "bam you dealt a critical strike\n";

			break;
		default:
			std::cout << "events i don't care about\n";
		}
	}
};


//One difference that they made in the examples that i was reading is that they made a class subject and made the player class inherit
//the vector of observers and the API for adding and removing observers. I see how that could prevent code duplication however 
//its more like a trait relationship rather than an inheritance like its just a functionality we are adding to the class its not really an hierarchical structure
//so for now i did not do it. The author even writes in notes that in real code he would avoid the use of inheritance here and rather have an instance of Subject in 
//the player class or whatever we want as a subject. i agree

// I’d make Physics have an instance of Subject. Instead of observing the physics engine itself, the subject would be a separate “falling event” object. 
// Observers could register themselves using something like
// so we would make a class for the type of subject event 


//ohh this is what the protected keyword does
//protected void foo() inside the BAR class would let its subclassess make use of the function but 
//code outside would not be able to call foo() through the subclass with the . operator
//neither code outside through a BAR instance with the . operator


//now that we have a Subject subclass instance in our object everytime something related to the concerned event can notify all the subscribers 
//to the subject. 

//"Pretty simple, right? Just one class that maintains a list of pointers to instances of some interface. It’s hard to believe that something so straightforward 
//is the communication backbone of countless programs and app frameworks."

//There are complains however 

//the way we have implemented this pattern so far is synchronous the subject code will wait for all its observers to run their onNotify functions
//there could be benefits of multithreading of asynchronous communication with an EVEN QUEUE
//like every time a subject notifies it goes in an event queue on the observer side and it can deal with the messages there somehow im not too sure how the Event 
//queue would be implemented. 


//another way that it could be implemented which is kind of smart is by having a link list with as the head the 
//Subject -> Observer -> Observer ... and its observers trailling 
//this one is not great because it adds link list code into the observer class which i personally don't like you would need to store the pointer to the next 
//observer in each Observer

//observers should not have an ordering dependency like observer X having to execute before Observer B
//that would mean that these two have some kind of subtle coupling. 

//there is also a more complex implementation of a list of a subject pointing to a list of nodes which contain a pointer to an observer
//this is more flexible and allows to plug in observers however you like and therefore you can also have observers that observe multiple subjects
//the way to avoid dynamic allocation of the nodes is to pre allocate an object pool of them 
//this is superior in my opinion because link list related code ends up in the node class which makes much more intuitive sense. 

//one thing worth noting 
//we need to be carefull not to destroy observer instances that are still in use by subjects otherwise we will get dangling pointers 
//adding a removeObserver() call to the destructor of the observer could solve this 




//right now we have seen very class heavy ways of making the observer pattern but there is a more functional style 
//A more modern approach is for an “observer” to be only a reference to a method or function. In languages with first-class functions,
//and especially ones with closures, this is a much more common way to do observers.
//so your list of observers would be a list of function references ? 
//"I would tend toward a system that let you register member function pointers as observers instead of instances of some Observer interface."

int main() {
	
	PlayerState joshua{};
	PlayerStateObserver healthObserver{};
	joshua.addObserver(healthObserver);
	joshua.notify(joshua, LOW_HEALTH_EVENT);
	


}