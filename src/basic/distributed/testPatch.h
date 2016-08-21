#ifndef TESTPATCH_H
#define TESTPATCH_H

#include <vector>

template<typename T>
class testPatch {

    
    /* ----------------------  Protected members ----------------------  */

protected:
    
    // Patch index
    uint _id;

    // Local elements
    std::vector<T> _local;


    /* ----------------------  Public members ----------------------  */    


public:

    // Constructors and destructors

    // Default constructor
    testPatch();

    // Default destructor
    ~testPatch();



    // Member modification

    // Set index
    const void setId(const uint& id);

    // Resize local nodes container
    const void resizeLocal(const uint& sz);



    
    // Member access

    // Patch index 
    const uint id() const;

    // Access to local element list (begin iterator)
    typename std::vector<T>::iterator localBegin();

    // Access to local element list (end iterator)
    typename std::vector<T>::iterator localEnd();
    
    
};






// Default constructor
template<typename T>
testPatch<T>::testPatch() {}

// Default destructor
template<typename T>
testPatch<T>::~testPatch() {}



// Member modification

// Set index
template<typename T>
const void testPatch<T>::setId(const uint& id) {
    _id = id;
}


// Resize local nodes container
template<typename T>
const void testPatch<T>::resizeLocal(const uint& sz) {
    this->_local.resize( sz );    
}






// Access to local element list (begin iterator)
template<class T>
typename std::vector<T>::iterator testPatch<T>::localBegin(){
    return this->_local.begin();
}

// Access to local element list (end iterator)
template<class T>
typename std::vector<T>::iterator testPatch<T>::localEnd()  {
    return this->_local.end();
}


#endif // TESTPATCH_H
