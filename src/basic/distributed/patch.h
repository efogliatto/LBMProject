#ifndef PATCH_H
#define PATCH_H

#include <node.h>
#include <vector>

template<typename T>
class patch {

    
    /* ----------------------  Protected members ----------------------  */

protected:
    
    // Patch index
    uint _id;

    // Local elements
    std::vector< node<T> > _localNodes;


    /* ----------------------  Public members ----------------------  */    


public:

    // Constructors and destructors

    // Default constructor
    patch();

    // Default destructor
    ~patch();



    // Member modification

    // Set index
    const void setId(const uint& id);

    // Add local node
    const void addLocal( const node<T>& n );

    // Add local node with index
    const void addLocal( const node<T>& n, const uint& id );    

    // Resize local nodes container
    const void resizeLocal(const uint& sz);



    
    // Member access

    // Patch index 
    const uint id() const;

    // Access to local element list (begin iterator)
    typename std::vector< node<T> >::const_iterator local_begin() const;

    // Access to local element list (end iterator)
    typename std::vector< node<T> >::const_iterator local_end() const;

    // Access to local element list (begin iterator)
    typename std::vector< node<T> >::iterator nodesBegin();

    // Access to local element list (end iterator)
    typename std::vector< node<T> >::iterator nodesEnd();

    // Access to local element list (end iterator)
    typename std::vector< node<T> >::iterator nodesAt(const int& id);    




    // Access to local element list (begin iterator)
    typename std::vector<T>::iterator localBegin();

    // Access to local element list (end iterator)
    typename std::vector<T>::iterator localEnd();
    
    
};






// Default constructor
template<typename T>
patch<T>::patch() {}

// Default destructor
template<typename T>
patch<T>::~patch() {}



// Member modification

// Set index
template<typename T>
const void patch<T>::setId(const uint& id) {
    _id = id;
}


// Add local node
template<typename T>
const void patch<T>::addLocal( const node<T>& n ) {

    // Add node to local list
    _localNodes.push_back( n );

    // Change patch id
    _localNodes.back().setPatchId( _id );

    /* // Change node local id */
    /* _localNodes.back().setLocalId( _localNodes.size() - 1 ); */
    
}



// Add local node with index
template<typename T>
const void patch<T>::addLocal( const node<T>& n, const uint& id ) {

    // Add node to local list
    _localNodes[id] = n;

    // Change patch id
    _localNodes[id].setPatchId( _id );
    
}






// Resize local nodes container
template<typename T>
const void patch<T>::resizeLocal(const uint& sz) {
    this->_localNodes.resize( sz );
}










// Access to local element list (begin iterator)
template<typename T>
typename std::vector< node<T> >::const_iterator patch<T>::local_begin() const{
    return _localNodes.begin();
}

/* // Access to local element list (end iterator) */
template<class T>
typename std::vector< node<T> >::const_iterator patch<T>::local_end() const{
    return _localNodes.end();
}


// Access to local element list (begin iterator)
template<class T>
typename std::vector< node<T> >::iterator patch<T>::nodesBegin(){
    return this->_localNodes.begin();
}

// Access to local element list (end iterator)
template<class T>
typename std::vector< node<T> >::iterator patch<T>::nodesEnd()  {
    return this->_localNodes.end();
}

// Access to local element list (end iterator)
template<class T>
typename std::vector< node<T> >::iterator patch<T>::nodesAt(const int& id) {
    return this->_localNodes.begin() + id;    
}





// Access to local element list (begin iterator)
template<class T>
typename std::vector<T>::iterator patch<T>::localBegin(){
    return this->_local.begin();
}

// Access to local element list (end iterator)
template<class T>
typename std::vector<T>::iterator patch<T>::localEnd()  {
    return this->_local.end();
}


#endif // PATCH_H
