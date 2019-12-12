# Create a Makefile to run MPI program
#

all : main

main : main.cpp
	@mpic++ -o main main.cpp function.cpp integration.cpp
run : main
	@mpiexec -np 2 ./main

clean : 
	@rm -rf main
