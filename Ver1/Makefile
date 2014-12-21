TARGET = bitonic
NPROC=$(shell echo 2\^$(p) | bc)

all:
	mpicc -O3 $(TARGET).c -o $(TARGET)
run:
	mpiexec -n $(NPROC) ./$(TARGET) $(p) $(q)
