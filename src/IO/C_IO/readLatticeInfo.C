// Read information for c-written solvers

#include <dictionary.h>
#include <LBModelCreator.h>
#include <fstream>
#include <readLatticeInfo.h>
#include <scalars_C.h>

#ifdef __cplusplus
extern "C" {
#endif


    struct latticeInfo readLatticeInfo( struct timeInfo* t_info, int pid ) {

	struct latticeInfo info;


	// Read lattice properties
	dictionary lp("properties/latticeProperties");

	// DqQq Model
	LBModelCreator creator;
	basicLBModel* lbm = creator.create( lp.lookUpEntry<string>("LBModel") );

	// Basic lattice properties
	info.size = (double)lp.lookUpEntry<double>("latticeSize");
	info.c = info.size / t_info->tstep; 
	info.cs2 = info.c * info.c * lbm->cs2(); 
	info.d = lbm->D();
	info.Q = lbm->Q();



    
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
    
	inFile >> info.nlocal;

	inFile.close();



	// Lattice weights
	const vector<double> omega = lbm->omega();
	info.omega = (c_scalar*)malloc( lbm->Q() * sizeof(c_scalar));
	for(uint i = 0 ; i < lbm->Q() ; i++)
	    info.omega[i] = omega[i];


	// Lattice reverse indices
	info.reverse = (int*)malloc( lbm->Q() * sizeof(int));
	for(uint i = 0 ; i < lbm->Q() ; i++)
	    info.reverse[i] = lbm->reverse(i);
    

	// Lattice velocities
	const vector<Vector3> vel = lbm->latticeVel();
	info.vel = (int**)malloc( lbm->Q() * sizeof(int*));
	for(uint i = 0 ; i < lbm->Q() ; i++)
	    info.vel[i] = (int*)malloc( 3 * sizeof(int));

	for(uint i = 0 ; i < lbm->Q() ; i++) {
	    info.vel[i][0] = (int)vel[i].x();
	    info.vel[i][1] = (int)vel[i].y();
	    info.vel[i][2] = (int)vel[i].z();
	}


	// Pseudopotential weights
	const vector<double> weights = lbm->weights();
	info.weights = (c_scalar*)malloc( lbm->Q() * sizeof(c_scalar));
	for(uint i = 0 ; i < lbm->Q() ; i++)
	    info.weights[i] = weights[i];
    
    
   
    
	return info;
    
    }


#ifdef __cplusplus
}
#endif
