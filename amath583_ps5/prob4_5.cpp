#include <iostream>

#include "Vector.hpp"
#include "amath583.hpp"
#include "HRTimer.hpp"

void matrix_vector(void){
	HRTimer t1, t2, t3;
	int dim = 1;
	const size_t iterations = 100;
	for(int i = 0; i < 14; ++i){
		double avg_t1 = 0, avg_t2 = 0, avg_t3 = 0, avg_t4 = 0;
		for(int j =0; j < iterations; ++j){
			Vector x = randomVector(dim);
			Vector y(dim);
			Matrix A = randomMatrix(dim,dim);
			t1.tic();
			matvec(A,x,y);
			avg_t1 += t1.toc();
			t2.tic();
		  task_matvec(A,x,y,2);
			avg_t2 += t2.toc() ;
			t3.tic();
			task_matvec(A,x,y,4);
			avg_t3 += t3.toc() ;
			t3.tic();
			task_matvec(A,x,y,8);
			avg_t4 += t3.toc() ;
		}
		std::cout << i << "\t" << avg_t1/iterations << "\t" << avg_t2/iterations << "\t" << avg_t3/iterations << "\t" << avg_t4/iterations << std::endl;
		dim *= 2;		
	}
}

int main(){

	matrix_vector();

	return 0;
}
