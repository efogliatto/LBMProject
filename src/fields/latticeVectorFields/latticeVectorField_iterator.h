#ifndef LATTICEVECTORFIELD_ITERATOR_H
#define LATTICEVECTORFIELD_ITERATOR_H

#include <lbPatch_iterator.h>

typedef vector< std::pair<uint, Vector3*> >::iterator neigh_iterator;


class iterator : public lbPatch_iterator<Vector3> {


    /* ----------------------  Protected members ----------------------  */

protected:

    // Reference to latticeVectorField
    const latticeVectorField* _field;
    
    
    
    /* ----------------------  Public members ----------------------  */
    
public:


    // Constructors and destructors

    // Constructor with references
    iterator( const lbPatch_iterator<Vector3>& it, const latticeVectorField* field ) : lbPatch_iterator<Vector3>(it) {  _field = field;  }

    // Default destructor
    ~iterator() {}
    
    
};

#endif // LATTICEVECTORFIELD_ITERATOR_H
