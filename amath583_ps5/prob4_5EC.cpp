#include <iostream>

#include "Vector.hpp"
#include "amath583.hpp"
#include "HRTimer.hpp"

void matrix_vector(void){
	HRTimer t;
	int dim = 1;
	const size_t iterations = 100;
  
  std::cout << "Dim" << "\t" << "matvec" << "\t" << "matvec_2" << "\t" << "matvec_4" << "\t" << "matvec_lambda_2" << "\t" << "matvec_lambda_4" << std::endl;
	for(int i = 0; i < 14; ++i){
		double avg_t1 = 0, avg_t2 = 0, avg_t3 = 0, avg_t4 = 0, avg_t5 = 0;
		for(int j =0; j < iterations; ++j){
			Vector x = randomVector(dim);
			Vector y(dim);
			Matrix A = randomMatrix(dim,dim);
			t.tic();
			matvec(A,x,y);
			avg_t1 += t.toc();

      t.tic();
		  task_matvec(A,x,y,2);
			avg_t2 += t.toc() ;
			
			t.tic();
			task_matvec(A,x,y,4);
			avg_t3 += t.toc() ;
			
			t.tic();
		  task_matvec_lambda(A,x,y,2);
			avg_t4 += t.toc() ;
			
			t.tic();
			task_matvec_lambda(A,x,y,4);
			avg_t5 += t.toc() ;
		}
		std::cout << i << "\t" << avg_t1/iterations << "\t" << avg_t2/iterations << "\t" << avg_t3/iterations << "\t" << avg_t4/iterations << "\t" << avg_t5/iterations << std::endl;
		dim *= 2;		
	}
}

int main(){

	matrix_vector();

	return 0;
}
