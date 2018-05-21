#include <iostream>
#include <cstdlib>
#include <iomanip>

#include "Vector.hpp"
#include "amath583.hpp"
#include "HRTimer.hpp"

void  first_part(){
	HRTimer t1, t2, t3;
	int dim = 2;
	double two_norm = 0, norm_partition = 0, rec_norm = 0;
	int iterations = 100;
	for(int i = 0; i < 23 ; ++i){
		double avg_t1 = 0, avg_t2 = 0, avg_t3 = 0;
		for(int j =0; j < iterations; ++j){
			Vector x = randomVector(dim);
			t1.tic();
			two_norm = twoNorm(x);
			avg_t1 += t1.toc();
			t2.tic();
			norm_partition = partitionedTwoNorm(x, 4);
			avg_t2 += t2.toc() ;
			t3.tic();
			rec_norm = recursiveTwoNorm(x, 4);
			avg_t3 += t3.toc() ;
		}
		std::cout << i << "\t" << avg_t1/iterations << "\t" << avg_t2/iterations << "\t" << avg_t3/iterations << std::endl;
		dim *= 2;		
	}
}

void second_part(){
	int dim = 2;
	for(int i = 1; i <= 15 ; ++i){
		dim *= 2;
	}	
	double avg_time = 0, norm_partition = 0;
	HRTimer t;
	int iterations = 100;
	for(int part = 1; part <= 19; part += 2){
		double avg_time = 0;
		for(int i = 0; i < iterations; ++i){
			Vector x = randomVector(dim);
			t.tic();
			norm_partition = partitionedTwoNorm(x, part);
			avg_time += t.toc() ;
		}
		std::cout << part << "\t" << avg_time/iterations << std::endl;
	}
}

void third_part(){
	int dim = 2;
	for(int i = 1; i < 15 ; ++i){
		dim *= 2;
	}	
	std::cout << dim << std::endl;
	HRTimer t;
	int iterations = 1000;
	for(int levels = 0; levels <= 20; ++levels){
		double avg_time = 0, norm_recursive = 0;
		for(int i = 0; i < iterations; ++i){
			Vector x = randomVector(dim);
			t.tic();
			norm_recursive += recursiveTwoNorm(x, levels);
			avg_time += t.toc() ;
		}
		std::cout << levels << "\t" << (avg_time/iterations) << "\t" << norm_recursive << std::endl;
	}
}



int main(){

	//first_part();
	//second_part();
	third_part();
	return 0;

}