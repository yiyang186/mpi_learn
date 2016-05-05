#ifndef Matrix_
#define Matrix_

#include "basic.h"
#include "block.h" 

class Matrix
{
private:
    Block *matrix[LEN][LEN];
public:
    Matrix();
    ~Matrix();
    int load(char *file);
    int save(char *file);
    Matrix& operator=(const Matrix& m);
    Matrix operator+(const Matrix& m) const;
    Matrix operator*(const Matrix& m) const;
};

#endif