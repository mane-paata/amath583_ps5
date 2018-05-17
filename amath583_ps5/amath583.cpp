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
    /*std::sort(y.begin(), y.end());
    for(int j = 0; j  < y.num_rows(); ++j){
        sum += y(j)*y(j);
    }
    norm_ascend = std::sqrt(sum);
    return norm_acsend;*/
}

/*double twoNormDescend(const Vector&  x)
{
    double norm_descend = 0, sum = 0;
    Vector y;
    for(int i = 0; i < x.num_rows(); ++i)
        y(i) = x(i);
    std::sort(y.begin(), y.end());
    for(int j = y.num_rows(); j > 0; --j)
        sum += y(j)*y(j);
    
    norm_descend = std::sqrt(sum);
    return norm_descend;
}*/

double partitionedTwoNorm(const Vector& x, size_t partitions)
{
    return 0;
}

void ptn_worker(const Vector& x, std::size_t begin, size_t end, double& partial)
{

}
	
double recursiveTwoNorm(const Vector& x, size_t levels)
{
    return 0;
}

double rtn_worker(const Vector& x, std::size_t begin, std::size_t end, std::size_t level)
{
    return 0;
}

// == HW Functions (AMATH 583) ======================================

void task_matvec(const Matrix& A, const Vector& x, Vector& y, std::size_t partitions)
{

}

void matvec_helper(const Matrix& A, const Vector& x, Vector& y, std::size_t begin, std::size_t end)
{

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