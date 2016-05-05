#include "block.h"

Block::Block() {
    block = new double[BLOCK_LEN2]();
}

Block::~Block() {
    delete[] block;
}

Block& Block::operator=(const Block& b) {
    if(this != &b) {}
    for (int i = 0; i < BLOCK_LEN2; i++)
        block[i] = b.block[i];
    return *this;
}

Block Block::operator+(const Block& b) const {
    Block c;
    for (int i = 0; i < BLOCK_LEN2; i++)
        c.block[i] = block[i] + b.block[i];
    return c;
}

Block Block::operator*(const Block& b) const {
    Block c;
    for (int i = 0; i < BLOCK_LEN; i++)
        for (int j = 0; j <BLOCK_LEN; j++) {
            double sum = 0;
            for (int k = 0; k < BLOCK_LEN; k++) 
                sum += block[i * BLOCK_LEN + k] * b.block[k * BLOCK_LEN + j];
            c.block[i * BLOCK_LEN + j] = sum; 
        }
    return c;
}

Block& Block::operator+=(const Block& b) {
    for (int i = 0; i < BLOCK_LEN2; i++)
        block[i] += b.block[i];
    return *this;
}