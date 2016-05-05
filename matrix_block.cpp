// 将一个1024行8列（1024*8）的矩阵分成128块，将每块分别存进一个二维数组
#include <stdio.h>
#include <stdlib.h>
const int block = 128;

int main()
{
    int arr[1024][8];
    int (**parr)[8];
    int i, j, k;
    int perblock = 1024 / block;
    int count = 0;

    parr = (int (**)[8])malloc(sizeof(int(**)[8]) * 128);

    for (i = 0; i < 1024; i++)
        for (j = 0; j < 8; j++)
            arr[i][j] = count++;

    for (i = 0; i < block; i++)
    {
        parr[i] = (int (*)[8])malloc(sizeof(int) * perblock * 8);
        for (j = 0; j < perblock; j++)
        {
            for (k = 0; k < 8; k++)
            {
                parr[i][j][k] = arr[i*8+j][k];
            }
        }
    }


    for (i = 0; i < 1024; i++)
        for (j = 0; j < 8; j++)
            printf("%d\n", arr[i][j]);

    printf("=================\n");

    for (i = 0; i < block; i++)
    {
        for (j = 0; j < perblock; j++)
        {
            for (k = 0; k < 8; k++)
                printf("i=%d,j=%d,k=%d,%d\n", i, j, k, parr[i][j][k]);
        }
    }

    return 0; 
}