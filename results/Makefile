TARGET = bitonic
NPROC=$(shell echo 2\^$(p) | bc)

all:
	mpicc bitonic.c ../src/general_functions.c ../src/bitonic_merge.c ../src/merge.c -Wall -Wextra -std=c99 -lm -DTEST -DCOMPARE -O3 -o $(TARGET).out
test: utilities.h
	gcc bitonic_tests.c general_functions.c merge.c -std=c99 -lm -o $(TARGET)_tests.out
run:
	mpiexec -n $(NPROC) ./$(TARGET).out $(q)
