#include "matrix.h"

Matrix::Matrix() {
    for(int i = 0; i < BLOCK_N; i++)
        for(int j = 0; j < BLOCK_N; j++)
            matrix[i][j] = new Block();
}

Matrix::~Matrix() {
    for(int i = 0; i < BLOCK_N; i++)
        for(int j = 0; j < BLOCK_N; j++)
            delete[] matrix[i][j];
}

int Matrix::load(char *file) {
    FILE* fp = fopen(file,"r");
    if(fp == NULL)
        return 1;

    for(int n = 0; n < LEN2; n++) {
        int n_i = n / LEN;
        int n_j = n % LEN;
        int i = n_i / BLOCK_LEN;
        int j = n_j / BLOCK_LEN;
        int k = n_i % BLOCK_LEN;
        int l = n_j % BLOCK_LEN;
        fscanf(fp, "%lf", &(matrix[i][j]->block[k * BLOCK_LEN + l]));
    }
    fclose(fp);
    return 0;
}

int Matrix::save(char *file) {
    FILE* fp = fopen(file,"w");
     
    if(fp==NULL)
        return 1;
 
    for(int n = 0; n < LEN2; n++){
        int n_i = n / LEN;
        int n_j = n % LEN;
        int i = n_i / BLOCK_LEN;
        int j = n_j / BLOCK_LEN;
        int k = n_i % BLOCK_LEN;
        int l = n_j % BLOCK_LEN;
        fprintf(fp, "%f\n", matrix[i][j]->block[k * BLOCK_LEN + l]);
    };

    fclose(fp);
    return 0;
}

Matrix& Matrix::operator=(const Matrix& m) {
    if (this != &m) {
        for (int i = 0; i < LEN; i++)
            for (int j = 0; j < LEN; j++)
                matrix[i][j] = m.matrix[i][j];
    }
    return *this;
}

Matrix Matrix::operator+(const Matrix& m) const {
    Matrix c;
    for (int i = 0; i < LEN; i++)
        for (int j = 0; j < LEN; j++)
            *c.matrix[i][j] = *matrix[i][j] + *m.matrix[i][j];
    return c;
}

Matrix Matrix::operator*(const Matrix& m) const {
    Matrix c;
    for (int i = 0; i < LEN; i++)
        for (int j = 0; j < LEN; j++) {
            Block sum;
            for (int k = 0; k < BLOCK_LEN; k++) 
                sum += *matrix[i][k] * *m.matrix[k][j];
            *c.matrix[i][j] = sum;
        }
    return c;
}