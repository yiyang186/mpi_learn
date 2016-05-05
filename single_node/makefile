CC = g++
CFLAGS = -Wall
OUT_NAME = matrixmultiple
objects = mpi_matrix_multiple_test.o block.o matrix.o

$(OUT_NAME): $(objects)
	$(CC) -o $@ $(CFLAGS) $^

$(objects): %.o: %.cpp
	$(CC) $(CFLAGS) $^ -o $@

clean:
	rm $(OUT_NAME) *.o