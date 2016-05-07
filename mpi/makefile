CC = g++
CFLAGS = -Wall
OUT_NAME = matrixmultiple
objects = block.o matrix.o mpi_matrix_multiple_test.o 

run: $(OUT_NAME)
	$(OUT_NAME)

$(OUT_NAME): $(objects)
	$(CC) $(CFLAGS) $^ -o $@

$(objects): %.o: %.cpp
	$(CC) $(CFLAGS) -c $^ -o $@

clean:
	rm $(OUT_NAME) *.o