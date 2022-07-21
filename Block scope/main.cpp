#include <iostream>
int main() {
	int val = 1;
	if (true) {
		std::cout << "first : " << val << "\n";//1
		int val = 10;
		if (true) {
			std::cout << "above : " << val << "\n"; //here we got the 10 hmm
			int val = 12;
			std::cout << "below : " << val << "\n"; //here we use 12
		}
		std::cout << "last : " << val << "\n"; //10
	}
	//int val = 12;compiler error multiple initializations
	//well this does not compile if i don't define val before the if
	std::cout << "value defined inside if :" << val << "\n"; //1
	return 0;
}