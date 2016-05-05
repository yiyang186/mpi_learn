#include <stdio.h>
#include <stdlib.h>

const int LEN = 60;
int main()
{
    double *matrix[2];
    for(int i = 0; i < 2; i++)
        matrix[i] = (double *)malloc(sizeof(double) * LEN);
    char file[2][6] = {"A.txt", "B.txt"};
    int h = 0;
    while(h < 2){
        FILE* fp1 = fopen(file[h],"r+");
         
        if(fp1==NULL)
            return 1;
     
        for(int i=0; i < LEN; i++)
            fscanf(fp1, "%lf", &matrix[h][i]);
        h++;
        fclose(fp1);
    }
    for(int i = 0; i < 2; i ++){
        for(int j = 0; j < LEN; j++)
            printf("%f ", matrix[i][j]);
        printf("\n");
    }
    for(int i = 0; i < 2; i++)
        free(matrix[i]);
    return 0;
}