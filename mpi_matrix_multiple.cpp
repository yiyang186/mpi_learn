#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

const int LEN = 6000;
const int LEN2 = 36000000;
const int BLOCK_LEN = 500;
const int BLOCK_LEN2 = 250000;
const int BLOCK_N = 12;

class Matrix
{
    double *matrix[BLOCK_N][BLOCK_N];
public:
    Matrix();
    ~Matrix();
    int loadMatrix(char *file);
    int saveMatrix(char *file);
    int scatter(double** block, int num, int my_rank, MPI_Comm comm);
};

int main(void) {
    char  greeting[MAX_STRING];
    int   comm_sz;
    int   my_rank;


    MPI_Init(NULL, NULL);
    MPI_Comm_size(MPI_COMM_WORLD, &comm_sz);
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);

    if(my_rank == 0) {

        char fileA[] = "A.txt";
        char fileB[] = "B.txt";
        Matrix A, B;
        A.loadMatrix(fileA);
        B.loadMatrix(fileB);

        printf("Greetings from process %d of %d!\n", my_rank, comm_sz);
        for (int q = 1; q < comm_sz; q++) {
            MPI_Recv(greeting, MAX_STRING, MPI_CHAR, q, 0, MPI_COMM_WORLD,\
                MPI_STATUS_IGNORE);
            printf("%s\n", greeting);
        }
    } else {
        sprintf(greeting, "Greetings from process %d of %d!", my_rank, comm_sz);
        MPI_Send(greeting, strlen(greeting)+1, MPI_CHAR, 0, 0, MPI_COMM_WORLD);
    }

    MPI_Finalize();

    for(int i = 0; i < BLOCK_N; i++)
        for(int j = 0; j < BLOCK_N; j++)
            free(matrix[i][j]);

    return 0;
}

Matrix::Matrix() {
    for(int i = 0; i < BLOCK_N; i++)
        for(int j = 0; j < BLOCK_N; j++)
            matrix[i][j] = (double **)malloc(sizeof(double) * BLOCK_LEN2);
}

Matrix::~Matrix() {
    for(int i = 0; i < BLOCK_N; i++)
        for(int j = 0; j < BLOCK_N; j++)
            free(matrix[i][j]);
}

int Matrix::loadMatrix(char *file) {
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
        fscanf(fp, "%lf", matrix[i][j] + k * BLOCK_LEN + l);
    }
    fclose(fp);
    return 0;
}

int Matrix::saveMatrix(char *file) {
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
        fprintf(fp, "%f\n", *(matrix[i][j] + k * BLOCK_LEN + l));
    };

    fclose(fp);
    return 0;
}