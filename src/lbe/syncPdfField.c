#include <syncPdfField.h>
#include <stdlib.h>
#include <stdio.h>

void syncPdfField( const struct solverInfo* info, double** fld, int sz ) {

    unsigned int i, j, k, pid;

    MPI_Barrier(MPI_COMM_WORLD);

    
    // Send information

    // Move over send ghosts
    for( i = 0 ; i < info->parallel.nSendGhosts ; i++ ) {

    	// Create buffer and copy data
    	double* buf = (double*)malloc( info->parallel.sendGhostIds[i][1] * sz * sizeof(double) );

    	for( j = 0 ; j < info->parallel.sendGhostIds[i][1] ; j++ ) {

	    for( k = 0 ; k < sz ; k++ ) {
	    
		buf[j*sz + k] = fld[ info->parallel.sendGhostIds[i][j+2] ][k];

	    }

    	}

    	// Send data
    	MPI_Send (buf, info->parallel.sendGhostIds[i][1] * sz, MPI_DOUBLE, info->parallel.sendGhostIds[i][0], info->parallel.pid, MPI_COMM_WORLD);

	/* MPI_Send (&buf,count,datatype,dest,tag,comm) */

    }


    MPI_Barrier(MPI_COMM_WORLD);    

    
    // Receive information

    // Move over recv ghosts
    for( i = 0 ; i < info->parallel.nRecvGhosts ; i++ ) {

    	// Create buffer and copy data
    	double* buf = (double*)malloc( info->parallel.recvGhostIds[i][1] * sz * sizeof(double) );

    	// Receive data
    	MPI_Status status;
    	MPI_Recv (buf, info->parallel.recvGhostIds[i][1] * sz, MPI_DOUBLE, info->parallel.recvGhostIds[i][0], info->parallel.recvGhostIds[i][0], MPI_COMM_WORLD, &status);


    	// Update field
    	for( j = 0 ; j < info->parallel.recvGhostIds[i][1] ; j++ ) {

	    for( k = 0 ; k < sz ; k++ ) {
		
		fld[ info->lattice.nlocal + info->parallel.recvGhostIds[i][j+2] ][k] = buf[j*sz + k];

	    }

	}

	    
    	/* MPI_Recv (&buf,count,datatype,source,tag,comm,&status) */
    }


    MPI_Barrier(MPI_COMM_WORLD);    
    
}
