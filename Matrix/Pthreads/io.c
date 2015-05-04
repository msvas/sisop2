#include "io.h"
#include "matrix.h"

int main (int argc, char *argv[])
{
    MATRIX matrixOne, matrixTwo, matrixResult;
    int intArg;
    
    intArg = atoi(argv[argc-1]);
    
    if(intArg > 0)
    {
        matrixOne = readFile("in1.txt");
        matrixTwo = readFile("in2.txt");

        matrixResult = multiplyMatrixes(matrixOne, matrixTwo, intArg);
        writeFile(matrixResult);
    }
    else
    {
        randomMatrix("in1.txt", 5000, 5000);
	randomMatrix("in2.txt", 5000, 5000);
    }
    
    printf("Elapsed time: %f\n", (float)clock() / CLOCKS_PER_SEC);
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

int writeFile(MATRIX matrix)
{
    FILE *matrixFile;
    int i, j;
    
    matrixFile = fopen("out.txt", "w");
    fprintf(matrixFile, "LINHAS = %i\n", matrix.lines);
    fprintf(matrixFile, "COLUNAS = %i\n", matrix.cols);
    
    for(i = 0; i <  matrix.lines; i++)
    {
        for(j = 0; j <  matrix.cols; j++)
        {
            if(j == (matrix.cols - 1))
                fprintf(matrixFile, "%i\n", matrix.elements[(i * matrix.cols) + j]);
            else
                fprintf(matrixFile, "%i ", matrix.elements[(i * matrix.cols) + j]);
        }
    }
    
    //printMatrix(matrix);
    
    fclose(matrixFile);
}

void randomMatrix (char fileName[10], int lines, int cols)
{
    FILE *matrixFile;
    int i, j;
    
    matrixFile = fopen(fileName, "w");
    fprintf(matrixFile, "LINHAS = %i\n", lines);
    fprintf(matrixFile, "COLUNAS = %i\n", cols);
    
    for(i = 0; i <  lines; i++)
    {
        for(j = 0; j <  cols; j++)
        {
            if(j == (cols - 1))
                fprintf(matrixFile, "%i\n", rand() % 1000);
            else
                fprintf(matrixFile, "%i ", rand() % 1000);
        }
    }
    
    //printMatrix(matrix);
    
    fclose(matrixFile);
}
