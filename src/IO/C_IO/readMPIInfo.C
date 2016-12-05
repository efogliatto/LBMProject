// Read information for c-written solvers

#include <dictionary.h>
#include <readMPIInfo.h>
#include <LBModelCreator.h>
#include <fstream>

#ifdef __cplusplus
extern "C" {
#endif


    struct mpiInfo readMPIInfo( int pid, int sz, int nlocal ) {

	struct mpiInfo info;
	

	// Basic environment properties
	info.nlocal = nlocal;
	info.pid = pid;
	info.worldSize = sz;


	// DqQq Model
	dictionary lp("properties/latticeProperties");
	LBModelCreator creator;
	basicLBModel* lbm = creator.create( lp.lookUpEntry<string>("LBModel") );

	
	// Read total ghost elements using globalGhostsIds
	std::ostringstream latticeFolder;
	latticeFolder << "processor" << pid << "/" << lbm->name() << "_lattice/";
	
	std::string fileName = latticeFolder.str() + "globalGhostsIds" ;

	std::ifstream inFile;
	inFile.open( fileName.c_str() );
	if( !inFile.is_open() ) {
	    std::cout << "Unable to open file " << fileName << std::endl;
	    exit(1);
	}
    
	inFile >> info.nghosts;
    
	inFile.close();



	// Read total send ghosts
	fileName = latticeFolder.str() + "sendMapIds" ;     
	inFile.open( fileName.c_str() );
	if( !inFile.is_open() ) {
	    std::cout << "Unable to open file " << fileName << std::endl;
	    exit(1);
	}
	inFile >> info.nSendGhosts;

	// Resize Send ghost ids
	info.sendGhostIds = (uint**)malloc( info.nSendGhosts * sizeof(unsigned int*) );  
	info.ssbuf = (c_scalar**)malloc( info.nSendGhosts * sizeof(c_scalar*) );
    

	for(uint i = 0 ; i < info.nSendGhosts ; i++) {
	
	    uint pid,nel;
	    inFile >> pid;
	    inFile >> nel;

	    info.sendGhostIds[i] = (uint*)malloc( (nel + 2) * sizeof(uint) );
	    info.ssbuf[i] = (c_scalar*)malloc( nel * sizeof(c_scalar) );

	    info.sendGhostIds[i][0] = pid;
	    info.sendGhostIds[i][1] = nel;

	    for(uint j = 0 ; j < nel ; j++) {
		inFile >> info.sendGhostIds[i][j+2];
	    }
	
	}

	inFile.close();
    


	// Compute scalar send blocks per process
	info.sendScalarBlocks = (int*)malloc( info.nSendGhosts * sizeof(int) );

	int nsb(0);
    
	for(uint i = 0 ; i < info.nSendGhosts ; i++) {

	    const int buffBlocks = ceil (1.0 * info.sendGhostIds[i][1] / MPI_BUFF_SIZE );
	
	    info.sendScalarBlocks[i] = buffBlocks;

	    nsb += buffBlocks * MPI_BUFF_SIZE;
	
	}

	// Resize send buffer
	info.scalarSendBuff = (c_scalar*)malloc( nsb * sizeof(c_scalar) );




    

	// Read total recv ghosts
	fileName = latticeFolder.str() + "recvMapIds" ;     
	inFile.open( fileName.c_str() );
	if( !inFile.is_open() ) {
	    std::cout << "Unable to open file " << fileName << std::endl;
	    exit(1);
	}
	inFile >> info.nRecvGhosts;

	// Resize Recv ghost ids
	info.recvGhostIds   = (uint**)malloc( info.nRecvGhosts * sizeof(uint*) );
	info.srbuf = (c_scalar**)malloc( info.nRecvGhosts * sizeof(c_scalar*) );

	
	for(uint i = 0 ; i < info.nRecvGhosts ; i++) {
	
	    uint pid,nel,aux;
	    inFile >> pid;
	    inFile >> nel;

	    info.recvGhostIds[i] = (uint*)malloc( (nel + 2) * sizeof(uint) );
	    info.srbuf[i] = (c_scalar*)malloc( nel * sizeof(c_scalar) );

	    info.recvGhostIds[i][0] = pid;
	    info.recvGhostIds[i][1] = nel;
	
	    for(uint j = 0 ; j < nel ; j++) {
		inFile >> info.recvGhostIds[i][j+2];
	    }

	    for(uint j = 0 ; j < nel ; j++) {
		inFile >> aux;
	    }

	
	}

	inFile.close();



	
    
	// Compute send blocks per process
	info.recvScalarBlocks = (int*)malloc( info.nRecvGhosts * sizeof(int) );

	int nrb(0);
    
	for(uint i = 0 ; i < info.nRecvGhosts ; i++) {

	    const int buffBlocks = ceil( 1.0 * info.recvGhostIds[i][1] / MPI_BUFF_SIZE );
	
	    info.recvScalarBlocks[i] = buffBlocks;

	    nrb += buffBlocks * MPI_BUFF_SIZE;
	
	}

    
	// Resize send buffer
	info.scalarRecvBuff = (c_scalar*)malloc( nrb * sizeof(c_scalar) );
   
    
	return info;
    
    }


#ifdef __cplusplus
}
#endif
