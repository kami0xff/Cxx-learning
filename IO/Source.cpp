#include <iostream>

int main() {

	//std::cout creates a buffer before issueing a system call
	//having to issue system calls everytime we want to write a character
	//is terrible for performance this is why this buffer exists 

	//std::endl has the property that it forces this buffer to be flushed and a system call to be issued
	

	std::cout << "aa" << std::endl;

	//disableing syncing
	std::ios_base::sync_with_stdio(false);


	return 0;
}