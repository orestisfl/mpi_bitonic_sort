TARGET = bitonic
NPROC=$(shell echo 2\^$(p) | bc)

all:
	mpicc -O3 -std=c99 $(TARGET).c $(TARGET)_merge.c -o $(TARGET).out
run:
	mpiexec -n $(NPROC) ./$(TARGET).out $(p) $(q)
