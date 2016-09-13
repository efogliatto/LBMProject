// Read information for c-written solvers

#include <basicSolverInfo.h>
#include <dictionary.h>
#include <LBModelCreator.h>
#include <fstream>
#include <readBasicInfo.h>

#ifdef __cplusplus
extern "C" {
#endif


    struct solverInfo readBasicInfo( int pid, int sz ) {

    struct solverInfo info;

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
    
    

    // Read macroscopic properties
    dictionary mp("properties/macroscopicProperties");

    pdf Sh = mp.lookUpEntry<pdf>("h/S");

    info.fields.colMat = (c_scalar**)malloc( lbm->Q() * sizeof(c_scalar*));
    for(uint i = 0 ; i < lbm->Q() ; i++)
	info.fields.colMat[i] = (c_scalar*)malloc( lbm->Q() * sizeof(c_scalar));

    Matrix SS( Sh.size() );
    for(uint i = 0 ; i < Sh.size() ; i++)
	SS[i][i] = Sh[i];

    Matrix M = lbm->invM() * SS * lbm->M();

    for(uint i = 0 ; i < lbm->Q() ; i++) {
	for(uint j = 0 ; j < lbm->Q() ; j++) {
	    info.fields.colMat[i][j] = M[i][j];
	}
    }
    

    info.fields.srcMat = (c_scalar**)malloc( lbm->Q() * sizeof(c_scalar*));
    for(uint i = 0 ; i < lbm->Q() ; i++)
	info.fields.srcMat[i] = (c_scalar*)malloc( lbm->Q() * sizeof(c_scalar));    

    for(uint i = 0 ; i < Sh.size() ; i++)
	SS[i][i] = 1.0 - (0.5 * Sh[i]);

    M = lbm->invM() * SS * lbm->M();

    for(uint i = 0 ; i < lbm->Q() ; i++) {
	for(uint j = 0 ; j < lbm->Q() ; j++) {
	    info.fields.srcMat[i][j] = M[i][j];
	}
    }
    


    pdf Sg_a = mp.lookUpEntry<pdf>("g/S_a");
    
    info.fields.colMatA = (c_scalar**)malloc( lbm->Q() * sizeof(c_scalar*));
    for(uint i = 0 ; i < lbm->Q() ; i++)
	info.fields.colMatA[i] = (c_scalar*)malloc( lbm->Q() * sizeof(c_scalar));

    for(uint i = 0 ; i < Sg_a.size() ; i++)
	SS[i][i] = Sg_a[i];

    M = lbm->invM() * SS * lbm->M();

    for(uint i = 0 ; i < lbm->Q() ; i++) {
	for(uint j = 0 ; j < lbm->Q() ; j++) {
	    info.fields.colMatA[i][j] = M[i][j];
	}
    }
    
    
    info.fields.srcMatA = (c_scalar**)malloc( lbm->Q() * sizeof(c_scalar*));
    for(uint i = 0 ; i < lbm->Q() ; i++)
	info.fields.srcMatA[i] = (c_scalar*)malloc( lbm->Q() * sizeof(c_scalar));    

    for(uint i = 0 ; i < Sg_a.size() ; i++)
	SS[i][i] = 1.0 - (0.5 * Sg_a[i]);

    M = lbm->invM() * SS * lbm->M();

    for(uint i = 0 ; i < lbm->Q() ; i++) {
	for(uint j = 0 ; j < lbm->Q() ; j++) {
	    info.fields.srcMatA[i][j] = M[i][j];
	}
    }
    

    
    pdf Sg_b = mp.lookUpEntry<pdf>("g/S_b");

    info.fields.colMatB = (c_scalar**)malloc( lbm->Q() * sizeof(c_scalar*));
    for(uint i = 0 ; i < lbm->Q() ; i++)
	info.fields.colMatB[i] = (c_scalar*)malloc( lbm->Q() * sizeof(c_scalar));

    for(uint i = 0 ; i < Sg_b.size() ; i++)
	SS[i][i] = Sg_b[i];

    M = lbm->invM() * SS * lbm->M();

    for(uint i = 0 ; i < lbm->Q() ; i++) {
	for(uint j = 0 ; j < lbm->Q() ; j++) {
	    info.fields.colMatB[i][j] = M[i][j];
	}
    }
    
    info.fields.srcMatB = (c_scalar**)malloc( lbm->Q() * sizeof(c_scalar*));
    for(uint i = 0 ; i < lbm->Q() ; i++)
	info.fields.srcMatB[i] = (c_scalar*)malloc( lbm->Q() * sizeof(c_scalar));    


    for(uint i = 0 ; i < Sg_b.size() ; i++)
	SS[i][i] = 1.0 - (0.5 * Sg_b[i]);

    M = lbm->invM() * SS * lbm->M();

    for(uint i = 0 ; i < lbm->Q() ; i++) {
	for(uint j = 0 ; j < lbm->Q() ; j++) {
	    info.fields.srcMatB[i][j] = M[i][j];
	}
    }
    

    info.fields.sigma = (c_scalar)mp.lookUpEntry<double>("h/sigma");
    
    info.fields.D = (c_scalar)mp.lookUpEntry<double>("h/D");
    
    info.fields.phi_A = (c_scalar)mp.lookUpEntry<double>("Macro/phi_A");

    info.fields.phi_B = (c_scalar)mp.lookUpEntry<double>("Macro/phi_B");

    info.fields.M_phi = (c_scalar)mp.lookUpEntry<double>("Macro/M_phi");

    info.fields.rho_A = (c_scalar)mp.lookUpEntry<double>("Macro/rho_A");
    
    info.fields.rho_B = (c_scalar)mp.lookUpEntry<double>("Macro/rho_B");

    Vector3 g = mp.lookUpEntry<Vector3>("g/G");

    info.fields.gx = g.x();
    info.fields.gy = g.y();
    info.fields.gz = g.z();
    
    
    info.fields.eta = info.fields.M_phi / (   info.lattice.cs2 * info.time.tstep * (1/Sh[3] - 0.5)   );

    info.fields.kappa = 3 * info.fields.sigma * info.fields.D / (2 * (info.fields.phi_A - info.fields.phi_B) * (info.fields.phi_A - info.fields.phi_B));
    
    info.fields.beta  = 12 * info.fields.sigma / ( info.fields.D * pow(info.fields.phi_A - info.fields.phi_B, 4));    








    // MPI info

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
