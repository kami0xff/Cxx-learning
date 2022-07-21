

#include <iostream>


//higher order function takes functions as input and can return functions as output


//how ?
void passCallBack(auto callme) {
	callme();
}

int main() {
	auto callme = [] {std::cout << "call me"; };
	callme();


	return 0;
}