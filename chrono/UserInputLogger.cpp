#include<iostream>
#include<chrono>

int main() {
	//wait keyboard input
	//detect keyboard input record it 
	//start timer and restart it after each keystroke 30 seconds 
	//if 30 seconds elapse query database
	//and go back to waiting for keyboard input;
	auto timeIntervalPrint = std::chrono::seconds{ 5 };
	while (true) {
		auto initialTimeReading = std::chrono::steady_clock::now();
		auto t0 = initialTimeReading;
		while (t0 < initialTimeReading + timeIntervalPrint) {
			t0 = std::chrono::steady_clock::now();
		}
		std::cout << "5 seconds passed :)\n";

	}
	return 0;
}