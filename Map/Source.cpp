#include <map>
#include <iostream>


struct Spell {
	std::string name;
	int damage;
	std::string attribute;
};

struct Example{
	int number;
	double numberList[2];
};

int main() {

	//the {} syntax for initalization is refered to as uniform initialization

	//

	std::map<int, std::string> mapIdToName{
		{0, "joshua"},
		{1, "kami"},
		{2, "0xff"}
	};

	for (auto keyVal : mapIdToName) {
		std::cout << keyVal.first << " : " << keyVal.second << "\n";
	}
	
	std::map<int, Spell> numberToSpellMap{
		{1, Spell{"fireball", 100, "fire"}}, //interesting how im creating these object as rvalues temporary
		{2, Spell{"iceShard", 132, "ice"}}
	};

	Spell shadowBolt{ "shadowBold",200, "shadow" }; //constructing and initializing an object Spell

	for (auto keyVal : numberToSpellMap) {
		std::cout << keyVal.first << " : " << keyVal.second.name << keyVal.second.damage << keyVal.second.attribute << "\n";
	}


	//using the initializer list for more complex structs or classes will try to fill things in linearly 
	Example eg{ 1,2,3 }; //will fill 1 for the number and 2,3 in the list 
	Example ex{ 1,2 }; //will put 1 in number and 2 as the first element of the list 

}