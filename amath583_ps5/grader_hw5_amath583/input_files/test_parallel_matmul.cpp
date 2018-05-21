#include "amath583IO.hpp"
#include "amath583.hpp"

// AMATH 583 ONLY: This is a main file for testing your implementations of task_matvec(), matvec_helper().
// The grader will use this same file to test your code. Do not modify this file for this assignment.

int main (int argc, char *argv[])
{
    Matrix A = readMatrix("input_matrix_1.txt");
    Vector x = readVector("input_vector_1.txt");
    Vector y(x.num_rows());
    
    // test matvec_helper()
    std::size_t start_index = A.num_rows() / 3;
    std::size_t end_index = A.num_rows() / 2;
    matvec_helper(A, x, y, start_index, end_index);
    writeVector(y, "mat_vec_helper.txt");
    
    // Test Standard MatrixMultiplication
    matvec(A, x, y);
    writeVector(y, "matmul_s.txt");
    
    //clear result vector
    for(int i = 0; i < y.num_rows(); i ++)
    {
        y(i) = 0.0;
    }
    
    // Test Matvec
    int min_partitions = 1;
    int max_partitions = 6;
    for(int i = min_partitions; i < max_partitions; i ++)
    {
        task_matvec(A, x, y, i);
        writeVector(y, "matmul_p" + std::to_string(i) + ".txt");
    }
}