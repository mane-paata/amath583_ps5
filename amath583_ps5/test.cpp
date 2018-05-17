#include <iostream>
#include <vector>
#include <algorithm>
int main(){
int x=10;

	auto hello = [&x](int a , int b) -> int{
		x=-3;
		std::cout << "Hello World" << std::endl;
		return a+b+x;
	};
	std::cout<<hello(10,10)<<std::endl;

	int myints[] = {1,-2,3,4,5};
	std::vector<int> y(myints, myints + sizeof(myints)/sizeof(int));
	std::sort(y.begin(),y.end());
	for (std::vector<int>::iterator it = y.begin(); it != y.end(); ++it)
    std::cout << ' ' << *it;
  std::cout << '\n';
	
	
	return 0;
}