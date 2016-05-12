#ifndef Matrix_
#define Matrix_

#include "basic.h"
#include "block.h"

class Matrix
{
private:
	Block *matrix[BLOCK_N][BLOCK_N];
	int myRank();
	int myCommSize();
public:
    Matrix();
    ~Matrix();
    int load(char *file);
    int save(char *file);
    int send(MPI_Datatype* MY_MPI_BLOCK);
    Matrix& operator=(const Matrix& m);
    Matrix operator+(const Matrix& m) const;
    Matrix operator*(const Matrix& m) const;

};

#endif