#include "matrix.h"
#include "io.h"
#include "communication.h"

void printMatrix(MATRIX matrix)
{
    int i, j;
    for(i = 0; i < matrix.lines; i++)
    {
        for(j = 0; j < matrix.cols; j++)
        {
            printf("%i ", matrix.elements[(i * matrix.cols) + j]);
        }
        printf("\n");
    }
}

MATRIX multiplyMatrixes(MATRIX matrixOne, MATRIX matrixTwo, int n)
{
    MATRIX *matrixResult;
    int i;
    
    *(matrixResult->elements) = malloc(matrixOne.lines * matrixTwo.cols * sizeof(int));
    matrixResult->lines = matrixOne.lines;
    matrixResult->cols = matrixTwo.cols;
    
    manageSM(matrixOne.lines * matrixTwo.cols * sizeof(int));    
    multAll(matrixOne, matrixTwo, matrixResult);
    
    printMatrix(*matrixResult);
    
    return *matrixResult;
}

void multAll(MATRIX matrixOne, MATRIX matrixTwo, MATRIX  *matrixResult, int n)
{
    int i, linesPerProc;
    
    linesPerProc = ceil(matrixOne.lines / n);
    
    for(i = 0; i < 
    
        multOneLine(i, matrixOne, matrixTwo, matrixResult);
    }
}

void multOneLine(int line, MATRIX matrixOne, MATRIX matrixTwo, MATRIX *matrixResult)
{
    int i, j, sumResult;
    
    i = (line * matrixResult->cols);
    for(j = 0; j < matrixTwo.cols; j++)
    {
        sumResult = multOneLineOneCol(line, j, matrixOne, matrixTwo);
        matrixResult->elements[i + j] = sumResult;
    }
}

int multOneLineOneCol(int line, int col, MATRIX matrixOne, MATRIX matrixTwo)
{
    int i, lineCol, finalSum = 0;
    
    i = line * matrixOne.lines;
    for(lineCol = 0; lineCol < matrixTwo.cols; lineCol++)
    {
        finalSum = finalSum + (matrixOne.elements[i + lineCol] * matrixTwo.elements[(lineCol * matrixTwo.cols) + col]);
    }
    
    return finalSum;
}