//
// This file is part of the course materials for AMATH483/583 at the University of Washington,
// Spring 2018
//
// Licensed under Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License
// https://creativecommons.org/licenses/by-nc-sa/4.0/
//
// Author: Tommaso Buvoli
//

#include "amath583IO.hpp"

// == Vector IO Functions  ===========================================================================
Vector readVector()
{
  return readVector(std::cin);
}

Vector readVector(std::string filename)
{
  std::ifstream inputFile(filename);
  return readVector(inputFile);
}

Vector readVector(std::istream &inputStream)
{
  std::string string_input;

  getline(inputStream, string_input);
  if (string_input.compare("AMATH 583 VECTOR") != 0) {
    std::cout << "Error: vector file does not contain a header.";
    throw;
  }

  getline(inputStream, string_input);
  if (string_input.compare("THIS IS THE END") == 0)
    return Vector(0);

  long lN = stol(string_input);
  if (lN < 0)
  {
    std::cout << "Error: vector file contains invalid vector length.";
    throw;
  }

  size_t N = lN;
  Vector v(N);

  for (size_t i = 0; i < N; i++) {
    getline(inputStream, string_input);
    v(i) = stod(string_input);
  }
  getline(inputStream, string_input);
  if (string_input.compare("THIS IS THE END") != 0)
  {
    std::cout << "Error: vector file does not contain proper footer.";
    throw;
  }
  return v;
}

void streamVector(const Vector &x)
{
    streamVector(x, std::cout);
}

void streamVector(const Vector &x, std::ostream &outputFile)
{
  outputFile << "AMATH 583 VECTOR" << std::endl; // Write header
  outputFile << x.num_rows() << std::endl;

  for (size_t i = 0; i < x.num_rows(); ++i) { // Write data
    outputFile << std::setprecision(15) << std::scientific << x(i) << std::endl;
  }

  outputFile << "THIS IS THE END" << std::endl; // Write tailer
}

void writeVector(const Vector &x, std::string filename)
{
  std::ofstream outputFile(filename);
  streamVector(x, outputFile);
}

// == Matrix IO Functions  ===========================================================================


Matrix readMatrix()
{
  return readMatrix(std::cin);
}

Matrix readMatrix(std::string filename)
{
  std::ifstream inputFile(filename);
  return readMatrix(inputFile);
}

Matrix readMatrix(std::istream &inputStream)
{
  std::string string_input;

  getline(inputStream, string_input);
  if (string_input.compare("AMATH 583 MATRIX") != 0) {
    std::cout << "Error: matrix file does not contain a header.";
    throw;
  }

  getline(inputStream, string_input);
  if (string_input.compare("THIS IS THE END") == 0)
    return Matrix(0,0);

  long num_rows = stol(string_input);
  if (num_rows < 0)
  {
    std::cout << "Error: matrix file contains invalid num rows";
    throw;
  }
  
  getline(inputStream, string_input);
  long num_cols = stol(string_input);
  if (num_cols < 0)
  {
    std::cout << "Error: matrix file contains invalid num columns";
    throw;
  }
  
  Matrix A(num_rows, num_cols);

  for (size_t i = 0; i < num_rows; i++) {
    for (size_t j = 0; j < num_cols; j++){
        getline(inputStream, string_input);
        A(i,j) = stod(string_input);
    }
  }
  getline(inputStream, string_input);
  if (string_input.compare("THIS IS THE END") != 0)
  {
    std::cout << "Error: vector file does not contain proper footer.";
    throw;
  }
  return A;
}

void streamMatrix(const Matrix &x)
{
    streamMatrix(x, std::cout);
}

void streamMatrix(const Matrix &A, std::ostream &outputFile)
{
  outputFile << "AMATH 583 MATRIX" << std::endl; // Write header
  outputFile << A.num_rows() << std::endl;
  outputFile << A.num_cols() << std::endl;

  for (size_t i = 0; i < A.num_rows(); i++)
  {
    for (size_t j = 0; j < A.num_cols(); j++)
    {
        outputFile << std::setprecision(15) << std::scientific << A(i,j) << std::endl;
    }
  }

  outputFile << "THIS IS THE END" << std::endl; // Write tailer
}

void writeMatrix(const Matrix &x, std::string filename)
{
  std::ofstream outputFile(filename);
  streamMatrix(x, outputFile);
}

// == Number IO Functions  ===========================================================================

double readDouble()
{
    return readDouble(std::cin);
}

double readDouble(std::istream& input_stream)
{
    std::string line;
    if(getline(input_stream, line))
    {
        return stod(line);
    }
    else
    {
        throw;
    }
}

double readDouble(std::string path)
{
    std::ifstream in_file (path);
    return readDouble(in_file);
}


std::complex<double> readComplexDouble(std::string path)
{
    std::ifstream in_file (path.c_str());
    return readComplexDouble(in_file);
}

std::complex<double> readComplexDouble(std::ifstream& in_file)
{
    std::string real_line = "";
    std::string imag_line = "";
    std::complex<double> c_value;
    if(in_file.is_open())
    {
        if(getline(in_file, real_line) && getline(in_file, imag_line))
        {
            in_file.close();
            std::complex<double> c_value (stod(real_line), stod(imag_line));
            return c_value;
        }
        else
        {
            std::cout << "ERROR: Complex Input file improperly formatted!";
            std::exit(-1);
        }
    }
    else
    {
        std::cout << "ERROR: Unable to read input file!";
        std::exit(-1);
    }
}

void streamComplexDouble(const std::complex<double> value)
{
    streamNumber(value, std::cout);
}

void streamComplexDouble(const std::complex<double> value, std::ostream& out_file)
{
    out_file << std::setprecision(15) << std::scientific << real(value) << std::endl;
    out_file << std::setprecision(15) << std::scientific << imag(value);
}

void writeComplexDouble(const std::complex<double> value, std::string file_path)
{
    std::ofstream out_file (file_path);
    streamComplexDouble(value, out_file);
}