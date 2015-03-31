#ifndef MATRIX_H_ 
#define MATRIX_H_

#include <stdio.h>
#include <stdlib.h>

typedef struct Matrix
{
    int *elements;
    int lines;
    int cols;
} MATRIX;  


void printMatrix(MATRIX matrix);
MATRIX multiplyMatrixes(MATRIX matrixOne, MATRIX matrixTwo);
int multOneLineOneCol(int line, int col, MATRIX matrixOne, MATRIX matrixTwo);
void multOneLine(int line, MATRIX matrixOne, MATRIX matrixTwo, MATRIX *matrixResult);
void multAll(MATRIX matrixOne, MATRIX matrixTwo, MATRIX *matrixResult);

#endif