#ifndef MATRIX_H_ 
#define MATRIX_H_

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "communication.h"

typedef struct Matrix
{
    int *elements;
    int lines;
    int cols;
} MATRIX;  


void printMatrix(MATRIX matrix);
MATRIX multiplyMatrixes(MATRIX matrixOne, MATRIX matrixTwo, int n);
int multOneLineOneCol(int line, int col, MATRIX matrixOne, MATRIX matrixTwo);
void multOneLine(int line, MATRIX matrixOne, MATRIX matrixTwo, BUFFER *postBox);
MATRIX multAll(MATRIX matrixOne, MATRIX matrixTwo, int n);
int findN(int value);

#endif