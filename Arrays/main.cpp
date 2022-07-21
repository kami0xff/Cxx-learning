#include <iostream>
#include <array>
#include <vector>

int main() {

	//one way to make an array at runtime of size n
	int n;
	std::cout << "enter the size of the array : ";
	std::cin >> n;

	int* a = (int*)malloc(n * sizeof(int));
	//is it possible to range for here ???
	for (int i = 0; i < n; i++) {
		a[i] = i;
		//std::cout << a[i] << "\n";
	}
	delete(a);//you have to delete this dynamically allocated memory yourself 
	//this is very bad C++ code nowadays we really want to make use of RAII


	//one better way would be to wrap our pointer in a class that implements RAII (not sure if i do it right ?)
	class Dynarr {
	public:
		int* m_p;
		int m_size;
		Dynarr(int n) {
			m_p = (int*)malloc(n * sizeof(int));
			m_size = n;
		}
		~Dynarr() {
			delete(m_p);
			std::cout << "destructor called memory is freed \n";
		}

		void FillAndPrint() const {
			for (int i{ 0 }; i < m_size; i++) {
				m_p[i] = i;
				std::cout << m_p[i] << "\n";
			}
		}
	};
	
	{
		Dynarr dynarr{ n }; //dont'have to use the = operator ??
		dynarr.FillAndPrint();
		
		//copy semantics / assignment semantics ??
		//comparison semantics A==B
		//


		//THIS CODE WILL CAUSE EXCEPTION IN Array.exe
		//but why maybe the copy dynarrcopy at the end of the scope calls delete on something that has already been deleted.
		
		
		//Dynarr dynarrcopy = dynarr;
		//this gave me a runtime bug im not sure what it did honestly here 
		//like this would make a copy of dynarr and set dynarrcopy to dynarr right some pointer and size

		//dynarrcopy.FillAndPrint();
		//vs gives me an assertion error here but what does it mean ?? 
		//where does dynarrcopy point to ??
		//TO BE INVESTIGATED 

	}//calls destructor and frees the memory that the pointer owns on its own we don't have to call delete on the pointer


	//another way to make an array in dynamic memory with size given at runtime
	std::vector<int> vec;
	vec.resize(n);
	for (int i = 0; i < vec.size(); i++) {
		vec[i] = i;
		//std::cout << vec[i] << "\n";
	}


	//static array allocated on stack 
	int arr[]{1,2,3}; // we don't need the = operator ?
	std::array<int, 3> stdarr{1,2,3};

	//syntax for accessing array elements is synonymous to pointer arithmetic 
	//for instance 


	int carray[4]{ 1,2,3,4 }; //this got me 4 integers in memory next to each other in memory so a block of 16 bytes
	std::cout << sizeof(carray) << "\n";//prints 16 the size in bytes of the array



	std::cout << carray[1]; //will print 2
	std::cout << *(carray + 1); //will print 2
	std::cout << 1[carray]; // will print 2 because this will turn into *(1 + carray) which is equivalent to *(carray + 1)
	//but this last one is not intuitive so we don't write this kind of code generally 






	return 0;
}