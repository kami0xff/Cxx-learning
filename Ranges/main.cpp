#include <iostream>

int main() {
	int x = 10;
	int numberList[7] = {1,2,3,4,5,6,7};
	char buffer[]{ "Hello" };
	
	std::string text = "sample text";
	char const* cstring = "cstring text"; //need const char* for string literals since they are in the data part of the program memory in ram the one that exists before runtime and cannot be changed


	//this will create two iterators begin and end that have as lifetime the duration of the loop 
	for (auto i : numberList) {
		std::cout << i;
	}
	//equivalent for loop 
	// 
	// 
	//how do you make an iterator of a fixed size array and not a vector ??
	
	//for a range based for loop the compiler will open a new scope 
	//this is so that all the variables the compiler creates to make the range based for loop work
	//get deleted at the end of the scope

	std::cout << "\n";
	{
		//this is how c++11 would do it because it was required that begin and end where the same type
		char(& __range1)[6] = buffer; //create a reference to our array/buffer
		for (char* __begin1 = __range1, *__end1 = __range1 + 6L; __begin1 != __end1; ++__begin1) {
			//1) declare two new variables that begin and end pointers compiler adds 6L to the pointe because it knows 
			//the size of the buffer and makes end point to the last element.

			//2)we compare the two pointers if they are the same we quit the loop if they are not we increment the 
			//begin pointer

			const char& c = *__begin1; //we get a variable here because in range based for loops or even regular
			//for loops we can create a variable in the header 
			//like in the above example with number list i would be the variable inside the loop
			std::cout << c;
		}
	}

	std::cout << "\n";

	//in c++14 and above the restriction on begin and end needing to be the same type was removed 
	//so the loop looks like this 
	{
		//essentially just moving the begin and end variables intialization and creation outside of the for loop
		//header
		char(&__range1)[6] = buffer;
		char* __begin1 = __range1;
		char* __end1 = __range1 + 6L;
		for (; __begin1 != __end1; __begin1++) {
			const char& c = *__begin1;
			std::cout << c;
		}
	}

	std::cout << "\n";
	//note that the above is for normal C style arrays for vectors the compiler would create iterators. 




	return 0;
}