


//

#include<iostream>
#include<string>

//function overloading or operator overloading
//functions with a common name but different parameters 
//for example the function plus here is defined for two integers as a parameter and two std::strings
//the problem of this approach is that it does not scale very well repeats boiler plate logic often

int plus(int a, int b) {
	return a + b;

}

long plus(long a, long b) {
	return a + b;

}

double plus(double a, double b) {
	return a + b;

}


std::string plus(std::string a, std::string b) {
	return a + b;
}



//template function for add 
//this time we only define one method and we parameterize the types that the add function works with 
template <typename T>
T add(T a, T b) {
	return a + b;
}


template <typename T, typename U>
T addmix(T a, U b) {
	return a + b;
}


//templatize all parameters and the return value
template <typename R, typename T, typename U>
R max(T a, U b) {
	return a < b ? b : a;
}


int main() {

	int i = 5, j = 6, k;
	long l = 10, m = 5, n;
	double a = 10.5, b = 5.5, d;

	//overloaded functions
	k = plus(i, j);
	n = plus(l, m);
	d = plus(a, b);

	std::cout << k << "\n";
	std::cout << n << "\n";
	std::cout << d << "\n";


	//this time with our template function
	k = add<int>(i, j);
	n = add<long>(l, m);
	d = add<double>(a, b);

	//we can ommit the explicit type information
	//the c++ compiler is able to deduce the types for us 
	k = add(i, j);
	n = add(l, m);
	d = add(a, b);

	std::cout << k << "\n";
	std::cout << n << "\n";
	std::cout << d << "\n";


	//since we have defined both our parameters to be T we need cannot have 
	//add(int,double)
	//add(int,float)
	//add(int,long)
	//they need to be the same type T
	//add(i,l)

	//if we wanted to have two different types as parameters we would need to extend 
	//our template function definition to have a typename T and a typename U


	//in the case of our max template function we either have to explicit about all the types
	//or only about the return type the compiler will then deduce the parameters

	double d = max<double>(5.5,2); //this will tell the compiler that all parameters are double T U and R
	int i = max<int, char, char>('a', 'b');

	std::cout << "max" << d << "\n";
	std::cout << "max" << i << "\n";




	return 0;
}
