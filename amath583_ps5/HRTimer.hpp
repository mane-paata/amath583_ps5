//
// This file is part of the course materials for AMATH483/583 at the University of Washington,
// Spring 2018
//
// Licensed under Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License
// https://creativecommons.org/licenses/by-nc-sa/4.0/
//
// Author: Tommaso Buvoli
//

// EXAMPLE CODE:
//
//    HRTimer t;
//    // == STANDARD USAGE ==============
//    t.tic();
//    // PLACE CODE BLOCK TO TIME HERE
//    std::cout << "seconds elapsed: " << t.toc() << std::endl;
//    
//    // == ALTERNATIVE USAGE ===========
//    auto start = t.tic();
//    // PLACE CODE BLOCK TO TIME HERE
//    std::cout << "seconds elapsed: " << t.toc(start) << std::endl;


#pragma once
#include <fstream>
#include <ctime>

class HRTimer
{
    private:
        typedef std::chrono::high_resolution_clock::time_point hr_time;
        typedef std::chrono::duration<double> hr_duration;

    public:
        HRTimer() : _start() {}
    
        hr_time tic()
        {
            _start = std::chrono::high_resolution_clock::now();
            return _start;
        }
    
        double toc()
        {
            return toc(_start);
        }
    
        double toc(hr_time start)
        {
            hr_time end = std::chrono::high_resolution_clock::now();
            hr_duration time_span = std::chrono::duration_cast<hr_duration>(end - start);
            return time_span.count();
        }

private:
    hr_time _start;
};