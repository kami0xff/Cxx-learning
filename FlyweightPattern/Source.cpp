#include <iostream>


class Mesh {};
class Texture {};
class Vector {};
class Color {};

int main() {


	//imagine the scenario where you want to render a whole forest in your game
	//a tree class might look as follows but if you have to render tens of thousands of them 
	//and each of them is an object that holds a model and a texture thats too much memory to be sending to the GPU

	class Tree
	{
	private:
		Mesh mesh_;
		Texture bark_;
		Texture leaves_;
		Vector position_;
		double height_;
		double thickness_;
		Color barkTint_;
		Color leafTint_;
	};

	//now one thing that we can use is that all these tree will most likely use the same textures and the same model
	//so most of the fields of these thousands of objects are actually the same 

	//we have to model that explicitly by spliting our initial tree class in half 
	class TreeModel
	{
	private:
		Mesh mesh_;
		Texture bark_;
		Texture leaves_;
	};

	//and we will make a single instance of this tree model class 
	//and use a reference of it in our Tree class which will be made thousands of time 
	class Tree2 {
	private:
		TreeModel& model_;
		Vector position_;
		double height_;
		double thickness_;
		Color barkTint_;
		Color leafTint_;
	};
	//all that remains in Tree is the information that is instance specific and thats the key behind this pattern 
	//we can save a lot of memory in scenarios like this. 

	//the gpu can also do somehting like this with instance rendering where it will use the same mesh etc for many objects to render. 

	//to summarize flyweight as its name suggests comes up when you need more lightweight objects usually because you have too many of them. 
	//the pattern solves this issue by separating an object data into two categories the non instance specific or "context-free" and instance specific data
	// 
	//


	//another example is imagine if we wanted to have a tilled world with each tile having a type of terrain and the terrain type affect the player 
	//movement speed we can think of 3 approaches. 

	//1) each terrain tile is an instance of some terrain type object : This is abismal for memory performance. 
	//2) each terrain is just an enum type basically a named number such that we can write code that will check for terrain type and generate the 
	//effects such terrain has on the player but this is kinda weird if we think about it we are sort of moving the state that belongs to a terrain type out of the 
	//terrain type which is kind of ugly 

	//3) the best approach is that each tile hold a reference to a terrain type this way we don't need many instances and the state of each terrain tyle 
	//remains local. 


	//the lifetime of the terrain instances could be tricky to manage we should loosely couple them with teh world class trough an interface. 


	//the big advantage of the flyweight pattern is that it gives the advantages of object oriented programming without tons of objects 
	//if we find ourselves doing and enum with lots of switches on it then consider doing using this pattern 
	//theremight be cases in which you need to couple this pattern with factory methods that will check if the flyweight object already exists or not 
	//it is best to create flyweights on demand. 

	//in order to return flyweights you have alredy created you will have to keep track of the pool that you have already created in some cases 
	//there might be many and this is where the object pool pattern might become usefull. 


	return 0;
}