int main() {
	int* ip;
	const int* cip;
	const int* const cipc = ip;

	auto aip = ip; //int*
	auto acip = cip; //const int*
	auto acicp = cipc; //the type deduced by auto here strips of the top level const 
	//result in const int* instead of const int* const

	
}