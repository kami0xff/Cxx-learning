


//think about spawners spawning monster in game 
//there are different types of spawners spawning different types of monsters


//now lets say we want spawners for every type of monster 
//we could brute force this by making a spawner class for each monster type but this creates a lot of redundancy (although i think its kinda nice)

//the prototype pattern offers a solution 
	//key insight an object can be used to create or spawn other objects simillar to itself. 
	//so we add a clone abstract method to our monster class such that each type of monster needs to implement one


class Monster
{
public:
	virtual ~Monster() {}
	virtual Monster* clone() = 0;

	// Other stuff...
};

class Ghost : public Monster {
public:
	Ghost(int health, int speed)
		: health_(health),
		speed_(speed)
	{}

	virtual Monster* clone() //we return a pointer to dynamic memory can we return a copy ??
	{
		return new Ghost(health_, speed_); //could the clone method not do a dynamic memory allocation ??
		//
	}

private:
	int health_;
	int speed_;
};

//the others would look simillar 
class Demon : public Monster {};
class Sorcerer : public Monster {};

//since all our monsters support a clone fucntion we don't need a spawner for each type of monster anymore
//rather we only need one spawner which will take a reference to a monster so the spawner can hold a reference to each type of monster 
//and so become a spawner of any type of monster with some state


class Spawner
{
public:
	Spawner(Monster* prototype)
		: prototype_(prototype)
	{}

	Monster* spawnMonster()
	{
		return prototype_->clone();
	}

private:
	Monster* prototype_;
};

//the neat things is that we also clone the state of the prototypical instances. 

int main() {
	Ghost ghostPrototype{ 15, 3 };
	Spawner ghostSpawner{ &ghostPrototype };

}

//define the data models in JSON for my engine
//or in binary at the bit level if i need to optimise
//

/*
* one very smart thing the author points out is that i could use prototyping in my json
* to avoid having to duplicate all the fields.
* we are adding single delegation to our data model and it already removes a lot of duplication
{
	"name": "goblin",
		"minHealth" : 20,
		"maxHealth" : 30,
		"resists" : ["cold", "poison"] ,
		"weaknesses" : ["fire", "light"]
}

{
	"name": "goblin wizard",
		"prototype" : "goblin",
		"spells" : ["fire ball", "lightning bolt"]
}

{
	"name": "goblin archer",
		"prototype" : "goblin",
		"attacks" : ["short bow"]
}
*/

//but i feel like i don't grasp this pattern 100% yet 
//its like you are making it so you can clone the state and behavior of your objects 
//such that if you define one prototypical object you can make a lot of objects from it 
//this adds a clone method to your class 
//basically in the first example when he had a spawner type for each monster type we had a more classes 
//but we just moved the duplication functionality inside the monsters themselves and then used the fact that the monstertypes are 
//polymorphic with the monster base class to have a very flexibler spawner instance creation

//but honestly this solution is not amazing to me 

//i think my favorite method was with templates 
//but he did not get into it very much and i am not that great at templates yet 
//so i think more videos and research into prototypes is needed. 

