#ifndef _Mympi
#define _Mympi

#include "basic.h"
#include "block.h"
#include "matrix.h"

void buildBlockMPIType(MPI_Datatype* mytype);
void buildMatrixMPIType(MPI_Datatype* mytype);

#endif