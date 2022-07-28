
#include <vector>

int main() {
	std::vector<double> vecdouble;
	typedef decltype(vecdouble.begin()) vecIterator;
	typedef decltype(42) myint;

	//the way i understand it is that decltype returns us the type of something which can be usefull to write meta stuff. 


}