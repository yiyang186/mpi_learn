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

    MPI_Datatype MY_MPI_BLOCK;
    buildBlockMPIType(MPI_Datatype* MY_MPI_BLOCK);

    MPI_Datatype MY_MPI_MATRIX;
    buildMatrixMPIType(MPI_Datatype* MY_MPI_MATRIX);

    Matrix A, B, C;
    A.load(fileA);
    B.load(fileB);

    MPI_Scatter()

    C = A * B;
    C.save(fileC);

    MPI_Op MY_MPI_SUM;  

  
    MPI_Op_create((MPI_User_function*)myProd,1,&MY_MPI_SUM);  
    buildBlockMPIType(&MY_MPI_BLOCK);  
    MPI_Reduce(dist,result,20,MY_MPI_BLOCK,MY_MPI_SUM,MASTER,MPI_COMM_WORLD); 

    MPI_Finalize();

    return 0;
}


