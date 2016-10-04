
#ifndef BASICSOLVERINFO_H
#define BASICSOLVERINFO_H

#include <time.h>
#include <sys/time.h>
#include <scalars_C.h>

#define MPI_BUFF_SIZE 100


struct li_timeInfo {

    // Simulation parameters

    // Start time
    unsigned int start;

    // End time
    unsigned int end;

    // Current time
    unsigned int current;

    
    // Time step
    c_scalar tstep;

    // Write interval (write every writeInterval steps)
    unsigned int writeInterval;

    // Start time (time measurement)
    time_t st;
    struct timeval stt;

    // Time step (inside write intrval)
    unsigned int stp;
    
    
};



struct li_latticeInfo {

    c_scalar size;
    c_scalar cs2;
    c_scalar c;
    unsigned int nlocal;
    int d;
    int Q;
    int** vel;
    int* reverse;
    c_scalar* omega;
    c_scalar* weights;    
    int principal[3][2];
    
};

struct li_fieldsInfo {

    // Model matrix (inverse)
    c_scalar** invM;

    // Collision matrix
    c_scalar** Lambda;

    // Carnahan - Starling coefficients
    c_scalar _a;
    c_scalar _b;
    c_scalar _R;
    c_scalar _T;
    c_scalar _G;
    c_scalar _c;

    
    
};



struct li_mpiInfo {

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


    // Buffers

    // Scalars
    c_scalar* scalarSendBuff;
    c_scalar* scalarRecvBuff;
    int* sendScalarBlocks;
    int* recvScalarBlocks;

    c_scalar** ssbuf;
    c_scalar** srbuf;
    
};


struct liModelInfo {

    struct li_timeInfo time;

    struct li_latticeInfo lattice;

    struct li_fieldsInfo fields;

    struct li_mpiInfo parallel;
};



#endif // BASICSOLVERINFO_H
