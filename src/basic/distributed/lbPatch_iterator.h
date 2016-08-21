#ifndef LBPATCH_ITERATOR_H
#define LBPATCH_ITERATOR_H

#include <basicPatch_iterator.h>

template<typename T>
class basicPatch_iterator;

template<typename T>
class lbPatch_iterator : public basicPatch_iterator<T> {

    
    /* ----------------------  Protected members ----------------------  */

protected:

    // Iterator fron neighbour linked list
    typename std::vector<  std::vector< std::pair<uint, T*> >  >::iterator _neighLinkedList_it;





    /* ----------------------  Public members ----------------------  */
    
public:
    
    // Default constructor
    lbPatch_iterator( const basicPatch_iterator<T>& bpit, const typename std::vector<  std::vector< std::pair<uint, T*> >  >::iterator& neighLinkedListIt );

    // The copy constructor
    lbPatch_iterator( const lbPatch_iterator<T>& it );
    
    // Default destructor
    ~lbPatch_iterator();


    // Forward operator
    void operator++();



    // Neighbour access using iterators

    // Begin neighbours
    typename std::vector< std::pair<uint, T*> >::iterator neighBegin();

    // End neighbours
    typename std::vector< std::pair<uint, T*> >::iterator neighEnd();


};






// Constructors and destructors

// Constructor. Only iterate over local nodes
template<typename T>
lbPatch_iterator<T>::lbPatch_iterator( const basicPatch_iterator<T>& bpit, const typename std::vector<  std::vector< std::pair<uint, T*> >  >::iterator& neighLinkedListIt ) : basicPatch_iterator<T>(bpit) {
    this->_neighLinkedList_it = neighLinkedListIt;
}


// The copy constructor
template<typename T>
lbPatch_iterator<T>::lbPatch_iterator( const lbPatch_iterator<T>& it ) : basicPatch_iterator<T>(it) { _neighLinkedList_it = it._neighLinkedList_it; }




// Default destructor
template<typename T>
lbPatch_iterator<T>::~lbPatch_iterator() {}




// Operators

// Forward operator
template<typename T>
void lbPatch_iterator<T>::operator++() {
    basicPatch_iterator<T>::operator++();
    ++_neighLinkedList_it;
}





// Neighbour access using iterators

// Begin neighbours
template<typename T>
typename std::vector< std::pair<uint, T*> >::iterator lbPatch_iterator<T>::neighBegin() {
    return this->_neighLinkedList_it->begin();
}


// End neighbours
template<typename T>
typename std::vector< std::pair<uint, T*> >::iterator lbPatch_iterator<T>::neighEnd() {
    return this->_neighLinkedList_it->end();
}



#endif // LBPATCH_ITERATOR_H
