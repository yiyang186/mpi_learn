#include "matrix.h"

Matrix::Matrix() {
    matrix = (double*)malloc(sizeof(double) * LEN2);
}

Matrix::~Matrix() {
    free(matrix);
}

int Matrix::load(char *file, 
                 int my_rank, 
                 int comm_sz;
                 MPI_Datatype* blocktype
                 MPI_Comm comm) {
    int local_n = BLOCK_N2/comm_sz; 
    Block local_block[local_n];

    if(my_rank == 1) {
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
            fscanf(fp, "%lf", &matrix[(i*BLOCK_N+j)*BLOCK_LEN2 + \
                k*BLOCK_LEN+l]);
        }
        fclose(fp);

        
        MPI_Scatter(matrix, local_n, blocktype, \
                   local_block.block, local_n, blocktype,\
                   0, comm);
    } else {

    }
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
        for (int i = 0; i < BLOCK_N; i++)
            for (int j = 0; j < BLOCK_N; j++)
                matrix[i][j] = m.matrix[i][j];
    }
    return *this;
}

Matrix Matrix::operator+(const Matrix& m) const {
    Matrix c;
    for (int i = 0; i < BLOCK_N; i++)
        for (int j = 0; j < BLOCK_N; j++)
            *c.matrix[i][j] = *matrix[i][j] + *m.matrix[i][j];
    return c;
}

Matrix Matrix::operator*(const Matrix& m) const {
    Matrix c;
    for (int i = 0; i < BLOCK_N; i++)
        for (int j = 0; j < BLOCK_N; j++) {
            Block sum;
            for (int k = 0; k < BLOCK_N; k++) 
                sum += *matrix[i][k] * *m.matrix[k][j];
            *c.matrix[i][j] = sum;
        }
    return c;
}