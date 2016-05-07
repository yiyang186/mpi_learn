#include "mympi.h"

void buildBlockMPIType(MPI_Datatype* mytype) {  
    MPI_TYPE_CONTIGUOUS(BLOCK_LEN2, MPI_DOUBLE, newtype);
    MPI_Type_commit(ctype);  
}  

void buildMatrixMPIType(MPI_Datatype* mytype) {
    int blockcounts[2];  
    MPI_Datatype oldtypes[2];  
    MPI_Aint offsets[2];  
  
    blockcounts[0]=1;  
    blockcounts[1]=256;  
  
    offsets[0]=0;  
    offsets[1]=sizeof(double);  
  
    oldtypes[0]=MPI_DOUBLE;  
    oldtypes[1]=MPI_CHAR;  
  
    MPI_Type_struct(2,blockcounts,offsets,oldtypes,ctype);
    MPI_Type_commit(ctype);  
}

