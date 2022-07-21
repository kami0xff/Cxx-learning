
#include <type_traits>
#include <iostream>

//SFINAE
//stands for substitution failure is not an error
//jason turner : "its a terrible mess"
//prior to c++ 20 concepts 

//related is the topic of overload resolution 
//to compile a function call the compiler must perform a name lookup
	//which for functions may be and argument dependent lookup
	//and for function templates may involve template argument deduction 

//if the lookup results in more than one candidate function then overload resolution is performed
//to select the function that will actually be called.

template<typename Float, typename = std::enable_if_t<std::is_floating_point_v<Float>>>
auto go(Float const value1, Float const value2) {
	return value1 + value2;
}

//C++ 20
//this is one way of doing it with the requires keyword 
template<typename Float>
auto go2(Float const value1, Float const value2) requires std::is_floating_point_v<Float>{
	return value1 + value2;
}

//but we could also create a concept
template<typename T>
concept is_floating_point = std::is_floating_point_v<T>;

template<is_floating_point Float>
auto go3(Float const value1, Float const value2){
	return value1 + value2;
}




//in this function signature you could have two different floating poitn types 
//go4(1.3,3.4f) double float
//but in the others with single template parameters you would not be able to
is_floating_point auto go4(is_floating_point auto const value1, is_floating_point auto const value2) {
	return value1 + value2;
}

//with concepts we can constrain parameters return types as well as regular values
//best practices are still up in the air 
//terse syntax is -> concept auto


int main() {
	std::cout << go(1.1, 2.3) << '\n';
	std::cout << go2(1.1, 2.3) << '\n';
	std::cout << go3(1.1, 2.3) << '\n';

	is_floating_point auto val = go4(1.3, 3.5);

	return 0;
}