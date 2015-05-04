#ifndef IO_H_ 
#define IO_H_

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "matrix.h"
#include "communication.h"

void readHeader(FILE *matrixFile, int *totalLines, int *totalCols);
MATRIX readMatrix(FILE *matrixFile, int totalLines, int totalCols);
MATRIX readFile (char fileName[10]);
int writeFile(MATRIX matrix);
void randomMatrix (char fileName[10], int lines, int cols);

#endif
