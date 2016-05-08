#ifndef Matrix_
#define Matrix_

#include "basic.h"
#include "block.h" 

class Matrix
{
public:
	double *matrix;
    Matrix();
    ~Matrix();
    int load(char *file, int my_rank, MPI_Datatype* MPI_MATRIX);
    int save(char *file);
    Matrix& operator=(const Matrix& m);
    Matrix operator+(const Matrix& m) const;
    Matrix operator*(const Matrix& m) const;

};

#endif