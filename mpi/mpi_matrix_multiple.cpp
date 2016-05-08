#include "matrix.h"

void buildBlockMPIType(MPI_Datatype* mytype);

int main(void) {
    int   comm_sz;
    int   my_rank;

    MPI_Init(NULL, NULL);
    MPI_Comm_size(MPI_COMM_WORLD, &comm_sz);
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);

    char fileA[] = "A.txt";
    char fileB[] = "B.txt";
    char fileC[] = "C.txt";

    Matrix A, B, C;
    MPI_Datatype MY_MPI_BLOCK;
    buildBlockMPIType(MY_MPI_BLOCK);

    MPI_Datatype MPI_MATRIX_A, MPI_MATRIX_B, MPI_MATRIX_C;
    buildMatrixMPIType(MPI_MATRIX_A, MY_MPI_BLOCK, A);
    buildMatrixMPIType(MPI_MATRIX_B, MY_MPI_BLOCK, B);
    buildMatrixMPIType(MPI_MATRIX_C, MY_MPI_BLOCK, C);

    MPI_Op MY_MPI_BLOCK_SUM;  
    MPI_Op_create((MPI_User_function*)matrixAdd, true, &MY_MPI_BLOCK_SUM);

    A.load(fileA);
    B.load(fileB);

    MPI_Scatter()

    C = A * B;
    C.save(fileC); 

    MPI_Finalize();

    return 0;
}


