#include <syncScalarField.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>


void syncScalarField( struct solverInfo* info, double* fld ) {

    
    MPI_Barrier(MPI_COMM_WORLD);


    
    // Send information. Divide by blocks

    MPI_Request request;
    MPI_Status status;

    
    // Copy data to send buffer
    
    // Move over send ghosts
    unsigned int pid;
    for( pid = 0 ; pid < info->parallel.nSendGhosts ; pid++ ) {

	
    	/* Move ovel blocks per send ghost */
    	unsigned int bid;
    	for( bid = 0 ; bid < info->parallel.sendScalarBlocks[pid] ; bid++ ) {

    	    // Move inside blocks
    	    unsigned int i,
    		lid;
	    
    	    for( i = 0 ; i < MPI_BUFF_SIZE ; i++ ) {

    		// Local index inside processor list
    		lid = bid * MPI_BUFF_SIZE + i;
		
    		// Copy data
    		if( lid < info->parallel.sendGhostIds[pid][1]) {

    		    info->parallel.ssbuf[pid][lid] = fld[ info->parallel.sendGhostIds[pid][lid+2] ];

    		}
		
    	    }
	    
    	}

    }
	




    /* if(info->parallel.pid == 0) { */

    /* 	// Move over send ghosts */
    /* 	for( pid = 0 ; pid < info->parallel.nSendGhosts ; pid++ ) { */
	    
    /* 	    unsigned int i; */
    /* 	    for( i = 0 ; i < info->parallel.sendGhostIds[pid][1] ; i++ ) { */
		
    /* 		printf("%f\n",info->parallel.ssbuf[pid][i]); */
		
    /* 	    } */
	    
    /* 	} */
    /* } */

    
    // Send data in send buffer

    
    // Move over send ghosts
    for( pid = 0 ; pid < info->parallel.nSendGhosts ; pid++ ) {

    	// Move ovel blocks per send ghost
    	unsigned int bid;
    	for( bid = 0 ; bid < info->parallel.sendScalarBlocks[pid] ; bid++ ) {

    	    // Start position of each block
    	    unsigned int lid = bid * MPI_BUFF_SIZE;

            // Send data. tag = bid
	    if(  bid != (info->parallel.sendScalarBlocks[pid] - 1)  ) {
		/* MPI_Isend (&info->parallel.ssbuf[pid][lid], MPI_BUFF_SIZE, MPI_DOUBLE, info->parallel.sendGhostIds[pid][0], bid, MPI_COMM_WORLD, &request); */
		MPI_Send (&info->parallel.ssbuf[pid][lid], MPI_BUFF_SIZE, MPI_DOUBLE, info->parallel.sendGhostIds[pid][0], bid, MPI_COMM_WORLD);
	    }
	    else {

		int msg = info->parallel.sendScalarBlocks[pid] * MPI_BUFF_SIZE - info->parallel.sendGhostIds[pid][1];
		msg = MPI_BUFF_SIZE - msg;
		/* MPI_Isend (&info->parallel.ssbuf[pid][lid], msg, MPI_DOUBLE, info->parallel.sendGhostIds[pid][0], bid, MPI_COMM_WORLD, &request); */
		MPI_Send (&info->parallel.ssbuf[pid][lid], msg, MPI_DOUBLE, info->parallel.sendGhostIds[pid][0], bid, MPI_COMM_WORLD);

	    }
	    
    	}

    }




    // Receive data in recv buffer
    
    // Move over send ghosts
    for( pid = 0 ; pid < info->parallel.nRecvGhosts ; pid++ ) {

    	// Move ovel blocks per send ghost
    	unsigned int bid;
    	for( bid = 0 ; bid < info->parallel.recvScalarBlocks[pid] ; bid++ ) {

    	    // Start position of each block
    	    unsigned int lid =  bid * MPI_BUFF_SIZE;

            // Send data. tag = bid
    	    if(  bid != (info->parallel.recvScalarBlocks[pid] - 1)  ) {
    		/* MPI_Irecv (&info->parallel.srbuf[pid][lid], MPI_BUFF_SIZE, MPI_DOUBLE, info->parallel.recvGhostIds[pid][0], bid, MPI_COMM_WORLD, &request); */
		MPI_Recv (&info->parallel.srbuf[pid][lid], MPI_BUFF_SIZE, MPI_DOUBLE, info->parallel.recvGhostIds[pid][0], bid, MPI_COMM_WORLD, &status);
    	    }
    	    else {
    	    	int msg = info->parallel.recvScalarBlocks[pid] * MPI_BUFF_SIZE - info->parallel.recvGhostIds[pid][1];
		msg = MPI_BUFF_SIZE - msg;
    	    	/* MPI_Irecv (&info->parallel.srbuf[pid][lid], msg, MPI_DOUBLE, info->parallel.recvGhostIds[pid][0], bid, MPI_COMM_WORLD, &request); */
    	    	MPI_Recv (&info->parallel.srbuf[pid][lid], msg, MPI_DOUBLE, info->parallel.recvGhostIds[pid][0], bid, MPI_COMM_WORLD, &status);
    	    }

    	}

    }

    
    /* // Finish communication between processors */
    /* MPI_Wait(&request, &status); */
    




    /* if(info->parallel.pid == 1) { */

    /* 	// Move over send ghosts */
    /* 	for( pid = 0 ; pid < info->parallel.nRecvGhosts ; pid++ ) { */
	    
    /* 	    unsigned int i; */
    /* 	    for( i = 0 ; i < info->parallel.recvGhostIds[pid][1] ; i++ ) { */
		
    /* 		printf("%f\n",info->parallel.srbuf[pid][i]); */
		
    /* 	    } */
	    
    /* 	} */
    /* } */

    
    // Copy data from buffer
    
    // Move over send ghosts
    for( pid = 0 ; pid < info->parallel.nRecvGhosts ; pid++ ) {
	    
	unsigned int i;
	for( i = 0 ; i < info->parallel.recvGhostIds[pid][1] ; i++ ) {
		
	    // Copy data
	    fld[ info->lattice.nlocal + info->parallel.recvGhostIds[pid][i+2] ] = info->parallel.srbuf[pid][i];
		
	}
	    

    }
    
    
    
    MPI_Barrier(MPI_COMM_WORLD);

    
}





// First non-blocking version. Not working

/* void syncScalarField( struct solverInfo* info, double* fld ) { */

    
/*     MPI_Barrier(MPI_COMM_WORLD); */

    
/*     // Send information. Divide by blocks */

/*     MPI_Request request; */
/*     MPI_Status status; */

    
/*     // Copy data to send buffer */
    
/*     // Move over send ghosts */
/*     unsigned int pid; */
/*     for( pid = 0 ; pid < info->parallel.nSendGhosts ; pid++ ) { */

	
/*     	/\* Move ovel blocks per send ghost *\/ */
/*     	unsigned int bid; */
/*     	for( bid = 0 ; bid < info->parallel.sendScalarBlocks[pid] ; bid++ ) { */

/*     	    // Move inside blocks */
/*     	    unsigned int i, */
/*     		gid, */
/*     		lid; */
	    
/*     	    for( i = 0 ; i < MPI_BUFF_SIZE ; i++ ) { */

/*     		// Global index inside sendBuffer */
/*     		gid = pid * info->parallel.sendScalarBlocks[pid] * MPI_BUFF_SIZE +  bid * MPI_BUFF_SIZE + i; */

/*     		// Local index inside processor list */
/*     		lid = bid * MPI_BUFF_SIZE + i; */
		
/*     		// Copy data */
/*     		if( lid < info->parallel.sendGhostIds[pid][1]) { */

/*     		    info->parallel.scalarSendBuff[gid] = fld[ info->parallel.sendGhostIds[pid][lid+2] ]; */

/*     		} */
		
/*     	    } */
	    
/*     	} */

/*     } */
	

    
/*     // Send data in send buffer */

    
/*     // Move over send ghosts */
/*     for( pid = 0 ; pid < info->parallel.nSendGhosts ; pid++ ) { */

/*     	// Move ovel blocks per send ghost */
/*     	unsigned int bid; */
/*     	for( bid = 0 ; bid < info->parallel.sendScalarBlocks[pid] ; bid++ ) { */

/*     	    // Start position of each block */
/*     	    unsigned int gid = pid * info->parallel.sendScalarBlocks[pid] * MPI_BUFF_SIZE +  bid * MPI_BUFF_SIZE; */

/*             // Send data. tag = bid */
/*     	    MPI_Isend (&info->parallel.scalarSendBuff[gid], MPI_BUFF_SIZE, MPI_DOUBLE, info->parallel.sendGhostIds[pid][0], bid, MPI_COMM_WORLD, &request); */

	    
/*     	} */

/*     } */




/*     // Receive data in recv buffer */
    
/*     // Move over send ghosts */
/*     for( pid = 0 ; pid < info->parallel.nRecvGhosts ; pid++ ) { */

/*     	// Move ovel blocks per send ghost */
/*     	unsigned int bid; */
/*     	for( bid = 0 ; bid < info->parallel.recvScalarBlocks[pid] ; bid++ ) { */

/*     	    // Start position of each block */
/*     	    unsigned int gid = pid * info->parallel.recvScalarBlocks[pid] * MPI_BUFF_SIZE +  bid * MPI_BUFF_SIZE; */

/*             // Send data. tag = bid */
/*     	    MPI_Irecv (&info->parallel.scalarRecvBuff[gid], MPI_BUFF_SIZE, MPI_DOUBLE, info->parallel.recvGhostIds[pid][0], bid, MPI_COMM_WORLD, &request); */
	    
/*     	} */

/*     } */


    
/*     // Finish communication between processors */
/*     MPI_Wait(&request, &status); */
    

    
/*     // Copy data from buffer */
    
/*     // Move over send ghosts */
/*     for( pid = 0 ; pid < info->parallel.nRecvGhosts ; pid++ ) { */
	
/*     	/\* Move ovel blocks per recv ghost *\/ */
/*     	unsigned int bid; */
/*     	for( bid = 0 ; bid < info->parallel.recvScalarBlocks[pid] ; bid++ ) { */
	    
/*     	    // Move inside blocks */
/*     	    unsigned int i, */
/*     		gid, */
/*     		lid; */
	    
/*     	    for( i = 0 ; i < MPI_BUFF_SIZE ; i++ ) { */

/*     		// Global index inside recvBuffer */
/*     		gid = pid * info->parallel.recvScalarBlocks[pid] * MPI_BUFF_SIZE +  bid * MPI_BUFF_SIZE + i; */

/*     		// Local index inside processor list */
/*     		lid = bid * MPI_BUFF_SIZE + i; */
		
/*     		// Copy data */
/*     		if( lid < info->parallel.recvGhostIds[pid][1]) { */
		    
/*     		    fld[ info->lattice.nlocal + info->parallel.recvGhostIds[pid][lid+2] ] = info->parallel.scalarRecvBuff[gid]; */

/*     		} */
		
/*     	    } */
	    
/*     	} */

/*     } */
    
    

    
/*     MPI_Barrier(MPI_COMM_WORLD); */

    
/* } */






/* // Blocking version */

/* void syncScalarField( struct solverInfo* info, double* fld ) { */

/*     unsigned int i, j, k, pid; */
    
/*     MPI_Barrier(MPI_COMM_WORLD); */

/*     // Allocate buffers */
/*     double sendBuff[MPI_BUFF_SIZE]; */
/*     double recvBuff[MPI_BUFF_SIZE]; */

    
    
/*     // Send information. Divide by blocks */
	
/*     // Move over send ghosts */
/*     for( i = 0 ; i < info->parallel.nSendGhosts ; i++ ) { */

/* 	// Number of blocks */
/* 	const int buffBlocks = (int)floor( info->parallel.sendGhostIds[i][1] / MPI_BUFF_SIZE ) + 1; */
	
/* 	unsigned int bid; */
/* 	for( bid = 0 ; bid < buffBlocks ; bid++ ) { */
	
/* 	    // Block positions in sendGhostIds */
/* 	    unsigned int min, max; */
/* 	    min = MPI_BUFF_SIZE * bid; */
/* 	    max = MPI_BUFF_SIZE * (bid + 1); */

/* 	    if(max > info->parallel.sendGhostIds[i][1] ) { max = info->parallel.sendGhostIds[i][1]; } */

	    
/* 	    // Move over blocks */
/* 	    unsigned int m = 0; */
/* 	    for( j = min ; j < max ; j++ ) { */
	    
/* 		sendBuff[m] = fld[ info->parallel.sendGhostIds[i][j+2] ]; */
/* 		m++; */

/* 	    } */

/* 	    // Send data */
/* 	    MPI_Send (sendBuff, MPI_BUFF_SIZE, MPI_DOUBLE, info->parallel.sendGhostIds[i][0], (bid + 1) * (k+1), MPI_COMM_WORLD); */

/* 	} */

/*     } */
	
       
    
/*     // Receive information. Divide by blocks */

/*     // Move over recv ghosts */
/*     for( i = 0 ; i < info->parallel.nRecvGhosts ; i++ ) { */

/* 	// Number of blocks */
/* 	const int buffBlocks = (int)floor( info->parallel.sendGhostIds[i][1] / MPI_BUFF_SIZE ) + 1; */
	
/* 	unsigned int bid; */
/* 	for( bid = 0 ; bid < buffBlocks ; bid++ ) { */

/* 	    // Block positions in recvGhostIds */
/* 	    unsigned int min, max; */
/* 	    min = MPI_BUFF_SIZE * bid; */
/* 	    max = MPI_BUFF_SIZE * (bid + 1); */

/* 	    if(max > info->parallel.recvGhostIds[i][1] ) { max = info->parallel.recvGhostIds[i][1]; } */

/* 	    // Receive data */
/* 	    MPI_Status status; */
/* 	    MPI_Recv (recvBuff, MPI_BUFF_SIZE, MPI_DOUBLE, info->parallel.recvGhostIds[i][0], (bid + 1) * (k+1), MPI_COMM_WORLD, &status); */


/* 	    // Update field */
/* 	    unsigned int m = 0; */
/* 	    for( j = min ; j < max ; j++ ) { */

/* 		fld[ info->lattice.nlocal + info->parallel.recvGhostIds[i][j+2] ] = recvBuff[m]; */
/* 		m++; */

/* 	    } */

	    
/* 	} */
	    
/*     } */

    
/*     MPI_Barrier(MPI_COMM_WORLD); */

    
/* } */
