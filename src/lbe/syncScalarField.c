#include <syncScalarField.h>
#include <stdlib.h>
#include <mpi.h>

void syncScalarField( struct twoPhasesFields* fields, const struct solverInfo* info, double* fld ) {

    unsigned int i, j, pid;


    
    // Send information

    // Move over send ghosts
    for( i = 0 ; i < info->parallel.nSendGhosts ; i++ ) {

	// Create buffer and copy data
	double* buf = (double*)malloc( info->parallel.sendGhostIds[i][1] * sizeof(double) );

	for( j = 0 ; j < info->parallel.sendGhostIds[i][1] ; j++ ) {

	    buf[j] = fld[ info->parallel.sendGhostIds[i][j+2] ];

	}

	// Send data
	MPI_Send (&buf, info->parallel.sendGhostIds[i][1], MPI_DOUBLE, info->parallel.sendGhostIds[i][0], info->parallel.pid, MPI_COMM_WORLD);

	/* MPI_Send (&buf,count,datatype,dest,tag,comm) */

    }




    
    // Receive information

    // Move over recv ghosts
    for( i = 0 ; i < info->parallel.nRecvGhosts ; i++ ) {

	// Create buffer and copy data
	double* buf = (double*)malloc( info->parallel.recvGhostIds[i][1] * sizeof(double) );

	// Receive data
	MPI_Status status;
	MPI_Recv (&buf, info->parallel.recvGhostIds[i][1], MPI_DOUBLE, info->parallel.recvGhostIds[i][0], info->parallel.recvGhostIds[i][0], MPI_COMM_WORLD, &status);


	// Update field
	
	for( j = 0 ; j < info->parallel.recvGhostIds[i][1] ; j++ ) {

	    fld[ info->lattice.nlocal + info->parallel.recvGhostIds[i][j+2] ] = buf[j];

	}

	    
	/* MPI_Recv (&buf,count,datatype,source,tag,comm,&status) */
    }

    
}
