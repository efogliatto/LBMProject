#ifndef BASICSOLVERINFO_H
#define BASICSOLVERINFO_H

#include <time.h>
#include <sys/time.h>
#include <scalars_C.h>

#define MPI_BUFF_SIZE 100


struct timeInfo {

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



struct latticeInfo {

    c_scalar size;
    c_scalar cs2;
    c_scalar c;
    unsigned int nlocal;
    int d;
    int Q;
    int** vel;
    int* reverse;
    c_scalar* omega;
    int principal[3][2];

    // Directional derivatives
    char* dd;
    
};

struct fieldsInfo {

    c_scalar** colMat;
    c_scalar** colMatA;
    c_scalar** colMatB;

    c_scalar** srcMat;
    c_scalar** srcMatA;
    c_scalar** srcMatB;
    
    c_scalar sigma;
    c_scalar D;
    c_scalar phi_A;
    c_scalar phi_B;
    c_scalar M_phi;
    c_scalar gx;
    c_scalar gy;
    c_scalar gz;
    c_scalar rho_A;
    c_scalar rho_B;
    c_scalar eta;
    c_scalar beta;
    c_scalar kappa;
    
};



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


    // Buffers

    // Scalars
    c_scalar* scalarSendBuff;
    c_scalar* scalarRecvBuff;
    int* sendScalarBlocks;
    int* recvScalarBlocks;

    c_scalar** ssbuf;
    c_scalar** srbuf;
    
};


struct solverInfo {

    struct timeInfo time;

    struct latticeInfo lattice;

    struct fieldsInfo fields;

    struct mpiInfo parallel;
};



#endif // BASICSOLVERINFO_H
