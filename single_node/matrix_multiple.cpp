#include "matrix.h"

int main() {

    char fileA[] = "A.txt";
    char fileB[] = "B.txt";
    char fileC[] = "C.txt";
    char fileA_test[] = "test_A.txt";
    char fileB_test[] = "test_B.txt";

    Matrix A, B, C;
    A.load(fileA);
    B.load(fileB);
    A.save(fileA_test);
    B.save(fileB_test);

    C = A * B;
    C.save(fileC);
    return 0;
}

