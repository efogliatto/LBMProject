#ifndef LBPATCH_H
#define LBPATCH_H

#include <basicPatch.h>
#include <basicLBModel.h>
#include <fstream>
#include <algorithm>
#include <map>
#include <lbPatch_iterator.h>


template<typename T>
class lbPatch : public basicPatch<T> {
    

/*     /\* ----------------------  Private members ----------------------  *\/ */

/* private: */

/*     // Create neighbour linked list */
/*     const void setNeighLinkedList(); */



    
    /* ----------------------  Protected members ----------------------  */

protected:

    // Neighbour indices. LOCAL INDEXING
    std::vector< std::vector<int> > _neighbours;
        
    // LBmodel reference
    basicLBModel* _lbm;

    // Ghost elements
    std::vector<T> _ghostValues;

    // Global indices for ghost elements
    std::vector<uint> _globalId_ghostNodes;

    // Neighbour linked list
    std::vector<  std::vector< std::pair<uint, T*> >  > _neighLinkedList;

    

    

    /* ----------------------  Public members ----------------------  */

public:

    
    // Constructors and destructors


    // Constructor with reference to LBModel
    lbPatch( basicLBModel* lbm );

    // Constructor with reference to LBModel and local nodes size
    lbPatch( basicLBModel* lbm, const uint& sz );

    // Default destructor
    ~lbPatch();



    // Member modification

    // Set neighbour. Parameter must contain global indices. patchId indicates which patch is owner 
    const void setGlobalNeighbours( const std::vector< std::vector<int> >& nb, const std::vector<uint>& patchId );
    
    // Set neighbour. Uses local indexing. No checking, only assigment (useful when reading from file)
    const void setLocalNeighbours( const std::vector< std::vector<int> >& nb, const std::vector<uint>& ghostId );

    // Resize neighbour indices container
    const void resize(const uint& sz);

    // Create neighbour linked list
    const void setNeighLinkedList();    

    // Set local and ghost values
    const void setValues( const typename std::vector<T>& val );
    

    
    // Member access
    
    // Access to model
    basicLBModel* lbmodel();

    // Neighbour list. Local indexing
    const std::vector< std::vector<int> >& neighbours() const;

    // Neighbour list. Global indexing
    const std::vector< std::vector<int> > neighbours_globalId() const;





    // Access using iterators

    // Access to local element list (begin iterator)
    lbPatch_iterator<T> begin();

    // Access to local element list (end iterator)
    lbPatch_iterator<T> end();

    // Access to ghost element list (begin iterator)
    typename std::vector<T>::iterator ghostBegin();

    // Access to ghost element list (end iterator)
    typename std::vector<T>::iterator ghostEnd();
    
    // Neighbour access. Begin
    typename std::vector< std::pair<uint, T*> >::iterator neigh_begin( basicPatch_iterator<T>& it );

    // Neighbour access. End
    typename std::vector< std::pair<uint, T*> >::iterator neigh_end( basicPatch_iterator<T>& it );

    
};





// Constructors and destructors


// Constructor with reference to LBModel
template<typename T>
lbPatch<T>::lbPatch( basicLBModel* lbm ) : basicPatch<T>() {

    // Assign model
    _lbm = lbm;
    
}

// Constructor with reference to LBModel and local size
template<typename T>
lbPatch<T>::lbPatch( basicLBModel* lbm, const uint& sz ) : basicPatch<T>(sz) {

    // Assign model
    _lbm = lbm;

    // Resize neighbour vector
    this->_neighbours.resize( sz );
    for(uint i = 0 ; i < this->_neighbours.size() ; i++) {
	this->_neighbours[i].resize( this->_lbm->Q(), -1 );
    }
    
}

// Default destructor
template<typename T>
lbPatch<T>::~lbPatch() {}






// Set neighbour. Parameter must contain global indices

template<typename T>
const void lbPatch<T>::setGlobalNeighbours( const std::vector< std::vector<int> >& nb, const std::vector<uint>& patchId ) {

    /*

      nb must contain global indexing
      patchId[i] indicates who is the owner of node i

    */


    // Count total number of local elements
    uint count(0);
    for(std::vector<uint>::const_iterator pid = patchId.begin() ; pid != patchId.end() ; pid++) {
	if( (*pid) == this->_id ) {
	    count++;
	}
    }
	

    // Resize containers
    this->resize( count );

	
    // Assign local_to_global, and global_to_local indices
    std::map<uint, uint> _globalToLocal;
    {
	uint lid(0);
	    
	for(uint gid = 0 ; gid < nb.size() ; gid++) {

	    if(patchId[gid] == this->_id) {

		// Local to global
		this->_globalId_localNodes[lid] = gid;

		// Global to local
		_globalToLocal[gid] = lid;

		lid++;
		    
	    }

	}
    }



    // Move over local indices only
    {

	std::map<uint, uint> _globalGhostToLocal;
	    
	for(uint lid = 0 ; lid < this->_globalId_localNodes.size() ; lid++) {

	    // Global id for local node
	    uint gid = this->_globalId_localNodes[lid];

	    // Mover over lbm velocities
	    for(uint velId = 0 ; velId < nb[gid].size() ; velId++){

		// Neighbour global index
		int neighId = nb[gid][velId];

		// No neighbour
		if(neighId == -1) {
		    
		    this->_neighbours[lid][velId] = neighId;
		    
		}

		else {

		    // Neighbour is local to this patch
		    if( _globalToLocal.find(neighId) != _globalToLocal.end() ) {

			this->_neighbours[lid][velId] = _globalToLocal[neighId];
			
		    }

		    // Neighbour belongs to other patch
		    else {

			// Not loaded
			if( _globalGhostToLocal.find( neighId ) == _globalGhostToLocal.end() ) {

			    _globalGhostToLocal[neighId] = this->_localValues.size() + _globalGhostToLocal.size() - 1;

			    this->_globalId_ghostNodes.push_back( neighId );
			    
			}
			
			this->_neighbours[lid][velId] = _globalGhostToLocal[neighId];
			
			
		    }
		    
		}
		
	    }
	    
	}


	// Resize Ghost values container
	this->_ghostValues.resize( _globalGhostToLocal.size() );
	    
    }
	


    // Assign linked list
    setNeighLinkedList();

}







// Set neighbour. Uses local indexing. No checking, only assigment (useful when reading from file)
template<typename T>
const void lbPatch<T>::setLocalNeighbours( const std::vector< std::vector<int> >& nb, const std::vector<uint>& ghostId ) {

    this->_neighbours = nb;

    this->_globalId_ghostNodes = ghostId;
    this->_ghostValues.resize( ghostId.size() );

}









// Member access
    
// Access to model
template<typename T>
basicLBModel* lbPatch<T>::lbmodel() {
    return _lbm;
}



// Resize neighbour indices container
template<typename T>
const void lbPatch<T>::resize(const uint& sz)  {

    // Call base method
    basicPatch<T>::resize(sz);

    // Resize neighbour list
    this->_neighbours.resize( sz );
    for(uint i = 0 ; i < this->_neighbours.size() ; i++) {
	this->_neighbours[i].resize( this->_lbm->Q(), -1 );
    }    
}




// Neighbour list. Local indexing
template<typename T>
const std::vector< std::vector<int> >& lbPatch<T>::neighbours() const {
    return this->_neighbours;
}


// Neighbour list. Global indexing
template<typename T>
const std::vector< std::vector<int> > lbPatch<T>::neighbours_globalId() const {

    // Global list
    std::vector< std::vector<int> > global( this->_neighbours.size() );
    for(uint i = 0 ; i < this->_neighbours.size() ; i++) {
	global[i].resize( this->_lbm->Q() );
    }

    // Move over indices and assign global values
    for(uint i = 0 ; i < global.size() ; i++) {
	for(uint j = 0 ; j < this->_lbm->Q() ; j++) {
	    
	    int neighId = this->_neighbours[i][j];

	    if(neighId == -1) {
		
		global[i][j] = -1;
		
	    }

	    else {

		if( (uint)neighId < this->_neighbours.size()) {

		    global[i][j] = this->_globalId_localNodes[neighId];
		    
		}

		else {

		    global[i][j] = this->_globalId_ghostNodes[neighId - this->_neighbours.size() ];
		    
		}
		
	    }
	    
	}
    }
    
    
    return global;
}






// Create neighbour linked list
template<typename T>
const void lbPatch<T>::setNeighLinkedList() {

    // Resize linked list
    this->_neighLinkedList.resize( this->_neighbours.size() );

    // Move over neighbours and assign references
    for(uint lid = 0 ; lid < this->_neighbours.size() ; lid++) {

	// Move over lattice velocities
	for(uint velId = 0 ; velId < this->_lbm->Q() ; velId++) {

	    int neighId = this->_neighbours[lid][velId];

	    if( neighId != -1) {

		if( neighId < (int)this->_neighbours.size() ) {

		    this->_neighLinkedList[lid].push_back( std::make_pair(velId, &this->_localValues[neighId]) );

		}

		else {

		    neighId = neighId - this->_neighbours.size();

		    this->_neighLinkedList[lid].push_back( std::make_pair(velId, &this->_ghostValues[neighId]) );

		}

	    }

	}

    }


}





// Neighbour access using iterators

// Begin
template<typename T>
typename std::vector< std::pair<uint, T*> >::iterator lbPatch<T>::neigh_begin( basicPatch_iterator<T>& it ) {
    return this->_neighLinkedList[ it.localId() ].begin();
}

// End
template<typename T>
typename std::vector< std::pair<uint, T*> >::iterator lbPatch<T>::neigh_end( basicPatch_iterator<T>& it ) {
    return this->_neighLinkedList[ it.localId() ].end();
}




// Access to local element list (begin iterator)
template<class T>
lbPatch_iterator<T> lbPatch<T>::begin(){
    return lbPatch_iterator<T>( basicPatch<T>::begin(), this->_neighLinkedList.begin() );
}

// Access to local element list (end iterator)
template<class T>
lbPatch_iterator<T> lbPatch<T>::end(){
    return lbPatch_iterator<T>( basicPatch<T>::end(), this->_neighLinkedList.end() );
}


// Access to ghost element list (begin iterator)
template<class T>
typename std::vector<T>::iterator lbPatch<T>::ghostBegin(){
    return this->_ghostValues.begin();
}

// Access to ghost element list (end iterator)
template<class T>
typename std::vector<T>::iterator lbPatch<T>::ghostEnd(){
    return this->_ghostValues.end();
}




// Set local and ghost values
template<class T>
const void lbPatch<T>::setValues( const typename std::vector<T>& val ) {

    // Move over local elements
    for(uint lid = 0 ; lid < this->_globalId_localNodes.size() ; lid++)
	this->_localValues[lid] = val[ this->_globalId_localNodes[lid] ];

    // Move over ghost elements
    for(uint gid = 0 ; gid < this->_globalId_ghostNodes.size() ; gid++)
	this->_ghostValues[gid] = val[ this->_globalId_ghostNodes[gid] ];    
    
}



#endif // LBPATCH_H
