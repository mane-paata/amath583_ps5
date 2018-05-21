//
// This file is part of the course materials for AMATH483/583 at the University of Washington,
// Spring 2018
//
// Licensed under Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License
// https://creativecommons.org/licenses/by-nc-sa/4.0/
//
// Author: Tommaso Buvoli
//

#include <iomanip>
#include <string>
#include <complex>
#include <iostream>
#include <fstream>

#include "Matrix.hpp"
#include "Vector.hpp"

// == Vector IO Functions  ===========================================================================
Vector readVector();
Vector readVector(std::string path);
Vector readVector(std::istream&);

void streamVector(const Vector &);
void streamVector(const Vector &, std::ostream &);
void writeVector(const Vector &, std::string);

// == Matrix IO Functions  ===========================================================================
Matrix readMatrix();
Matrix readMatrix(std::string path);
Matrix readMatrix(std::istream&);

void streamMatrix(const Matrix &);
void streamMatrix(const Matrix &, std::ostream &);
void writeMatrix(const Matrix &, std::string);

// == Number IO Functions  ===========================================================================
double readDouble();
double readDouble(std::istream&);
double readDouble(std::string);

std::complex<double> readComplexDouble();
std::complex<double> readComplexDouble( std::ifstream& file );
std::complex<double> readComplexDouble( std::string path );

void streamComplexDouble(const std::complex<double> );
void streamComplexDouble(const std::complex<double> , std::ostream &);
void writeComplexDouble(const std::complex<double> , std::string);

template <class NUMT>
void streamNumber(NUMT value)
{
    streamNumber(value, std::cout);
}
template <class NUMT>
void streamNumber(NUMT value, std::ostream& out_file)
{
    out_file << std::setprecision(15) << std::scientific << value;
}
template <class NUMT>
void writeNumber(NUMT value, std::string file_path)
{
    std::ofstream out_file (file_path);
    streamNumber(value, out_file);
}