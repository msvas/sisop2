#ifndef IO_H_ 
#define IO_H_

#include <stdio.h>
#include <stdlib.h>
#include "matrix.h"

void readHeader(FILE *matrixFile, int *totalLines, int *totalCols);
MATRIX readMatrix(FILE *matrixFile, int totalLines, int totalCols);
MATRIX readFile (char fileName[10]);

#endif