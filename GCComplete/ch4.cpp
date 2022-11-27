//Docs Assets folder move the textures outside of the engine on my project 
//Source directory i have src but i could rename to source
//Temp or Build directory 
//Game directory he says should contain the release build 



//need a Test directory 

//need a lib Folder for the output of the engine ??
	//would be kinda nice 

//so the way this guy does it is have the engine and the game in parrallel in terms of their project structure
//so basically i should rename app to Kami and engine to KamiEngine and move the folders that are top level inside the Kami and add some folders for building the library Docs and Temp in the Engine yeah i could see that be an ok idea 

//the output of my engine is a static library
//i feel like whenever i build my game i should have a 
//Build folder for the engine that will contain teh static library built and then a build folder for the game whch will contain the exe and all intermediate files etc 

//i have a platform folder in my engine for platform specific code OS
//engine should have clear seperation between platform agnostic code and platform specific code 


//BIG 
//OKKKK i think i have a good idea 
//so i have my main game version branch 
//then a dev branch and then feature branches that start from the dev branch :OOOO then if im working on a feature and my code does not compile yet i can always switch to other branches that still compile and work :OOO
	
//i set up this layout for each of my projects 
//Kami KamiEngine and KamiServer
//so whenever im coding i should start a branch from dev 
//and try to add some feature and when im done and it works i merge it back with DEV if i get stuck i can start other branch 
// //MASTER
//		-> DEV
//			-> FEATURE X 
//			-> FEATURE Y
//BIG

//my game and engine and server need automated builds 
//each their own i guess 
//build machine with constant backups and controlled versions for software used in the build compilers etc

//build script should build every build target 
//spit out some labeled file with inside every build file
//if possible build everyday and store each build 
//in something liek C:/Build/Kami/DATEVERSIONRELEASE on build machine




