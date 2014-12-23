TARGET = bitonic
NPROC=$(shell echo 2\^$(p) | bc)

all:
	mpicc bitonic.c general_functions.c bitonic_merge.c merge.c -std=c99 -lm -DTEST -o $(TARGET).out
test: utilities.h
	gcc bitonic_tests.c general_functions.c merge.c -std=c99 -lm -o $(TARGET)_tests.out
run:
	mpiexec -n $(NPROC) ./$(TARGET).out $(p) $(q)
