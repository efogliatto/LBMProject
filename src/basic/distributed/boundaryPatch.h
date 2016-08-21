#ifndef BOUNDARYPATCH_H
#define BOUNDARYPATCH_H

#include <lbPatch.h>

template<typename T>
class boundaryPatch : public lbPatch<T> {


    /* ----------------------  Protected members ----------------------  */

protected:

    std::map<std::string, std::vector<uint> > _boundaryMap;




    /* ----------------------  Public members ----------------------  */

public:

    
    // Constructors and destructors


    // Constructor with reference to LBModel
    boundaryPatch( basicLBModel* lbm );

    // Constructor with reference to LBModel and local nodes size
    boundaryPatch( basicLBModel* lbm, const uint& sz );

    // Default destructor
    ~boundaryPatch();



    // Member modification
    
    // Set boundaryMap using global indexes
    const void setGlobalBdMap( const std::map<std::string, std::vector<uint> >& bdmap );

    // Set boundaryMap using local indexes
    const void setLocalBdMap( const std::string& bdName, const std::vector<uint>& bdIds );
    
    
    // Access to boundary elements
    const std::map<std::string, std::vector<uint> >& boundaryElements() const;


};



// Constructors and destructors


// Constructor with reference to LBModel
template<typename T>
boundaryPatch<T>::boundaryPatch( basicLBModel* lbm ) : lbPatch<T>( lbm ) {}


// Constructor with reference to LBModel and local size
template<typename T>
boundaryPatch<T>::boundaryPatch( basicLBModel* lbm, const uint& sz ) : lbPatch<T>(lbm,sz) {}


// Default destructor
template<typename T>
boundaryPatch<T>::~boundaryPatch() {}




// Set boundaryMap using global indexes
template<typename T>
const void boundaryPatch<T>::setGlobalBdMap( const std::map<std::string, std::vector<uint> >& bdmap ) {

    // Move over boundary map
    for( auto bmap : bdmap ) {

    	// Move over boundary global list
    	for( auto gid : bmap.second ) {

    	    // Check if element is in local
    	    for( uint i = 0 ; i < this->_globalId_localNodes.size() ; i++ ) {
		
    		if( this->_globalId_localNodes[i] == gid ) {

    		    this->_boundaryMap[bmap.first].push_back( i );

    		}

    	    }

    	}

    }

}





// Set boundaryMap using local indexes
template<typename T>
const void boundaryPatch<T>::setLocalBdMap( const std::string& bdName, const std::vector<uint>& bdIds ) {
    this->_boundaryMap[bdName] = bdIds;
}


// Access to boundary elements
template<typename T>
const std::map<std::string, std::vector<uint> >& boundaryPatch<T>::boundaryElements() const {
    return this->_boundaryMap;
}


#endif // BOUNDARYPATCH_H
