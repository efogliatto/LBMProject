#ifndef MPIPATCH_H
#define MPIPATCH_H

#include <IOPatch.h>
#include <boost/mpi/environment.hpp>
#include <boost/mpi/communicator.hpp>
#include <boost/serialization/vector.hpp>
#include <boost/mpi/nonblocking.hpp>
#include <boost/mpi/skeleton_and_content.hpp>

// MPI namespace
namespace mpi = boost::mpi;


template<typename T>
class mpiPatch : public IOPatch<T> {

    
    
    /* ----------------------  Protected members ----------------------  */

protected:

    // Reference to mpi::environment
    mpi::environment& _env;

    // Reference to mpi::comunicator
    mpi::communicator& _world;
    
    
    
    /* ----------------------  Public members ----------------------  */

public:

    
    // Constructors and destructors

    // Constructor with reference to LBModel
    mpiPatch( basicLBModel* lbm, mpi::environment& env, mpi::communicator& world );

    // Constructor with reference to LBModel and local nodes size
    mpiPatch( basicLBModel* lbm, const uint& sz, mpi::environment& env, mpi::communicator& world );

    // Default destructor
    ~mpiPatch();




    // Member modification

    // Read values
    const void readValues(const std::string& fileName, const std::string& folderName);

    // Read values
    const void readValues(const std::string& fileName, const double& timeFolder);

    

    // Member synchronization
    
    // Sync send and recv skeletons
    const void syncSkeletons();

    // Sync send and recv values
    const void syncGhostValues();


    // Member access

    // Write values to time folder
    const void writeValues(const std::string& fileName, const double& timeFolder);    
    
    
};


// Constructors and destructors


// Constructor with reference to LBModel
template<typename T>
mpiPatch<T>::mpiPatch( basicLBModel* lbm, mpi::environment& env, mpi::communicator& world ) : IOPatch<T>( lbm ),  _env(env),  _world(world) {

    // Fix id 
    this->_id = _world.rank();



    
    // Read structure

    std::ostringstream folderName;
    folderName << "processor" << this->_id << "/" << this->_lbm->name() << "_lattice" ;
    
    // Neighbours
    IOPatch<T>::readNeighboursIds(  "neighbours", folderName.str() );

    // Global Ids, local nodes
    IOPatch<T>::readGlobalIdLocal(  "globalIds", folderName.str() );	

    // Global indices, ghost nodes
    IOPatch<T>::readGlobalIdGhost(  "globalGhostsIds", folderName.str() );

    // neighbour linked list
    IOPatch<T>::setNeighLinkedList();	

    // Recv map indices
    IOPatch<T>::readRecvMapsIds(  "recvMapIds", folderName.str() );

    // Send map indices
    IOPatch<T>::readSendMapsIds(  "sendMapIds", folderName.str() );

    /* // Boundaries indices */
    /* IOPatch<T>::readBoundariesIds(  "boundary", folderName.str() );     */

}


// Constructor with reference to LBModel and local size
template<typename T>
mpiPatch<T>::mpiPatch( basicLBModel* lbm, const uint& sz, mpi::environment& env, mpi::communicator& world ) : IOPatch<T>(lbm,sz),  _env(env),  _world(world) { this->_id = _world.rank(); }


// Default destructor
template<typename T>
mpiPatch<T>::~mpiPatch() {}






// Read values
template<typename T>
const void mpiPatch<T>::readValues(const std::string& fileName, const std::string& folderName) {

    std::ostringstream fldName;
    fldName << "processor" << this->_id << "/" << folderName;
    
    // Call base method
    IOPatch<T>::readLocalValues( fileName, fldName.str() );
    
}



// Read values from time folder
template<typename T>
const void mpiPatch<T>::readValues(const std::string& fileName, const double& timeFolder) {

    std::ostringstream fldName;
    fldName << "processor" << this->_id << "/" << timeFolder;
    
    // Call base method
    IOPatch<T>::readLocalValues( fileName, fldName.str() );
    
}







// Write values from time folder
template<typename T>
const void mpiPatch<T>::writeValues(const std::string& fileName, const double& timeFolder) {

    std::ostringstream fldName;
    fldName << "processor" << this->_id << "/" << timeFolder;
    
    // Call base method
    IOPatch<T>::writeLocalValues( fileName, fldName.str() );
    
}





// Sync send and recv skeletons
template<typename T>
const void mpiPatch<T>::syncSkeletons() {

    // MPI barrier
    this->_world.barrier();

    // Requests
    std::vector<mpi::request> reqs;
  
    for(int tid = 0 ; tid < this->_world.size() ; tid++) {
    	if( tid != this->_world.rank() ) {

    	    // Send request
    	    reqs.push_back(   this-> _world.isend( tid, _world.rank(),  mpi::skeleton( this->_ghostSendMap[tid] ) )    );
	   
    	    // Receive request
    	    reqs.push_back(   this->_world.irecv( tid, tid,  mpi::skeleton( this->_ghostRecvMap[tid] ) )   );

    	}
	
    }


    // Wait all requests
    wait_all(reqs.begin(), reqs.end() );
    
}



// Sync send and recv
template<typename T>
const void mpiPatch<T>::syncGhostValues() {


    // MPI barrier
    this->_world.barrier();
  

    // Non blocking communications
    std::vector<mpi::request> reqs;
    
    for(int tid = 0 ; tid < this->_world.size() ; tid++) {
    	if( tid != this->_world.rank() ) {

    	    // Send request
    	    this->updateSendMap(tid);
    	    reqs.push_back( this->_world.isend(tid, this->_world.rank(), this->_ghostSendMap[tid] )  );
	    
    	    // Receive request
    	    reqs.push_back(  this->_world.irecv(tid, tid, this->_ghostRecvMap[tid])  );

    	}
	
    }


    // Wait all requests
    wait_all(reqs.begin(), reqs.end() );
    

    // Update ghost nodes
    for(int tid = 0 ; tid < _world.size() ; tid++) {
    	if( tid != _world.rank() ) {
    	    this->updateRecvMap( tid );
    	}
	
    }
    
    
}



#endif // MPIPATCH_H
