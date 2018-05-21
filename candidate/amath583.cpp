//
// This file is part of the course materials for AMATH483/583 at the University of Washington,
// Spring 2018
//
// Licensed under Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License
// https://creativecommons.org/licenses/by-nc-sa/4.0/
//
// Author: Tommaso Buvoli
//

#include "amath583.hpp"

// == HW Functions (AMATH 483 & 583) ================================

double twoNorm(const Vector& x)
{   
    double norm2 = 0, sum = 0;
    for(int i = 0; i < x.num_rows(); ++i){
        sum += x(i)*x(i);
    }
    norm2 = std::sqrt(sum);
    return norm2;
}

double twoNormAscend(const Vector&  x)
{
    double norm_ascend = 0, sum = 0;
    int rows = 0;
    rows = x.num_rows();
    Vector y(rows);
    for(int i = 0; i < x.num_rows(); ++i)
        y(i) = x(i);
    double *start, *end;
    start = &y(0);
    end = &y(rows);
    std::sort(start,end);
    for(int j = 0; j  < y.num_rows(); ++j){
        sum += y(j)*y(j);
    }
    norm_ascend = std::sqrt(sum);
    return norm_ascend;
}

double twoNormDescend(const Vector&  x)
{
    double norm_descend = 0, sum = 0;
    int rows = 0;
    rows = x.num_rows();
    Vector y(rows);
    for(int i = 0; i < x.num_rows(); ++i)
        y(i) = x(i);
    double *start, *end;
    start = &y(0);
    end = &y(rows);
    std::sort(start,end);
    for(int j = y.num_rows(); j  >= 0; --j){
        sum += y(j)*y(j);
    }
    norm_descend = std::sqrt(sum);
    return norm_descend;
}

double partitionedTwoNorm(const Vector& x, size_t partitions)
{
   std::vector<double> partials(partitions, 0.0);
   std::vector<std::thread> tids;
   double norm2 = 0, sum =0;
   int eip = 0, rem = 0;
   size_t begin = 0, end = 0;
   eip = x.num_rows()/partitions;
   rem = x.num_rows() % partitions;
   for(size_t i = 0; i < partitions; ++i){
        size_t actual_eip = eip;
        if(rem > 0){
            actual_eip += 1;
            rem -= 1;
        }
        begin = end ;
        end = begin + actual_eip;
        tids.push_back(std::thread(ptn_worker, std::ref(x), begin, end, std::ref(partials[i])));
   }

   for (size_t i = 0; i < partitions; ++i)
   {
       tids[i].join();
       sum += partials[i]; 
   }

   norm2 = std::sqrt(sum);
   return(norm2);
   }



void ptn_worker(const Vector& x, std::size_t begin, size_t end, double& partial)
{
    for(int i = begin; i < end; ++i){
        partial += x(i)*x(i);
    }
}
	
double recursiveTwoNorm(const Vector& x, size_t levels)
{
    std::future<double> sum = std::async(std::launch::deferred, rtn_worker, std::ref(x), 0, x.num_rows(), levels);
    double norm2 = std::sqrt(sum.get());
    return norm2;
}

double rtn_worker(const Vector& x, std::size_t begin, std::size_t end, std::size_t level)
{
    size_t total_elements = end - begin;
    if ((level == 0) || total_elements < 2 )
    {
        double sum = 0;
        for(int i = begin; i < end; ++i){
            sum += x(i)*x(i);
        }
        return sum;
    }
    else
    {
        size_t mid_point = begin + (total_elements / 2) ;
        return rtn_worker( std::ref(x), begin, mid_point, level-1) +  rtn_worker( std::ref(x) , mid_point, end, level-1);
    }
}

// == HW Functions (AMATH 583) ======================================

void task_matvec(const Matrix& A, const Vector& x, Vector& y, std::size_t partitions)
{
   std::vector<std::thread> tids;
   int eip = 0, rem = 0;
   size_t begin = 0, end = 0;
   eip = A.num_rows()/partitions;
   rem = A.num_rows() % partitions;
   for(size_t i = 0; i < partitions; ++i){
        size_t actual_eip = eip;
        if(rem > 0){
            actual_eip += 1;
            rem -= 1;
        }
        begin = end ;
        end = begin + actual_eip;
        tids.push_back(std::thread(matvec_helper, std::ref(A), std::ref(x), std::ref(y), begin, end)); 
   }
   for(size_t i=0; i< partitions; i++){
      tids[i].join();
   }
}

void matvec_helper(const Matrix& A, const Vector& x, Vector& y, std::size_t begin, std::size_t end)
{
    for (size_t i= begin ; i < end; ++i){
        y(i) = 0;
        for ( size_t j=0 ; j < A.num_cols(); ++j){
            y(i) += A(i,j) * x(j);
        }
    }
}

// extra credit
void task_matvec_lambda(const Matrix& A, const Vector& x, Vector& y, std::size_t partitions)
{
   std::vector<std::thread> tids;
   int eip = 0, rem = 0;
   size_t begin = 0, end = 0;
   eip = A.num_rows()/partitions;
   rem = A.num_rows() % partitions;
   for(size_t i = 0; i < partitions; ++i){
        int actual_eip = eip;
        if(rem > 0){
            actual_eip += 1;
            rem -= 1;
        }
        begin = end ;
        end = begin + actual_eip;
        tids.push_back(std::thread(
            [&A, &x, &y, begin, end]() -> void
            { 
                for (size_t i= begin ; i < end; ++i){
                    for (size_t j = 0; j < A.num_cols(); ++j) {
                        y(i) += A(i, j) * x(j);
                    }
                }
            })
        );
   }
   for(size_t i=0; i< partitions; i++){
      tids[i].join();
   }
}


// == Random Functions ==============================================

Vector randomVector(std::size_t n)
{
    std::default_random_engine generator;
    std::uniform_real_distribution<double> distribution(-100.0, 100.0);
    
    Vector x(n);
    for (std::size_t i = 0; i < x.num_rows(); i++)
    {
        x(i) = distribution(generator);
    }
    return x;
}

Matrix randomMatrix(std::size_t m, std::size_t n)
{
    static std::default_random_engine             generator;
    static std::uniform_real_distribution<double> distribution(-100.0, 100.0);
    
    Matrix A(m,n);
    for (std::size_t i = 0; i < A.num_rows(); i++)
    {
        for(std::size_t j = 0; j < A.num_cols(); j++)
        {
            A(i,j) = distribution(generator);
        }
    }
    return A;
}

// == Operations ====================================================
void matvec(const Matrix& A, const Vector& x, Vector& y)
{
    double sum = 0;
    for(std::size_t i = 0; i < A.num_rows(); i ++)
    {
        sum = 0.0;
        for(std::size_t j = 0; j < A.num_cols(); j ++)
        {
            sum += A(i,j) * x(j);
        }
        y(i) = sum;
        
    }
}