
#include <iostream>

class PlayerState {
public:
	int positionX;
	int positionY;
	int health = 20;
	int armor;

	//subscriber
	PlayerStateObserver healthObserver;

	PlayerState() {}
	
	//publisher object
	void addHealthListener(const PlayerStateObserver& observer) {
		healthObserver = observer;
	}

	void healthEvent() {
		if (health > 0) {
			health--;
			healthObserver.notify(health);
		}
	}

};


class PlayerStateObserver {
	//subscriber object 
public:
	void notify(int health) {
		if (health == 0) {
			std::cout << "you are dead" << "\n";
		}
		else if (health < 10) {
			std::cout << "you are about to die" << "\n";
		}
		else {
			std::cout << health << "\n";
		}
	}
};

int main() {
	
	//i want to notify when the health changes and if the health goes below something give a warning

		//passing a ref of the instance of my player state object to the observer and then inside the oberserve 
		//it is store inside a member var but then i need a variable that stores the current state of the player state
	    //and poll every time the new playerState and do a comparison this is super bad in terms of performance and logic
		//much better that the playerState object would TELL the observer that something changes rather than continuous polling
		
		//so then i guess i need a ref of my observer inside my player state
		//and then i use that ref to call an event function 

	    //but there could be many observers looking at my player state then i need some kind of generic 
		//way of making a vector of them or make a big list of member variables 
		//i don't set them at constructor i set them with add listeners health add listener armor etc ?

	PlayerState joshua{};
	PlayerStateObserver healthObserver{};
	joshua.addHealthListener(healthObserver);
	while (true) {
		joshua.healthEvent();
	}


	//look how to instanciate classes syntax 
	//look how to create arrays and structs syntax 
	//how to call constructor. 
}