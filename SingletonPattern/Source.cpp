//use this pattern sparingly it is the most overused pattern and abused one
//making singletons with a static get instance method is just the same as writting in the global scope. which in some case is desired


//Singleton : Ensures a class has one instance and provides a global point of access to it. 

//there are times a class cannot perform correctly if there are multiple instances of it. 
//common case is when the class interfaces with an external system that has its own state like a database 
//or a filesystem API wrapper for example 

//if a lot of different systems depend on your singleton class the singleton provides global easy access to an instance. 
//




class Singleton {
private:
	Singleton() {} //private constructor to avoid the creation of new instances
	static Singleton* m_instance; //static instance member that holds an instance of the class

public:
	static Singleton* getInstance() {
		if (m_instance == nullptr) {
			m_instance = new Singleton(); //is this mandatory 
		}
		else {
			return m_instance;
		}
	}
};

//this patterns definitely has some good points 
	//+ we don't create an instance if don't need it
	//we don't have to pass around const references of our instances everywhere
	//a common alternative to a singleton is a class with static members variables the problem is that the compiler initializes static before main()
	//and sometimes you might need some kind of runtime information also the compiler does not guarantee the order in which static members are intialized
	//another + is that singletons can be subclassed 

class FileSystem
{
public:
	static FileSystem& instance();

	virtual ~FileSystem() {}
	virtual char* readFile(char* path) = 0;
	virtual void  writeFile(char* path, char* contents) = 0;

protected:
	FileSystem() {}
};

class PS3FileSystem : public FileSystem
{
public:
	virtual char* readFile(char* path)
	{
		// Use Sony file IO API...
	}

	virtual void writeFile(char* path, char* contents)
	{
		// Use sony file IO API...
	}
};

class WiiFileSystem : public FileSystem
{
public:
	virtual char* readFile(char* path)
	{
		// Use Nintendo file IO API...
	}

	virtual void writeFile(char* path, char* contents)
	{
		// Use Nintendo file IO API...
	}
};


//we can make the getInstance() function return whatever instance we like at compile time 
//we might want to return a debug instance or a PS3 or a WII instance 
//and since we are using preprocessor directives at compile time these directives will decide what concrete type
//FileSystem::instance() will return 

FileSystem& FileSystem::instance()
{
#if PLATFORM == PLAYSTATION3
	static FileSystem* instance = new PS3FileSystem();
#elif PLATFORM == WII
	static FileSystem* instance = new WiiFileSystem();
#endif

	return *instance;
}
//maybe this is something simillar we could see in factory methods 




//the bad
//singletons are global variables and global state 
//and as the author said debuggin global state can be cancer 
// 
//if a function does not touch global state it is easy to reason about "If that function doesn’t touch any global state, 
//we can wrap our heads around it just by understanding the body of the function and the arguments being passed to it."


//Now, imagine right in the middle of that function is a call to SomeClass::getSomeGlobalData(). To figure out what’s 
//going on, we have to hunt through the entire codebase to see what touches that global data.


//singletons encourage coupling 
//lets say im writing code that will play a sound when some fireball hits a tree if i have an audio singleton i might just include it 
//and use the singleton getInstance() AND BOOM my physics and audio code is coupled 

//"By controlling access to instances, you control coupling."

//the singleton pattern is not concurency friendly

//singleton is just global state encapsulated in a class
//

//beware of classes adding functionalities to another class 
//generally this is dubious code, these are often manager classes like 
//Bullet and Bulletmanager in the book. 

//singletons provide both single instance and global access but there are cases where
	//we just want global access -> static class
	//we just want a single instance -> instanciated boolean flag in the class that is set to true in the constructor
	//the downside of this tho is that it guarantees single instance at runtime whereas the singleton guarantees it at compile time

	
	//and there are other ways of achieving these goals without the singleton pattern
	
//the main reason we use singletons is for convienient access if we need to use some class in many parts
//of our code it is very convienient to have a singleton so we can get our hands on the object everywhere we want to 
//but the problem is that we can then also get our hands on the object everywhere we don't want to. 
//and generally we want to constrict variables or objects to the scope in which they are needed

//but what are our other solutions ?? 

//Passing the object as a parameter : simply pass in the object that you need in the function that you need 
//as a parameter (this is also refered to as dependency injection sometimes although dependency injection is also used for other cases)
//
//in some cases passing in an object makes perfect sense for example a function that is rendering something on the screen 
//passing to it our object that represents the graphics device and API that we define makes perfect sense
//however passing a LOG object in every single function in our codebase because we might want to log things in some place 
//is really annoying. Because unlike the previous case it is not related to the direct purpose of the function. 

//if there is some kind of inheritance hierarchy we could get it from a base class.
//and it would have to be a static member of the base class 

//instead of a bunch of singletons we could make one big global object 
class Game
{
public:
	static Game& instance() { return instance_; }

	// Functions to set log_, et. al. ...

	Log& getLog() { return *log_; }
	FileSystem& getFileSystem() { return *fileSystem_; }
	AudioPlayer& getAudioPlayer() { return *audioPlayer_; }

private:
	static Game instance_;

	Log* log_;
	FileSystem* fileSystem_;
	AudioPlayer* audioPlayer_;
};
//and through it we could access the systems in most cases games will need global state anyways
//this does cause more code coupled to the game class but reduces the number of globall classes but not realy 
//because we are making those classes global anyways by coupling them with the game class so its just indirect now and kind of stupid 
//we get both coupling global access to our classes and perhaps multiple instance for classes we wanted single instance. i rather not do this 


//so far honestly it feels like there is nothing good out of this singleton pattern there are valid 
//for and against arguments at every stage of the thing 
// 


//im not sure what to make it i think the best is to follow the book author advice of not really using them 
//unless we want both the feature of a globally accessible instance and that is globally visible
//otherwise use static classes or the instanciated boolean flag assert ?? 
//think about access to the object should it be global ?? 
//can we pass it as param ? can we refactor the class as a whole ?  many things to consider. 



int main() {
	Singleton* s = Singleton::getInstance();
}