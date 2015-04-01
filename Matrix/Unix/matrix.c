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

void multiplyMatrixes(MATRIX matrixOne, MATRIX matrixTwo, int n)
{
    
    manageSM(matrixOne.lines * matrixTwo.cols * sizeof(int));  
    multAll(matrixOne, matrixTwo, findN(n));
    
    //printMatrix(*matrixResult);
}

MATRIX multAll(MATRIX matrixOne, MATRIX matrixTwo, int nProcs)
{
    int i, j, k;
    MATRIX matrixResult;
    pid_t pid;
    
    matrixResult.elements = malloc(matrixOne.lines * matrixTwo.cols * sizeof(int));
    
    for(k = 0; k < nProcs; k++)
    {
        pid = fork();
    }
    
    //linesPerProc = ceil(matrixOne.lines / n);
    
    for(j = 0; j < matrixOne.lines; j++)
    {
        for(i = 0; i < n; i++)
        {
            //multOneLine(i, matrixOne, matrixTwo, matrixResult);
        }
    }
    
    return matrixResult;
}

void multOneLine(int line, MATRIX matrixOne, MATRIX matrixTwo)
{
    int i, j, sumResult;
    
    i = (line * matrixTwo.cols);
    for(j = 0; j < matrixTwo.cols; j++)
    {
        sumResult = multOneLineOneCol(line, j, matrixOne, matrixTwo);
        //matrixResult->elements[i + j] = sumResult;
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

int findN(int value)
{
    int i = 0;
    
    while(value != 1)
    {
        value = value / 2;
        i++;
    }
    return i;
}