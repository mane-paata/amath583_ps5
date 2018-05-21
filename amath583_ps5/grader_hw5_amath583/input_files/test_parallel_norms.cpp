#include "amath583IO.hpp"
#include "amath583.hpp"

// This is a main file for testing your implementations of:
//     (1) recursiveTwoNorm()
//     (2) partitionedTwoNorm()
// The grader will use this same file to test your code. Do not modify this file for this assignment.

int main (int argc, char *argv[])
{
    Vector x = readVector("input_vector_1.txt");
    
    int min_partitions = 1;
    int max_partitions = 6;
    for(int i = min_partitions; i < max_partitions; i ++)
    {
        double norm = partitionedTwoNorm(x, i);
        writeNumber(norm, "norm_par_" + std::to_string(i) + ".txt");
    }
    
    int min_level = 1;
    int max_level = 6;
    for(int i = min_level; i < max_level; i ++)
    {
        double norm = recursiveTwoNorm(x, i);
        writeNumber(norm, "norm_lev_" + std::to_string(i) + ".txt");
    }
    
    // test rtn_worker and ptn_worker()
    std::size_t begin = x.num_rows() / 3;
    std::size_t end = x.num_rows() / 2;
    double partial = 0;
    ptn_worker(x, begin, end, partial);
    writeNumber(partial, "ptn_worker.txt");
    
    double norm_piece = rtn_worker(x, begin, end, 0);
    writeNumber(norm_piece, "rtn_worker.txt");
}