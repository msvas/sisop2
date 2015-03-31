#include "communication.h"

int smid;

int manageSM(int smSize)
{
    smid = shmget(IPC_PRIVATE, smSize, S_IRUSR | S_IWUSR);

    return smid;
}

int *smAttach(int line, int col, int totalCol, int *memAddr)
{
    int memPos;
    int *smMatrix;
    
    memPos = ((line * totalCol) + col) * sizeof(int);
    smMatrix = (int *) shmat(smid, (memAddr + memPos), 0);
    
    return smMatrix;
}

void dettDestroy(int *smMatrix)
{
    shmdt(smMatrix);
    shmctl(smid, IPC_RMID, NULL); 
}
