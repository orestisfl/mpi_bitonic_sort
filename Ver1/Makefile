TARGET = bitonic
NPROC=$(shell echo 2\^$(p) | bc)

all: merge.h
	mpicc.mpich2 $(TARGET).c bitonic_merge.c -std=c99 -O3 -DTEST -lm -o $(TARGET).out
test: utilities.h merge.h
	cc $(TARGET)_tests.c -std=c99 -lm -o $(TARGET)_tests.out
run:
	mpiexec.mpich2 -n $(NPROC) ./$(TARGET).out $(p) $(q)
