#ifndef Block_
#define Block_

#include "basic.h"

class Block
{
	friend class Matrix;
private:
    double* block;
public:
    Block();
    ~Block();
    Block& operator=(const Block& m);
    Block operator+(const Block& m) const;
    Block operator*(const Block& m) const;
    Block& operator+=(const Block& m);
};

#endif