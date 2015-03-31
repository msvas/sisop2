#include "io.h"
#include "matrix.h"

int main (int argc, char *argv[])
{
    MATRIX matrixOne, matrixTwo;
    
    matrixOne = readFile("in1.txt");
    matrixTwo = readFile("in2.txt");
    
    multiplyMatrixes(matrixOne, matrixTwo, atoi(argv[argc-1]));
    return 0;
}

void readHeader(FILE *matrixFile, int *totalLines, int *totalCols)
{
    char charBuffer;
    char values[2][10];
    int i;
    
    for(i = 0; i < 2; i++)
    {
        do
            charBuffer = fgetc(matrixFile);
        while (charBuffer != '=');
        fgetc(matrixFile);

        fscanf(matrixFile, "%s", values[i]);
    }
    *totalLines = atoi(values[0]);
    *totalCols = atoi(values[1]);
}

MATRIX readMatrix(FILE *matrixFile, int totalLines, int totalCols)
{
    char strBuffer[10];
    int i, j;
    MATRIX matrix;
    
    matrix.elements = malloc(totalLines * totalCols * sizeof(int));
    
    matrix.lines = totalLines;
    matrix.cols = totalCols;
    
    for(i = 0; i < totalLines; i++)
    {
        for(j = 0; j < totalCols; j++)
        {
            fscanf(matrixFile, "%s", strBuffer);
            matrix.elements[(i * totalCols) + j] = atoi(strBuffer);
        }
    }
    
    return matrix;
}

MATRIX readFile (char fileName[10])
{
    FILE *matrixFile;
    int totalLines, totalCols;
    MATRIX matrix;
    
    matrixFile = fopen(fileName, "r");
    readHeader(matrixFile, &totalLines, &totalCols);
    matrix = readMatrix(matrixFile, totalLines, totalCols);
    
    //printMatrix(matrix);
    
    fclose(matrixFile);
    return matrix;
}