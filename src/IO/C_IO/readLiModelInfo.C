// Read information for c-written solvers

#include <dictionary.h>
#include <LBModelCreator.h>
#include <fstream>
#include <readLiModelInfo.h>


#ifdef __cplusplus
extern "C" {
#endif


    struct liModelInfo readLiModelInfo( int pid, int sz ) {

    struct liModelInfo info;

    // Read time properties
    dictionary tp("properties/simulation");

    info.time.start = (unsigned int)tp.lookUpEntry<double>("startTime");
    info.time.end = (unsigned int)tp.lookUpEntry<double>("endTime");
    info.time.tstep = (c_scalar)tp.lookUpEntry<double>("timeStep");
    info.time.writeInterval = (unsigned int)tp.lookUpEntry<double>("writeInterval");
    info.time.current = info.time.start;
    info.time.stp = 0;



    info.time.st = time( NULL );
    
    gettimeofday( &info.time.stt, NULL );
    


    // Read lattice properties
    dictionary lp("properties/latticeProperties");

    LBModelCreator creator;
    basicLBModel* lbm = creator.create( lp.lookUpEntry<string>("LBModel") );
    
    info.lattice.size = (c_scalar)lp.lookUpEntry<double>("latticeSize");
    info.lattice.c = info.lattice.size / info.time.tstep; 
    info.lattice.cs2 = info.lattice.c * info.lattice.c * lbm->cs2(); 
    info.lattice.d = lbm->D();
    info.lattice.Q = lbm->Q();



    
    // Read total number of points from global Ids
    std::ostringstream latticeFolder;
    latticeFolder << "processor" << pid << "/" << lbm->name() << "_lattice/";
    std::string fileName = latticeFolder.str() + "globalIds" ;
    
    std::ifstream inFile;
    inFile.open( fileName.c_str() );
    if( !inFile.is_open() ) {
    	std::cout << "Unable to open file " << fileName << std::endl;
    	exit(1);
    }
    
    inFile >> info.lattice.nlocal;

    inFile.close();



    // Lattice weights
    const vector<double> omega = lbm->omega();
    info.lattice.omega = (c_scalar*)malloc( lbm->Q() * sizeof(c_scalar));
    for(uint i = 0 ; i < lbm->Q() ; i++)
    	info.lattice.omega[i] = omega[i];


    // Lattice reverse indices
    info.lattice.reverse = (int*)malloc( lbm->Q() * sizeof(int));
    for(uint i = 0 ; i < lbm->Q() ; i++)
    	info.lattice.reverse[i] = lbm->reverse(i);
    

    // Lattice velocities
    const vector<Vector3> vel = lbm->latticeVel();
    info.lattice.vel = (int**)malloc( lbm->Q() * sizeof(int*));
    for(uint i = 0 ; i < lbm->Q() ; i++)
    	info.lattice.vel[i] = (int*)malloc( 3 * sizeof(int));

    for(uint i = 0 ; i < lbm->Q() ; i++) {
    	info.lattice.vel[i][0] = (int)vel[i].x();
    	info.lattice.vel[i][1] = (int)vel[i].y();
    	info.lattice.vel[i][2] = (int)vel[i].z();
    }


    // Pseudopotential weights
    const vector<double> weights = lbm->weights();
    info.lattice.weights = (c_scalar*)malloc( lbm->Q() * sizeof(c_scalar));
    for(uint i = 0 ; i < lbm->Q() ; i++)
    	info.lattice.weights[i] = weights[i];
    
    
    

    // Read macroscopic properties
    dictionary mp("properties/macroscopicProperties");

    // Read diagonal entries
    pdf le = mp.lookUpEntry<pdf>("f/Lambda");

    // Create lambda
    Matrix Lambda( le.size() );
    for(uint i = 0 ; i < le.size() ; i++)
    	Lambda[i][i] = le[i];

    

    // Lambda = Lambda bar
    
    Matrix M = lbm->invM() * Lambda * lbm->M();

    info.fields.Lambda = (c_scalar**)malloc( lbm->Q() * sizeof(c_scalar*));
    for(uint i = 0 ; i < lbm->Q() ; i++)
	info.fields.Lambda[i] = (c_scalar*)malloc( lbm->Q() * sizeof(c_scalar)); 
    
    for(uint i = 0 ; i < lbm->Q() ; i++) {
    	for(uint j = 0 ; j < lbm->Q() ; j++) {
    	    info.fields.Lambda[i][j] = M[i][j];
    	}
    }


    info.fields.invM = (c_scalar**)malloc( lbm->Q() * sizeof(c_scalar*));
    for(uint i = 0 ; i < lbm->Q() ; i++)
	info.fields.invM[i] = (c_scalar*)malloc( lbm->Q() * sizeof(c_scalar)); 
    
    // Model inverse matrix
    for(uint i = 0 ; i < lbm->Q() ; i++) {
    	for(uint j = 0 ; j < lbm->Q() ; j++) {
    	    info.fields.invM[i][j] = lbm->invM()[i][j];
    	}
    }
    




    // Read model
    string eosType = mp.lookUpEntry<string>("EOS/model");

    if( eosType.compare("idealGas") == 0 ) {
	
	info.fields._eosIdx = 0;

	info.fields._R = (c_scalar)mp.lookUpEntry<double>("EOS/R");

	info.fields._G = (c_scalar)mp.lookUpEntry<double>("EOS/G");
	
    }
    
    else {

	if( eosType.compare("Carnahan-Starling") == 0 ) {

	    info.fields._eosIdx = 1;

	    // Carnahan - Starling constants
    
	    info.fields._a = (c_scalar)mp.lookUpEntry<double>("EOS/a");
    
	    info.fields._b = (c_scalar)mp.lookUpEntry<double>("EOS/b");
    
	    info.fields._R = (c_scalar)mp.lookUpEntry<double>("EOS/R");

	    info.fields._T = (c_scalar)mp.lookUpEntry<double>("EOS/T");

	    info.fields._G = (c_scalar)mp.lookUpEntry<double>("EOS/G");
	    
	}

    }




    // Gravity
    Vector3 gravity = mp.lookUpEntry<Vector3>("f/g");
    info.fields._g[0] = gravity.x();
    info.fields._g[1] = gravity.y();
    info.fields._g[2] = gravity.z();




    // Temperature relaxation time
    info.fields.tau_T = (c_scalar)mp.lookUpEntry<double>("g/tau");    

    // Specific heat
    info.fields._Cv = (c_scalar)mp.lookUpEntry<double>("g/Cv");


    // Forcing scheme coefficients
    
    info.fields.sigma = (c_scalar)mp.lookUpEntry<double>("f/sigma");
    
    info.fields.tau_e = 1 / le[1];

    info.fields.tau_c = 1 / le[2];









    // MPI info

    info.parallel.nlocal = info.lattice.nlocal;
    
    info.parallel.pid = pid;
    info.parallel.worldSize = sz;

    // Read total ghost elements using globalGhostsIds
    fileName = latticeFolder.str() + "globalGhostsIds" ;
    
    inFile.open( fileName.c_str() );
    if( !inFile.is_open() ) {
    	std::cout << "Unable to open file " << fileName << std::endl;
    	exit(1);
    }
    
    inFile >> info.parallel.nghosts;
    
    inFile.close();



    // Read total send ghosts
    fileName = latticeFolder.str() + "sendMapIds" ;     
    inFile.open( fileName.c_str() );
    if( !inFile.is_open() ) {
    	std::cout << "Unable to open file " << fileName << std::endl;
    	exit(1);
    }
    inFile >> info.parallel.nSendGhosts;

    // Resize Send ghost ids
    info.parallel.sendGhostIds = (uint**)malloc( info.parallel.nSendGhosts * sizeof(unsigned int*) );  
    info.parallel.ssbuf = (c_scalar**)malloc( info.parallel.nSendGhosts * sizeof(c_scalar*) );
    

    for(uint i = 0 ; i < info.parallel.nSendGhosts ; i++) {
	
    	uint pid,nel;
    	inFile >> pid;
    	inFile >> nel;

    	info.parallel.sendGhostIds[i] = (uint*)malloc( (nel + 2) * sizeof(uint) );
    	info.parallel.ssbuf[i] = (c_scalar*)malloc( nel * sizeof(c_scalar) );

    	info.parallel.sendGhostIds[i][0] = pid;
    	info.parallel.sendGhostIds[i][1] = nel;

    	for(uint j = 0 ; j < nel ; j++) {
    	    inFile >> info.parallel.sendGhostIds[i][j+2];
    	}
	
    }

    inFile.close();
    


    // Compute scalar send blocks per process
    info.parallel.sendScalarBlocks = (int*)malloc( info.parallel.nSendGhosts * sizeof(int) );

    int nsb(0);
    
    for(uint i = 0 ; i < info.parallel.nSendGhosts ; i++) {

    	const int buffBlocks = ceil (1.0 * info.parallel.sendGhostIds[i][1] / MPI_BUFF_SIZE );
	
    	info.parallel.sendScalarBlocks[i] = buffBlocks;

    	nsb += buffBlocks * MPI_BUFF_SIZE;
	
    }

    // Resize send buffer
    info.parallel.scalarSendBuff = (c_scalar*)malloc( nsb * sizeof(c_scalar) );




    

    // Read total recv ghosts
    fileName = latticeFolder.str() + "recvMapIds" ;     
    inFile.open( fileName.c_str() );
    if( !inFile.is_open() ) {
    	std::cout << "Unable to open file " << fileName << std::endl;
    	exit(1);
    }
    inFile >> info.parallel.nRecvGhosts;

    // Resize Recv ghost ids
    info.parallel.recvGhostIds   = (uint**)malloc( info.parallel.nRecvGhosts * sizeof(uint*) );
    info.parallel.srbuf = (c_scalar**)malloc( info.parallel.nRecvGhosts * sizeof(c_scalar*) );
    
    for(uint i = 0 ; i < info.parallel.nRecvGhosts ; i++) {
	
    	uint pid,nel,aux;
    	inFile >> pid;
    	inFile >> nel;

    	info.parallel.recvGhostIds[i] = (uint*)malloc( (nel + 2) * sizeof(uint) );
    	info.parallel.srbuf[i] = (c_scalar*)malloc( nel * sizeof(c_scalar) );

    	info.parallel.recvGhostIds[i][0] = pid;
    	info.parallel.recvGhostIds[i][1] = nel;
	
    	for(uint j = 0 ; j < nel ; j++) {
    	    inFile >> info.parallel.recvGhostIds[i][j+2];
    	}

    	for(uint j = 0 ; j < nel ; j++) {
    	    inFile >> aux;
    	}

	
    }

    inFile.close();

    
    // Compute send blocks per process
    info.parallel.recvScalarBlocks = (int*)malloc( info.parallel.nRecvGhosts * sizeof(int) );

    int nrb(0);
    
    for(uint i = 0 ; i < info.parallel.nRecvGhosts ; i++) {

    	const int buffBlocks = ceil( 1.0 * info.parallel.recvGhostIds[i][1] / MPI_BUFF_SIZE );
	
    	info.parallel.recvScalarBlocks[i] = buffBlocks;

    	nrb += buffBlocks * MPI_BUFF_SIZE;
	
    }

    
    // Resize send buffer
    info.parallel.scalarRecvBuff = (c_scalar*)malloc( nrb * sizeof(c_scalar) );
   
    
    return info;
    
}


#ifdef __cplusplus
}
#endif
