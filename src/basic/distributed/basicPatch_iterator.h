#ifndef BASICPATCH_ITERATOR_H
#define BASICPATCH_ITERATOR_H

#include <scalars.h>
#include <Vector3.h>
#include <pdf.h>

template<typename T>
class basicPatch_iterator {

    
    /* ----------------------  Protected members ----------------------  */

protected:

    // Local nodes iterator
    typename std::vector<T>::iterator _localNodes_it;

    // Swap elements iterator
    typename std::vector<T>::iterator _swapValue_it;

    // Values form previous time steps iterator
    typename std::vector<T>::iterator _oldValues_it;

    // Global indices for local elements iterator
    typename std::vector<uint>::iterator _globalId_local_it;

    // Local Id
    uint _localId;


    
    /* ----------------------  Public members ----------------------  */
    
public:
    
    // Default constructor
    basicPatch_iterator( const typename std::vector<T>::iterator& localIt,
			 const typename std::vector<T>::iterator& swapIt,
			 const typename std::vector<T>::iterator& oldIt,
			 const typename std::vector<uint>::iterator& globalIdLocalIt,
			 const uint& localId );

    
    // The copy constructor
    basicPatch_iterator( const basicPatch_iterator<T>& it );

    // Default destructor
    ~basicPatch_iterator();




    // Member access

    // Local value
    const T& value() const;
    
    // Swap value
    const T& swapValue() const;

    // Old time value
    const T& oldValue() const;

    // Global index
    const uint& globalId() const;

    // Local index
    const uint& localId() const;



    // Member modification

    // Local value
    void setValue(const T& val);

    // Swap value
    void setSwapValue( const T& val );

    // Old time value
    void setOldValue( const T& val );

    // Global index
    void setGlobalId( const uint& id );



    
    // Operators

    // Derreference operators. Point to local values
    T& operator*();
    T* operator->();
    
    // Forward operator
    void operator++();

    // Equality operator
    const bool operator==(const basicPatch_iterator<T>& n) const;

    // Inequality operator
    const bool operator!=(const basicPatch_iterator<T>& n) const;
    
};



// Constructors and destructors

// Constructor. Only iterate over local nodes
template<typename T>
basicPatch_iterator<T>::basicPatch_iterator( const typename std::vector<T>::iterator& localIt,
					     const typename std::vector<T>::iterator& swapIt,
					     const typename std::vector<T>::iterator& oldIt,
					     const typename std::vector<uint>::iterator& globalIdLocalIt,
					     const uint& localId ){
    _localNodes_it       = localIt;
    _swapValue_it        = swapIt;
    _oldValues_it        = oldIt;
    _globalId_local_it   = globalIdLocalIt;
    _localId             = localId;
}



// The copy constructor
template<typename T>
basicPatch_iterator<T>::basicPatch_iterator( const basicPatch_iterator<T>& it ) {
    _localNodes_it       = it._localNodes_it;
    _swapValue_it        = it._swapValue_it;
    _oldValues_it        = it._oldValues_it;
    _globalId_local_it   = it._globalId_local_it;
    _localId             = it._localId;
}


// Default destructor
template<typename T>
basicPatch_iterator<T>::~basicPatch_iterator() {}






// Member access

// Local value
template<typename T>
const T& basicPatch_iterator<T>::value() const {
    return *_localNodes_it;
}

// Swap value
template<typename T>
const T& basicPatch_iterator<T>::swapValue() const {
    return *_swapValue_it;
}

// Old time value
template<typename T>
const T& basicPatch_iterator<T>::oldValue() const {
    return *_oldValues_it;
}

// Global index
template<typename T>
const uint& basicPatch_iterator<T>::globalId() const {
    return *_globalId_local_it;
}

// Local index
template<typename T>
const uint& basicPatch_iterator<T>::localId() const {
    return _localId;
}


// Member modification

// Local value
template<typename T>
void basicPatch_iterator<T>::setValue(const T& val) {
    *_localNodes_it = val;
}


// Swap value
template<typename T>
void basicPatch_iterator<T>::setSwapValue( const T& val ) {
    *_swapValue_it = val;
}

// Old time value
template<typename T>
void basicPatch_iterator<T>::setOldValue( const T& val ) {
    *_oldValues_it = val;
}

// Global index
template<typename T>
void basicPatch_iterator<T>::setGlobalId( const uint& id ) {
    *_globalId_local_it = id;
}








// Operators

// Derreference operator
template<typename T>
T& basicPatch_iterator<T>::operator*() {
    return *_localNodes_it;
}


template<typename T>
T* basicPatch_iterator<T>::operator->() {
    return _localNodes_it;
}




// Forward operator
template<typename T>
void basicPatch_iterator<T>::operator++() {
    ++_localNodes_it;
    ++_swapValue_it;
    ++_oldValues_it;
    ++_globalId_local_it;
    ++_localId;
}


// Equality operator
template<typename T>
const bool basicPatch_iterator<T>::operator==(const basicPatch_iterator<T>& n) const{
    return ( n._localNodes_it == _localNodes_it );
}


// Inequality operator
template<typename T>
const bool basicPatch_iterator<T>::operator!=(const basicPatch_iterator<T>& n) const{
    return !operator==(n);
}



#endif // BASICPATCH_ITERATOR_H
