TARGET = bitonic
NPROC=$(shell echo 2\^$(p) | bc)

all:
	mpicc $(TARGET).c $(TARGET)_merge.c -std=c99 -O3 -lm -o $(TARGET).out
run:
	mpiexec -n $(NPROC) ./$(TARGET).out $(p) $(q)
