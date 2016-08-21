#ifndef COMMPATCH_H
#define COMMPATCH_H

#include <boundaryPatch.h>

template<typename T>
class commPatch : public boundaryPatch<T> {

    
    /* ----------------------  Protected members ----------------------  */

protected:    


    // Maps to save links between node values. Local indices for ghost values( absolute position in _ghostValues ), useful when reading from file.

    // Values to be received (ghost nodes in this patch). _ghostMapValues
    std::map<uint, std::vector<uint> > _ghostRecvId;

    // Values to be sent (local nodes from this patch, that are ghost in other patches). _otherPatchGhostMap values
    std::map<uint, std::vector<uint> > _ghostSendId;
    
    
    
    // Maps to save links between node values

    // Values to be received (ghost nodes in this patch). _ghostMapValues
    std::map<uint, std::vector<T> > _ghostRecvMap;

    // Values to be sent (local nodes from this patch, that are ghost in other patches). _otherPatchGhostMap values
    std::map<uint, std::vector<T> > _ghostSendMap;


    // Auxiliary map. Global indices needed for other patch in order to create the _ghostSendMaps
    std::map<uint, std::vector<uint> > _ghostRecvMap_globalId;


    

    /* ----------------------  Public members ----------------------  */

public:

    
    // Constructors and destructors


    // Constructor with reference to LBModel
    commPatch( basicLBModel* lbm );

    // Constructor with reference to LBModel and local nodes size
    commPatch( basicLBModel* lbm, const uint& sz );

    // Default destructor
    ~commPatch();

    

    // Member modification

    // Set neighbour. Parameter must contain global indices. patchId indicates which patch is owner 
    const void setGlobalNeighbours( const std::vector< std::vector<int> >& nb, const std::vector<uint>& patchId );    

    // Global indices for receiving ghost nodes
    const std::vector<uint>& ghostRecvGId( const uint& pid ) const;

    // Create send map
    const void setSendMap( const uint& pid, const std::vector<uint> gids );

    // Send ghost values
    const std::vector<T>& sendGhostValues( const uint& pid );

    // Receive ghost values
    const void recvGhostValues( const uint& pid, const std::vector<T>& recv );

    // Set recv maps with local ids
    const void setRecvLocalMaps(const uint& pid, const std::vector<uint>& lid, const std::vector<uint>& gid);

    // Set send maps with local ids
    const void setSendLocalMaps(const uint& pid, const std::vector<uint>& lid);

    // Update send map values
    const void updateSendMap( const uint& pid );

    // Update recv map values
    const void updateRecvMap( const uint& pid );    
    
};







// Constructors and destructors

// Constructor with reference to LBModel
template<typename T>
commPatch<T>::commPatch( basicLBModel* lbm ) : boundaryPatch<T>( lbm ) {}


// Constructor with reference to LBModel and local size
template<typename T>
commPatch<T>::commPatch( basicLBModel* lbm, const uint& sz ) : boundaryPatch<T>( lbm, sz) {}


// Default destructor
template<typename T>
commPatch<T>::~commPatch() {}





// Member modification

// Set neighbour. Parameter must contain global indices
template<typename T>
const void commPatch<T>::setGlobalNeighbours( const std::vector< std::vector<int> >& nb, const std::vector<uint>& patchId ) {

    
    // Call base method
    lbPatch<T>::setGlobalNeighbours(nb, patchId);


    // Link elements to be received (from _ghostValues)

    // Move over ghost elements
    for(uint id = 0 ; id < this->_ghostValues.size() ; id++) {

	// Ghost value global id
	uint gh_gid = this->_globalId_ghostNodes[id];

	// Check patch ownership
	uint pid = patchId[gh_gid];

	// Add reference to map
	this->_ghostRecvMap[pid].push_back( this->_ghostValues[id] );

	// Add local index to map
	this->_ghostRecvId[pid].push_back( id );

	// Add index to map
	this->_ghostRecvMap_globalId[pid].push_back( gh_gid );

    }

    
    
}





// Global indices for receiving ghost nodes
template<typename T>
const std::vector<uint>& commPatch<T>::ghostRecvGId( const uint& pid ) const {

    std::vector<uint> a;
    
    if( this->_ghostRecvMap_globalId.find(pid) != this->_ghostRecvMap_globalId.end() ) {
	return this->_ghostRecvMap_globalId.at( pid );
    }

    else {
	return a;
    }
    
}



// Create send map
template<typename T>
const void commPatch<T>::setSendMap( const uint& pid, const std::vector<uint> gids ) {

    // Move over global ids and create references
    for(uint gid = 0 ; gid < gids.size() ; gid++) {

	// Move over _localValues and check matching
	for(uint lid = 0 ; lid < this->_globalId_localNodes.size() ; lid++) {

	    if( this->_globalId_localNodes[lid] == gids[gid] ) {

		// Add value to map
		this->_ghostSendMap[pid].push_back( this->_localValues[lid] );

		// Add index to map
		this->_ghostSendId[pid].push_back( lid );
		
	    }

	}
	
    }
    
}




// Send ghost values
template<typename T>
const std::vector<T>& commPatch<T>::sendGhostValues( const uint& pid ) {

    // Update send ghost map and return
    updateSendMap(pid);

    return this->_ghostSendMap.at(pid);


    
    /* std::vector<T> _send( this->_ghostSendMap.at(pid).size() ); */

    /* for(uint i = 0 ; i < this->_ghostSendMap.at(pid).size() ; i++) { */

    /* 	_send[i] = this->_ghostSendMap.at(pid)[i]; */
	
    /* } */

    /* return _send; */
    
}




// Receive ghost values
template<typename T>
const void commPatch<T>::recvGhostValues( const uint& pid, const std::vector<T>& recv ) {

    for(uint i = 0 ; i < recv.size() ; i++) {
	this->_ghostRecvMap.at(pid)[i] = recv[i];
    }

    // Update values
    for(uint i = 0 ; i < this->_ghostRecvId[pid].size() ; i++) {
	this->_ghostValues[ this->_ghostRecvId[pid][i] ] = recv[i];
    }    
	
}






// Set recv maps with local ids
template<typename T>
const void commPatch<T>::setRecvLocalMaps(const uint& pid, const std::vector<uint>& lid, const std::vector<uint>& gid) {

    // Add local indices to map
    this->_ghostRecvId[pid] = lid;

    // Add index to map
    this->_ghostRecvMap_globalId[pid] = gid;

    // Add references to map
    for(uint i = 0 ; i < lid.size() ; i++) {

	this->_ghostRecvMap[pid].push_back( this->_ghostValues[ lid[i] ] );

    }

}



// Set send maps with local ids
template<typename T>
const void commPatch<T>::setSendLocalMaps(const uint& pid, const std::vector<uint>& lid) {

    // Add local indices to map
    this->_ghostSendId[pid] = lid;

    
    // Add references to map
    for(uint i = 0 ; i < lid.size() ; i++) {

	// Add reference to map
	this->_ghostSendMap[pid].push_back( this->_localValues[ lid[i] ] );

    }

}




// Update send map values
template<typename T>
const void commPatch<T>::updateSendMap( const uint& pid ) {

    for(uint i = 0 ; i < this->_ghostSendMap.at(pid).size() ; i++) {

    	this->_ghostSendMap[pid][i] = this->_localValues[ this->_ghostSendId.at(pid)[i] ];

    }

}



// Update send map values
template<typename T>
const void commPatch<T>::updateRecvMap( const uint& pid ) {

    for(uint i = 0 ; i < this->_ghostRecvId[pid].size() ; i++) {
	
	this->_ghostValues[ this->_ghostRecvId[pid][i] ] = this->_ghostRecvMap[pid][i];
	
    }    

}



#endif // COMMPATCH_H
