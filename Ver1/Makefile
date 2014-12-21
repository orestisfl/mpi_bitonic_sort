TARGET = bitonic
NPROC = 4

all:
	mpicc -O3 $(TARGET).c -o $(TARGET)
run:
	mpiexec -n $(NPROC) ./$(TARGET) $(p) $(q)
