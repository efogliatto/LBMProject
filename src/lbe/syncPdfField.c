#include <syncPdfField.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

/* #define MPI_BUFF_SIZE 500 */

void syncPdfField( struct solverInfo* info, double** fld, int sz ){


    MPI_Barrier(MPI_COMM_WORLD);

    
    // Send information. Divide by blocks and columns

    unsigned int k;
    for( k = 0 ; k < sz ; k++ ) {
    
	// Copy data to send buffer
    
	// Move over send ghosts
	unsigned int pid;
	for( pid = 0 ; pid < info->parallel.nSendGhosts ; pid++ ) {

	
	    /* Move ovel blocks per send ghost */
	    unsigned int bid;
	    for( bid = 0 ; bid < info->parallel.sendScalarBlocks[pid] ; bid++ ) {
	    

		// Move inside blocks
		unsigned int i,
		    gid,
		    lid;
	    
		for( i = 0 ; i < MPI_BUFF_SIZE ; i++ ) {

		    // Global index inside sendBuffer
		    gid = pid * info->parallel.sendScalarBlocks[pid] * MPI_BUFF_SIZE +  bid * MPI_BUFF_SIZE + i;

		    // Local index inside processor list
		    lid = bid * MPI_BUFF_SIZE + i;

		    // Copy data
		    if( lid < info->parallel.sendGhostIds[pid][1]) {

			info->parallel.scalarSendBuff[gid] = fld[ info->parallel.sendGhostIds[pid][lid+2] ][k];

		    }
		
		}
	    
	    }

	}
	


	// Send data in send buffer

	MPI_Request request;
	MPI_Status status;

    
	// Move over send ghosts
	for( pid = 0 ; pid < info->parallel.nSendGhosts ; pid++ ) {

	    // Move ovel blocks per send ghost
	    unsigned int bid;
	    for( bid = 0 ; bid < info->parallel.sendScalarBlocks[pid] ; bid++ ) {

		// Start position of each block
		unsigned int gid = pid * info->parallel.sendScalarBlocks[pid] * MPI_BUFF_SIZE +  bid * MPI_BUFF_SIZE;

		// Send data. tag = bid
		MPI_Isend (&info->parallel.scalarSendBuff[gid], MPI_BUFF_SIZE, MPI_DOUBLE, info->parallel.sendGhostIds[pid][0], bid, MPI_COMM_WORLD, &request);

	    
	    }

	}




	// Receive data in recv buffer
    
	// Move over send ghosts
	for( pid = 0 ; pid < info->parallel.nRecvGhosts ; pid++ ) {

	    // Move ovel blocks per send ghost
	    unsigned int bid;
	    for( bid = 0 ; bid < info->parallel.recvScalarBlocks[pid] ; bid++ ) {

		// Start position of each block
		unsigned int gid = pid * info->parallel.recvScalarBlocks[pid] * MPI_BUFF_SIZE +  bid * MPI_BUFF_SIZE;

		// Send data. tag = bid
		MPI_Irecv (&info->parallel.scalarRecvBuff[gid], MPI_BUFF_SIZE, MPI_DOUBLE, info->parallel.recvGhostIds[pid][0], bid, MPI_COMM_WORLD, &request);

	    
	    }

	}


	// Finish communication between processors
	MPI_Wait(&request, &status);
    

	// Copy data from buffer
    
	// Move over send ghosts
	for( pid = 0 ; pid < info->parallel.nRecvGhosts ; pid++ ) {
	
	    /* Move ovel blocks per recv ghost */
	    unsigned int bid;
	    for( bid = 0 ; bid < info->parallel.recvScalarBlocks[pid] ; bid++ ) {
	    
		// Move inside blocks
		unsigned int i,
		    gid,
		    lid;
	    
		for( i = 0 ; i < MPI_BUFF_SIZE ; i++ ) {

		    // Global index inside recvBuffer
		    gid = pid * info->parallel.recvScalarBlocks[pid] * MPI_BUFF_SIZE +  bid * MPI_BUFF_SIZE + i;

		    // Local index inside processor list
		    lid = bid * MPI_BUFF_SIZE + i;

		    // Copy data
		    if( lid < info->parallel.recvGhostIds[pid][1]) {

			fld[ info->lattice.nlocal + info->parallel.recvGhostIds[pid][lid+2] ][k] = info->parallel.scalarRecvBuff[gid];

		    }
		
		}
	    
	    }

	}
    
    

    
	MPI_Barrier(MPI_COMM_WORLD);

    }

    
}




// Blocking version

/* void syncPdfField( struct solverInfo* info, double** fld, int sz ){ */

/*     unsigned int i, j, k, pid; */
    
/*     MPI_Barrier(MPI_COMM_WORLD); */

/*     // Allocate buffers */
/*     double sendBuff[MPI_BUFF_SIZE]; */
/*     double recvBuff[MPI_BUFF_SIZE]; */

    
    
/*     // Send information. Divide by blocks */

/*     for( k = 0 ; k < sz ; k++ ) { */

	
/* 	// Move over send ghosts */
/* 	for( i = 0 ; i < info->parallel.nSendGhosts ; i++ ) { */

/* 	    // Number of blocks */
/* 	    const int buffBlocks = (int)floor( info->parallel.sendGhostIds[i][1] / MPI_BUFF_SIZE ) + 1; */
	
/* 	    unsigned int bid; */
/* 	    for( bid = 0 ; bid < buffBlocks ; bid++ ) { */
	
/* 	    	// Block positions in sendGhostIds */
/* 	    	unsigned int min, max; */
/* 	    	min = MPI_BUFF_SIZE * bid; */
/* 	    	max = MPI_BUFF_SIZE * (bid + 1); */

/* 	    	if(max > info->parallel.sendGhostIds[i][1] ) { max = info->parallel.sendGhostIds[i][1]; } */

	    
/* 	    	// Move over blocks */
/* 	    	unsigned int m = 0; */
/* 	    	for( j = min ; j < max ; j++ ) { */
	    
/* 	    	    sendBuff[m] = fld[ info->parallel.sendGhostIds[i][j+2] ][k]; */
/* 	    	    m++; */

/* 	    	} */

/* 	    	// Send data */
/* 	    	MPI_Send (sendBuff, MPI_BUFF_SIZE, MPI_DOUBLE, info->parallel.sendGhostIds[i][0], (bid + 1) * (k+1), MPI_COMM_WORLD); */

/* 	    } */

/* 	} */
	
	
/*     } */


/*     /\* MPI_Barrier(MPI_COMM_WORLD); *\/ */

    
/*     // Receive information. Divide by blocks */

/*     for( k = 0 ; k < sz ; k++ ) { */

/*     	// Move over recv ghosts */
/*     	for( i = 0 ; i < info->parallel.nRecvGhosts ; i++ ) { */

/*     	    // Number of blocks */
/*     	    const int buffBlocks = (int)floor( info->parallel.sendGhostIds[i][1] / MPI_BUFF_SIZE ) + 1; */
	
/*     	    unsigned int bid; */
/*     	    for( bid = 0 ; bid < buffBlocks ; bid++ ) { */

/*     		// Block positions in recvGhostIds */
/*     		unsigned int min, max; */
/*     		min = MPI_BUFF_SIZE * bid; */
/*     		max = MPI_BUFF_SIZE * (bid + 1); */

/*     		if(max > info->parallel.recvGhostIds[i][1] ) { max = info->parallel.recvGhostIds[i][1]; } */

/*     		// Receive data */
/*     		MPI_Status status; */
/*     		MPI_Recv (recvBuff, MPI_BUFF_SIZE, MPI_DOUBLE, info->parallel.recvGhostIds[i][0], (bid + 1) * (k+1), MPI_COMM_WORLD, &status); */


/*     		// Update field */
/*     		unsigned int m = 0; */
/*     		for( j = min ; j < max ; j++ ) { */

/*     		    fld[ info->lattice.nlocal + info->parallel.recvGhostIds[i][j+2] ][k] = recvBuff[m]; */
/*     		    m++; */

/*     		} */

	    
/*     	    } */
	    
/*     	} */

/*     } */
    
/*     MPI_Barrier(MPI_COMM_WORLD); */


    
/* } */
