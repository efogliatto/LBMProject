#ifndef MPIINFO_H
#define MPIINFO_H

#include <scalars_C.h>

#define MPI_BUFF_SIZE 100

struct mpiInfo {

    // Process id
    unsigned int pid;

    // Total number of processes
    unsigned int worldSize;    

    // Total number of ghosts
    unsigned int nghosts;

    // Send ghosts
    unsigned int nSendGhosts;

    // Recv ghosts
    unsigned int nRecvGhosts;

    // Send ghost ids
    unsigned int** sendGhostIds;

    // Recv ghost ids. Id = nlocal + id
    unsigned int** recvGhostIds;

    // Local elements
    unsigned int nlocal;


    // Buffers

    // Scalars
    c_scalar* scalarSendBuff;
    c_scalar* scalarRecvBuff;
    int* sendScalarBlocks;
    int* recvScalarBlocks;

    c_scalar** ssbuf;
    c_scalar** srbuf;
    
};

#endif // MPIINFO_H
