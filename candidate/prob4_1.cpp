#include <iostream>
#include <cstdlib>
#include <iomanip>
#include "Vector.hpp"
#include "amath583.hpp"

int main(){
	double norm2 = 0, norm_asc = 0, norm_descend = 0;
  for(int i=0; i < 100; ++i){
		Vector x = randomVector(1000);

	{

		norm2 += twoNorm(x);
		//std::cout << "The vector norm is" << std::setprecision(15) << norm2 << std::endl;
	}

	{
		norm_asc += twoNormAscend(x);
		//std::cout << "The two norm of sorted (ascending) vector is " << std::setprecision(15) << norm_asc << std::endl;
	}
	{
		norm_descend += twoNormDescend(x);
		//std::cout << "The two norm of sorted (descending) vector is " << std::setprecision(15) << norm_descend << std::endl;
	}
	/*{
		double norm_partition;
		norm_partition = partitionedTwoNorm(x, 4);
		std::cout << "The partitioned two norm of vector is " << std::setprecision(15) << norm_partition << std::endl;
	}
	
		Matrix A = randomMatrix(5,3);
		Vector p = randomVector(A.num_cols());
		Vector q(A.num_rows()), r(A.num_rows());
		task_matvec(A,p,q,2);
		matvec_helper(A,p,r,0,A.num_rows());
		std::cout << "Matrix vector product is" << std::setprecision(15) << std::endl;
		for(size_t i=0; i<q.num_rows();++i){
			std::cout << q(i) << "::" << r(i) << std::endl;
		}

	double norm_recursive;
	norm_recursive = recursiveTwoNorm(x,4);
	std::cout << "The recursive two norm of vector is " << std::setprecision(15) << norm_recursive << std::endl;*/
}
std::cout << "The vector norm is" << std::setprecision(15) << norm2/100 << std::endl;
std::cout << "The two norm of sorted (ascending) vector is " << std::setprecision(15) << norm_asc/100 << std::endl;
std::cout << "The two norm of sorted (descending) vector is " << std::setprecision(15) << norm_descend/100 << std::endl;
return 0;
}