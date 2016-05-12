#ifndef Block_
#define Block_

#include "basic.h"

class Block
{
	friend class Matrix;
public:
	double* block;
    Block();
    ~Block();
    Block& receive();
    Block& operator=(const Block& m);
    Block operator+(const Block& m) const;
    Block operator*(const Block& m) const;
    Block& operator+=(const Block& m);
};

#endif