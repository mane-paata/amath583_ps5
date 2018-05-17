#
# This file is part of the course materials for AMATH483/583 at the University of Washington,
# Spring 2018
#
# Licensed under Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License
# https://creativecommons.org/licenses/by-nc-sa/4.0/
#
# Author: Tommaso Buvoli
#

CC     = c++
OPTS   = -O3 -DNDEBUG -pthreads
LANG   = -std=c++11
PICKY  = -Wall 
CFLAGS = $(LANG) $(OPTS) $(PICKY) 

OBJFILES = Matrix.o Vector.o amath583.o amath583IO.o
EXEFILES = test_serial_norms.exe test_parallel_norms.exe test_parallel_matmul.exe
.PHONY: all clean

all: $(EXEFILES)
	
%.exe: %.o $(OBJFILES)
	$(CC) $(CFLAGS) $< $(OBJFILES) -o $@
%.o : %.cpp
	$(CC) -c $(CFLAGS) $< -o $@
clean:
	rm -f *.o *.exe
