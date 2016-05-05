

class Block
{
    double* block;
public:
    Block();
    ~Block();
    Block operator+(const Matrix& m) const;
    Block operator*(const Matrix& m) const;
};