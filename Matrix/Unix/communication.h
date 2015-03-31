#ifndef COMMUNICATION_H_ 
#define COMMUNICATION_H_

#include <stdlib.h>
#include <stdio.h>
#include <sys/shm.h>
#include <sys/stat.h> 

int manageSM(int smSize);
int *smAttach(int line, int col, int totalCol, int *memAddr);
void dettDestroy(int *smMatrix);

#endif