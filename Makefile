CXXFLAGS=-Wall 
CC=g++

build: tema3

tema3: tema3.o algorithm.o
tema3.o: tema3.cpp
algorithm.o: algorithm.cpp

run:
	./tema3 <in.txt

.PHONY: clean
clean:
	rm -fr tema3 *.o *~ 

