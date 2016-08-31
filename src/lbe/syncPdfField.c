#include <syncPdfField.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

/* #define MPI_BUFF_SIZE 500 */

void syncPdfField( struct solverInfo* info, double** fld, int sz ){

    unsigned int i, j, k, pid;
    
    MPI_Barrier(MPI_COMM_WORLD);

    // Allocate buffers
    double sendBuff[MPI_BUFF_SIZE];
    double recvBuff[MPI_BUFF_SIZE];

    
    
    // Send information. Divide by blocks

    for( k = 0 ; k < sz ; k++ ) {

	
	// Move over send ghosts
	for( i = 0 ; i < info->parallel.nSendGhosts ; i++ ) {

	    // Number of blocks
	    const int buffBlocks = (int)floor( info->parallel.sendGhostIds[i][1] / MPI_BUFF_SIZE ) + 1;
	
	    unsigned int bid;
	    for( bid = 0 ; bid < buffBlocks ; bid++ ) {
	
	    	// Block positions in sendGhostIds
	    	unsigned int min, max;
	    	min = MPI_BUFF_SIZE * bid;
	    	max = MPI_BUFF_SIZE * (bid + 1);

	    	if(max > info->parallel.sendGhostIds[i][1] ) { max = info->parallel.sendGhostIds[i][1]; }

	    
	    	// Move over blocks
	    	unsigned int m = 0;
	    	for( j = min ; j < max ; j++ ) {
	    
	    	    sendBuff[m] = fld[ info->parallel.sendGhostIds[i][j+2] ][k];
	    	    m++;

	    	}

	    	// Send data
	    	MPI_Send (sendBuff, MPI_BUFF_SIZE, MPI_DOUBLE, info->parallel.sendGhostIds[i][0], (bid + 1) * (k+1), MPI_COMM_WORLD);

	    }

	}
	
	
    }


    /* MPI_Barrier(MPI_COMM_WORLD); */

    
    // Receive information. Divide by blocks

    for( k = 0 ; k < sz ; k++ ) {

    	// Move over recv ghosts
    	for( i = 0 ; i < info->parallel.nRecvGhosts ; i++ ) {

    	    // Number of blocks
    	    const int buffBlocks = (int)floor( info->parallel.sendGhostIds[i][1] / MPI_BUFF_SIZE ) + 1;
	
    	    unsigned int bid;
    	    for( bid = 0 ; bid < buffBlocks ; bid++ ) {

    		// Block positions in recvGhostIds
    		unsigned int min, max;
    		min = MPI_BUFF_SIZE * bid;
    		max = MPI_BUFF_SIZE * (bid + 1);

    		if(max > info->parallel.recvGhostIds[i][1] ) { max = info->parallel.recvGhostIds[i][1]; }

    		// Receive data
    		MPI_Status status;
    		MPI_Recv (recvBuff, MPI_BUFF_SIZE, MPI_DOUBLE, info->parallel.recvGhostIds[i][0], (bid + 1) * (k+1), MPI_COMM_WORLD, &status);


    		// Update field
    		unsigned int m = 0;
    		for( j = min ; j < max ; j++ ) {

    		    fld[ info->lattice.nlocal + info->parallel.recvGhostIds[i][j+2] ][k] = recvBuff[m];
    		    m++;

    		}

	    
    	    }
	    
    	}

    }
    
    MPI_Barrier(MPI_COMM_WORLD);


    
}




    /* // Send information */

    /* // Move over send ghosts */
    /* for( i = 0 ; i < info->parallel.nSendGhosts ; i++ ) { */

    /* 	// Number of blocks */
    /* 	const int buffBlocks = (int)ceil( info->parallel.sendGhostIds[i][1] * sz / MPI_BUFF_SIZE ); */

    /* 	unsigned int bid; */
    /* 	for( bid = 0 ; bid < buffBlocks ; bid++ ) { */
	
	    // Create buffer and copy data
	    /* double* buf = (double*)malloc( info->parallel.sendGhostIds[i][1] * sz * sizeof(double) ); */
	    /* double buf[MPI_BUFF_SIZE]; */

	    /* for( j = 0 ; j < info->parallel.sendGhostIds[i][1] ; j++ ) { */

	    /* 	for( k = 0 ; k < sz ; k++ ) { */
	    
	    /* 	    buf[j*sz + k] = fld[ info->parallel.sendGhostIds[i][j+2] ][k]; */
	    /* 	    /\* if(info->parallel.pid == 1) {printf("%f\n", buf[j*sz + k]);} *\/ */

	    /* 	} */

	    /* } */

	    /* // Send data */
	    /* MPI_Send (buf, info->parallel.sendGhostIds[i][1] * sz, MPI_DOUBLE, info->parallel.sendGhostIds[i][0], info->parallel.pid, MPI_COMM_WORLD); */

    /* 	} */
	
    /* } */


    /* MPI_Barrier(MPI_COMM_WORLD); */

    
    /* // Receive information */

    /* // Move over recv ghosts */
    /* for( i = 0 ; i < info->parallel.nRecvGhosts ; i++ ) { */

    /* 	// Create buffer and copy data */
    /* 	double* buf = (double*)malloc( info->parallel.recvGhostIds[i][1] * sz * sizeof(double) ); */

    /* 	// Receive data */
    /* 	MPI_Status status; */
    /* 	MPI_Recv (buf, info->parallel.recvGhostIds[i][1] * sz, MPI_DOUBLE, info->parallel.recvGhostIds[i][0], info->parallel.recvGhostIds[i][0], MPI_COMM_WORLD, &status); */


    /* 	// Update field */
    /* 	for( j = 0 ; j < info->parallel.recvGhostIds[i][1] ; j++ ) { */

    /* 	    for( k = 0 ; k < sz ; k++ ) { */
		
    /* 		fld[ info->lattice.nlocal + info->parallel.recvGhostIds[i][j+2] ][k] = buf[j*sz + k]; */

    /* 	    } */

    /* 	} */

	    
    /* } */


    /* MPI_Barrier(MPI_COMM_WORLD); */
    
