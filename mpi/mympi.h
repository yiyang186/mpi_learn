#ifndef _Mympi
#define _Mympi

#include "basic.h"
#include "block.h"
#include "matrix.h"

void buildBlockMPIType(MPI_Datatype* mytype);
void matrixAdd(Block* local_block, Block* total_block, int* len,\
	MPI_Datatype* mytype);

#endif