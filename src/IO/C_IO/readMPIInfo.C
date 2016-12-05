// Read information for c-written solvers

#include <dictionary.h>
#include <readMPIInfo.h>


#ifdef __cplusplus
extern "C" {
#endif


    struct mpiInfo readMPIInfo( int pid, int sz, int nlocal ) {

	struct mpiInfo info;
	

	// Basic environment properties
	info.nlocal = nlocal;
	info.pid = pid;
	info.worldSize = sz;

	
	// // Read total ghost elements using globalGhostsIds
	// std::ostringstream latticeFolder;
	// latticeFolder << "processor" << pid << "/" << lbm->name() << "_lattice/";
	
	// fileName = latticeFolder.str() + "globalGhostsIds" ;
    
	// inFile.open( fileName.c_str() );
	// if( !inFile.is_open() ) {
	//     std::cout << "Unable to open file " << fileName << std::endl;
	//     exit(1);
	// }
    
	// inFile >> info.nghosts;
    
	// inFile.close();



	// // Read total send ghosts
	// fileName = latticeFolder.str() + "sendMapIds" ;     
	// inFile.open( fileName.c_str() );
	// if( !inFile.is_open() ) {
	//     std::cout << "Unable to open file " << fileName << std::endl;
	//     exit(1);
	// }
	// inFile >> info.parallel.nSendGhosts;

	// // Resize Send ghost ids
	// info.parallel.sendGhostIds = (uint**)malloc( info.parallel.nSendGhosts * sizeof(unsigned int*) );  
	// info.parallel.ssbuf = (c_scalar**)malloc( info.parallel.nSendGhosts * sizeof(c_scalar*) );
    

	// for(uint i = 0 ; i < info.parallel.nSendGhosts ; i++) {
	
	//     uint pid,nel;
	//     inFile >> pid;
	//     inFile >> nel;

	//     info.parallel.sendGhostIds[i] = (uint*)malloc( (nel + 2) * sizeof(uint) );
	//     info.parallel.ssbuf[i] = (c_scalar*)malloc( nel * sizeof(c_scalar) );

	//     info.parallel.sendGhostIds[i][0] = pid;
	//     info.parallel.sendGhostIds[i][1] = nel;

	//     for(uint j = 0 ; j < nel ; j++) {
	// 	inFile >> info.parallel.sendGhostIds[i][j+2];
	//     }
	
	// }

	// inFile.close();
    


	// // Compute scalar send blocks per process
	// info.parallel.sendScalarBlocks = (int*)malloc( info.parallel.nSendGhosts * sizeof(int) );

	// int nsb(0);
    
	// for(uint i = 0 ; i < info.parallel.nSendGhosts ; i++) {

	//     const int buffBlocks = ceil (1.0 * info.parallel.sendGhostIds[i][1] / MPI_BUFF_SIZE );
	
	//     info.parallel.sendScalarBlocks[i] = buffBlocks;

	//     nsb += buffBlocks * MPI_BUFF_SIZE;
	
	// }

	// // Resize send buffer
	// info.parallel.scalarSendBuff = (c_scalar*)malloc( nsb * sizeof(c_scalar) );




    

	// // Read total recv ghosts
	// fileName = latticeFolder.str() + "recvMapIds" ;     
	// inFile.open( fileName.c_str() );
	// if( !inFile.is_open() ) {
	//     std::cout << "Unable to open file " << fileName << std::endl;
	//     exit(1);
	// }
	// inFile >> info.parallel.nRecvGhosts;

	// // Resize Recv ghost ids
	// info.parallel.recvGhostIds   = (uint**)malloc( info.parallel.nRecvGhosts * sizeof(uint*) );
	// info.parallel.srbuf = (c_scalar**)malloc( info.parallel.nRecvGhosts * sizeof(c_scalar*) );
    
	// for(uint i = 0 ; i < info.parallel.nRecvGhosts ; i++) {
	
	//     uint pid,nel,aux;
	//     inFile >> pid;
	//     inFile >> nel;

	//     info.parallel.recvGhostIds[i] = (uint*)malloc( (nel + 2) * sizeof(uint) );
	//     info.parallel.srbuf[i] = (c_scalar*)malloc( nel * sizeof(c_scalar) );

	//     info.parallel.recvGhostIds[i][0] = pid;
	//     info.parallel.recvGhostIds[i][1] = nel;
	
	//     for(uint j = 0 ; j < nel ; j++) {
	// 	inFile >> info.parallel.recvGhostIds[i][j+2];
	//     }

	//     for(uint j = 0 ; j < nel ; j++) {
	// 	inFile >> aux;
	//     }

	
	// }

	// inFile.close();

    
	// // Compute send blocks per process
	// info.parallel.recvScalarBlocks = (int*)malloc( info.parallel.nRecvGhosts * sizeof(int) );

	// int nrb(0);
    
	// for(uint i = 0 ; i < info.parallel.nRecvGhosts ; i++) {

	//     const int buffBlocks = ceil( 1.0 * info.parallel.recvGhostIds[i][1] / MPI_BUFF_SIZE );
	
	//     info.parallel.recvScalarBlocks[i] = buffBlocks;

	//     nrb += buffBlocks * MPI_BUFF_SIZE;
	
	// }

    
	// // Resize send buffer
	// info.parallel.scalarRecvBuff = (c_scalar*)malloc( nrb * sizeof(c_scalar) );
   
    
	return info;
    
    }


#ifdef __cplusplus
}
#endif
