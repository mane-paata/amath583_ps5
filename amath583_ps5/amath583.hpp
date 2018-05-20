//
// This file is part of the course materials for AMATH483/583 at the University of Washington,
// Spring 2018
//
// Licensed under Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License
// https://creativecommons.org/licenses/by-nc-sa/4.0/
//
// Author: Tommaso Buvoli
//

#include <random>
#include <algorithm> // line added 
#include <iostream> //line added
#include <thread> //line added
#include <future>
#include "Matrix.hpp"
#include "Vector.hpp"

// == HW Functions (AMATH 483 & 583) ================================
double twoNorm(const Vector& x);
double twoNormAscend(const Vector&  x);
double twoNormDescend(const Vector&  x);

double partitionedTwoNorm(const Vector& x, size_t partitions);
void ptn_worker(const Vector& x, std::size_t begin, size_t end, double& partial);
	
double recursiveTwoNorm(const Vector& x, size_t levels);
double rtn_worker(const Vector& x, std::size_t begin, std::size_t end, std::size_t level);

// == HW Functions (AMATH 583) ======================================
void task_matvec(const Matrix& A, const Vector& x, Vector& y, std::size_t partitions);
void matvec_helper(const Matrix& A, const Vector& x, Vector& y, std::size_t begin, std::size_t end);

// == Random Functions ==============================================
Vector randomVector(std::size_t n);
Matrix randomMatrix(std::size_t n, std::size_t m);

// == Operations ====================================================
void matvec(const Matrix& A, const Vector& x, Vector& y);