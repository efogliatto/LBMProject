#ifndef BASICPATCH_H
#define BASICPATCH_H

#include <vector>
#include <basicPatch_iterator.h>

template<typename T>
class basicPatch {

    
    /* ----------------------  Protected members ----------------------  */

protected:
    
    // Patch index
    uint _id;

    // Local elements
    std::vector<T> _localValues;

    // Swap elements. Used only for streamming
    std::vector<T> _swapValues;

    // Values form previous time steps. Useful for temporal derivatives
    std::vector<T> _oldValues;

    // Global indices for local elements
    std::vector<uint> _globalId_localNodes;

    
    
    

    /* ----------------------  Public members ----------------------  */    


public:

    // Constructors and destructors

    // Default constructor
    basicPatch();

    // Constructor with local size
    basicPatch(const uint& sz);

    // Default destructor
    ~basicPatch();



    // Member modification

    // Set index
    const void setId(const uint& id);

    // Resize local nodes container
    const void resize(const uint& sz);



    
    // Member access

    // Access to local element list (begin iterator)
    basicPatch_iterator<T> begin();

    // Access to local element list (end iterator)
    basicPatch_iterator<T> end();


    // Patch index 
    const uint& id() const;

    // Total number of local elements
    const uint& size() const;

    
    
};




// Default constructor
template<typename T>
basicPatch<T>::basicPatch() {}

// Constructor with local size
template<typename T>
basicPatch<T>::basicPatch(const uint& sz) {
    this->_localValues.resize( sz );
    this->_swapValues.resize( sz );
    this->_oldValues.resize( sz );
    this->_globalId_localNodes.resize( sz );
}

// Default destructor
template<typename T>
basicPatch<T>::~basicPatch() {}




// Member modification

// Set index
template<typename T>
const void basicPatch<T>::setId(const uint& id) {
    _id = id;
}



// Resize local nodes container
template<typename T>
const void basicPatch<T>::resize(const uint& sz) {
    this->_localValues.resize( sz );
    this->_swapValues.resize( sz );
    this->_oldValues.resize( sz );
    this->_globalId_localNodes.resize( sz );
}






// Access to local element list (begin iterator)
template<class T>
basicPatch_iterator<T> basicPatch<T>::begin(){
    return basicPatch_iterator<T>( _localValues.begin(),
				   _swapValues.begin(),
				   _oldValues.begin(),
				   _globalId_localNodes.begin(),
				   0
	);
}

// Access to local element list (end iterator)
template<class T>
basicPatch_iterator<T> basicPatch<T>::end(){
    return basicPatch_iterator<T>( _localValues.end(),
				   _swapValues.end(),
				   _oldValues.end(),
				   _globalId_localNodes.end(),
				   0
	);
}



// Local values size
template<typename T>
const uint& basicPatch<T>::size() const {
    return this->_localValues.size();
}



// Patch id
template<typename T>
const uint& basicPatch<T>::id() const {
    return this->_id;
}


#endif // BASICPATCH_H
