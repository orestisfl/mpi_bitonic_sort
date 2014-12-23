TARGET = bitonic
NPROC=$(shell echo 2\^$(p) | bc)

all: utilities.h
	mpicc $(TARGET).c  -std=c99 -O3 -lm -o $(TARGET).out
test: utilities.h
	cc $(TARGET)_tests.c  -std=c99 -lm -o $(TARGET)_tests.out
run:
	mpiexec -n $(NPROC) ./$(TARGET).out $(p) $(q)
