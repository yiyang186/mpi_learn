#include "mympi.h"

void buildBlockMPIType(MPI_Datatype* mytype) {
    MPI_TYPE_CONTIGUOUS(BLOCK_LEN2, MPI_DOUBLE, mytype);
    MPI_Type_commit(ctype);
}  

void buildMatrixMPIType(MPI_Datatype* mytype, 
                        MPI_Datatype* blocktype,
                        Matrix& m) {
    int blockcounts[BLOCK_N2];
    MPI_Datatype oldtypes[BLOCK_N2];
    MPI_Aint offsets[BLOCK_N2], lastadd, nowadd;
    MPI_Get_address(&m.matrix[0][0].block[0], &lastadd);
     
    for(int i = 0; i < BLOCK_N2; i++) {
        blockcounts[i] = BLOCK_LEN2;
        oldtypes[i] = blocktype;
        int i_i = i / BLOCK_N;
        int i_j = i % BLOCK_N;
        MPI_Get_address(&m.matrix[i_i][i_j]->block[0], &nowadd);
        offsets[i] = nowadd - lastadd;
        lastadd = nowadd;
    }

    MPI_Type_struct(BLOCK_N2, blockcounts, offsets, oldtypes, mytype);
    MPI_Type_commit(newtype);
}

void matrixAdd(Block* local_block, 
               Block* total_block, 
               int* len,
               MPI_Datatype* mytype) {
    *sum += *b;
}

