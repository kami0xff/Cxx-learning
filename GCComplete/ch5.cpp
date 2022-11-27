//Initalization / core main loop / shutdown
// 
// 
//Initialization will prepare the canvas for painting pixels
//main loop accepts and translates user input, changes the game state, renders the game state until the loop is broken

//shutdown code releases resources. 

//lets think what do i need to initalize
//2) Random number generator 
//3) Logger
//1) my window and do the call the finds the opengl functions
//)other game systems physics AI and so on. 

//be carefull with c++ constructors for initializing game objects 
//c++ global objects are initialized before the entry point main() but in any random order

//global object pointers are much better than global objects. 
//some objects are naturaly global such as audio system 

//objects are released in the inverse order in which they were instantiated. 
//function parameters pushed on the stack right to left 

//TODO i need a game option class

//why do we have lua scripting in game engine i think i just understood what the point is 
//basically if your main code is using a script to perform a taks you don't need to recompile your main code if you want to change 
//that small task you can just modify the lua script file and re run your program or the script

//i guess this is super usefull when the project is huge with big compile times you get more flexibility 
//
