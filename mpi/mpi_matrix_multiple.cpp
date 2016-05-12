#include "matrix.h"

int main(void) {
    MPI_Init(NULL, NULL);

    char fileA[] = "A.txt";
    char fileB[] = "B.txt";
    char fileC[] = "C.txt";

    Matrix A, B, C;
    
    A.load(fileA);
    B.load(fileA);

    C = A * B;  // 重载了*方法，其中做了mpi并行计算
    C.save(fileC); 

    MPI_Finalize();
    return 0;
}


