#include <iostream>
#include <functional>

class Player {
public:
	int m_health{ 10 };
	int m_armor{ 4 };

	int getHealth() const {
		return m_health;
	}
};

struct Weapon {

	int m_damage{ 100 };
	int getDamage() const {
		return m_damage;
	}

	int getBuffedDamage() const {
		return m_damage + 10;
	}

	void operator()() {
		std::cout << "The mighty weapon has been called";
	}


};

int main() {
	
	Player p; //create instance of Player p
	Weapon w; //create instance of Weapon w

	int (Player::*member_function_pointer_player)() const = &Player::getHealth; //we have pointers to const member functions 
	int (Weapon::*member_function_pointer_weapon)()  const = &Weapon::getDamage; 

	std::cout << "current player health : " << (p.*member_function_pointer_player)() << " current player weapon damage : " << (w.*member_function_pointer_weapon)();
	//syntax is a bit weird i don't really see the case where this would be usefull either. 


	std::cout << "\n";

	Player* p_ptr = &p;
	Weapon* w_ptr = &w;

	//if we have pointer to an object (instance of class or struct) then we can use -> instead to first access the value of our object pointer and then 
	//look for the member function 
	std::cout << "current player health : " << (p_ptr->*member_function_pointer_player)() << " current player weapon damage : " << (w_ptr->*member_function_pointer_weapon)();



	//we can reasing a member function pointer
	member_function_pointer_weapon = &Weapon::getBuffedDamage;
	//member_function_pointer_weapon = &Player::getHealth; // this would not work however because its a Weapon member function pointer 
	std::cout << "\n";


	//the member function pointer and i assume also regular function pointers as well as lambdas are CALLABLES 

	//we can use them with std::invoke and std::bind

	std::cout << "BUFFED DAMAGE : " << std::invoke(member_function_pointer_weapon, w);

	//perhaps surprisingly pointer to member objects like m_damage and m_health here are also callables 
	int (Player:: * member_object_pointer_player) = &Player::m_health;
	int (Weapon:: * member_object_pointer_weapon) = &Weapon::m_damage;

	member_object_pointer_player = &Player::m_armor; //which we can also reasign

	std::cout << "\n";

	std::cout << "The player has this much armor : " << p.*member_object_pointer_player << " or " << p_ptr->*member_object_pointer_player;

	//lastly you could make something callable by overloading the () call operator 

	std::cout << "\n";
	w(); //here calling our struct Weapon hmm
	return 0;
}