#include "matrix.h"

Matrix::Matrix() {
    for(int i = 0; i < BLOCK_N; i++)
        for(int j = 0; j < BLOCK_N; j++)
            matrix[i][j] = new Block();
}

Matrix::~Matrix() {
    for(int i = 0; i < BLOCK_N; i++)
        for(int j = 0; j < BLOCK_N; j++)
            delete matrix[i][j];
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

    for(int i = 0; i < BLOCK_N; i++)
        for(int j = 0; j < BLOCK_N; j++) {
            matrix[i][j]->block[BLOCK_LEN2] = i;
            matrix[i][j]->block[BLOCK_LEN2+1] = j;
        }

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

int Matrix::myRank() {
    int my_rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
    return my_rank;
}

int Matrix::myCommSize() {
    int comm_sz;
    MPI_Comm_size(MPI_COMM_WORLD, &comm_sz);
    return comm_sz;
}

Matrix Matrix::operator*(const Matrix& m) const {
    
    MPI_Datatype MY_MPI_BLOCK;
    buildBlockMPIType(&MY_MPI_BLOCK);
    int my_rank = myRank();
    int comm_sz = myCommSize();
    int blockPairInNode = BLOCK_N/comm_sz + ((my_rank <= BLOCK_N%comm_sz)?1:0);
    Block *a, *b, *c;

    // 拆分发送/接收
    int tag = 0;
    if(my_rank == 0) {
        for(int i = 0; i < BLOCK_N; i++)
            for(int j = 0; j < BLOCK_N; j++) {
                int destA = i % (comm_sz - 1) + 1;
                int destB = j % (comm_sz - 1) + 1;

                MPI_Send(matrix[i][j]->block, BLOCK_LEN2_EX, MPI_DOUBLE, \
                    dest, tag++, MPI_COMM_WORLD);
                MPI_Send(m.matrix[j][i]->block, BLOCK_LEN2_EX, MPI_DOUBLE, \
                    dest, tag++, MPI_COMM_WORLD);
            }
    } else {
        a = new Block();
        b = new Block();
        c = new Block();

        for(int i = 0; i < blockPairInNode; i++) {
            MPI_Recv(a->block, BLOCK_LEN2_EX, MPI_DOUBLE, 0, i*2, \
                MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            MPI_Recv(b->block, BLOCK_LEN2_EX, MPI_DOUBLE, 0, i*2+1, \
                MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            *c = (*a) * (*b);

            MPI_Send(c->block, BLOCK_LEN2_EX, MPI_DOUBLE, 0, , MPI_COMM_WORLD);
        }

        
    }

    // 块相乘
    // 
    // 结果回传/接收
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