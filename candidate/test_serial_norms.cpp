#include "amath583IO.hpp"
#include "amath583.hpp"

// This is a main file for testing your implementations of:
//     (1) twoNorm()
//     (2) twoNormAscend()
//     (3) twoNormDescend()
// The grader will use this same file to test your code. Do not modify this file for this assignment.


int main (int argc, char *argv[])
{
    Vector x = readVector("input_vector_1.txt");
    Vector result(3); // store norms of x into Vector
    result(0) = twoNorm(x);
    result(1) = twoNormAscend(x);
    result(2) = twoNormDescend(x);
    writeVector(result, "test_serial_norms.txt"); // grader will compare this output
}