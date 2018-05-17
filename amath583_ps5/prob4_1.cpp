#include <iostream>
#include <cstdlib>

#include "Vector.hpp"
#include "amath583.hpp"

int main(int argc, char* argv[]){

	if(argc!=2)
		{std::cout << "Usage: " << argv[0] << "1/2/3" << std::endl;}

	int d = 0;
	d = atoi(argv[1]);

	Vector x(1000);
	x = randomVector(1000);

	if(d == 1){
	  double norm2;
		norm2 = twoNorm(x);
		std::cout << "The vector norm is" << norm2 << std::endl;
	}

	else if(d == 2){
		double norm_asc;
		norm_asc = twoNormAscend(x);
		std::cout << "The two norm of sorted (ascending) vector is " << norm_asc << std::endl;
	}
	/*else if(d == 3){
		double norm_descend;
		norm_descend = twoNormDescend(x);
		std::cout << "The two norm of sorted (descending) vector is " << norm_descend << std::endl;
	}*/
	else{
		std::cout << "choose from 1/2/3" << std::endl;
	}
	

	return 0;
}