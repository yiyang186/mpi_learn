#include <stdio.h>
#include <stdlib.h>

const int LEN2 = 144;

int main() {

    char file[2][6] = {"A.txt", "B.txt"};
    int h = 0;
    while(h < 2) {
        FILE *fp = fopen(file[h++], "w");  
        if (fp) { 
            srand((unsigned int)h);
            for (int i = 0; i < LEN; i++)
                fprintf(fp, "%d\n", rand());
        } else printf("I can not open it!\n");
        fclose(fp);
    }
    return 0;
}