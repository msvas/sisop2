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
    MATRIX matrixResult;
    
    manageMQ();
    matrixResult = multAll(matrixOne, matrixTwo, n);
    
    printMatrix(matrixResult);
}

MATRIX multAll(MATRIX matrixOne, MATRIX matrixTwo, int n)
{
    int i, j, k;
    int procInterval, linesPerProc;
    MATRIX matrixResult;
    pid_t pid[n];
    BUFFER postBox[n];
    
    matrixResult.elements = malloc(matrixOne.lines * matrixTwo.cols * sizeof(int));
    matrixResult.lines = matrixOne.lines;
    matrixResult.cols = matrixTwo.cols;
    linesPerProc = ceil(matrixOne.lines / n);
    
    //printf("%i, %i\n", matrixOne.lines, n);
    
    for(k = 0; k < n; k++)
        pid[k] = 1;
    
    if (!linesPerProc)
        linesPerProc = 1;
        
    procInterval = -linesPerProc;
    k = 0;
    while((k < n) && pid[k] != 0)
    {
        k++;
        procInterval += linesPerProc;
        pid[k] = fork();
    }
    
    if(pid[k] == 0)
    {
        for(j = procInterval; (j < (procInterval + linesPerProc)) && (j < matrixOne.lines); j++)
        {
            (postBox[n]).lineResult = malloc(matrixTwo.cols * sizeof(int));
            (postBox[n]).mtype = j;
            multOneLine(j, matrixOne, matrixTwo, postBox[n]);
            sendMessage(postBox[n]);
        }
        exit(0);
    }
    else
        for(k = 0; k < n; k++)
            waitpid(pid[n], 0, 0);
    
    for(i = 0; i < matrixResult.lines; i++)
    {
        matrixResult.elements[(i * matrixResult.cols)] = rcvMessage(i);
    }
    
    return matrixResult;
}    

void multOneLine(int line, MATRIX matrixOne, MATRIX matrixTwo, BUFFER postBox)
{
    int j, sumResult;
    
    for(j = 0; j < matrixTwo.cols; j++)
    {
        sumResult = multOneLineOneCol(line, j, matrixOne, matrixTwo);
        postBox.lineResult[j] = sumResult;
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