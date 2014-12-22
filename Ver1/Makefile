TARGET = bitonic
NPROC=$(shell echo 2\^$(p) | bc)

all:
	mpicc $(TARGET).c $(TARGET)_merge.c -std=c99 -O3 -lm -o $(TARGET).out
test:
	cc $(TARGET)_tests.c merge.c -std=c99 -lm -o $(TARGET)_tests.out
run:
	mpiexec -n $(NPROC) ./$(TARGET).out $(p) $(q)
