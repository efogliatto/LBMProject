#ifndef LATTICEPDFFIELD_ITERATOR_H
#define LATTICEPDFFIELD_ITERATOR_H

#include <lbPatch_iterator.h>

typedef vector< std::pair<uint, pdf*> >::iterator neigh_iterator;


class iterator : public lbPatch_iterator<pdf> {


    /* ----------------------  Protected members ----------------------  */

protected:

    // Reference to latticePdfField
    const latticePdfField* _field;
    
    
    
    /* ----------------------  Public members ----------------------  */
    
public:


    // Constructors and destructors

    // Constructor with references
    iterator( const lbPatch_iterator<pdf>& it, const latticePdfField* field ) : lbPatch_iterator<pdf>(it) {  _field = field;  }

    // Default destructor
    ~iterator() {}
    
    
};

#endif // LATTICEPDFFIELD_ITERATOR_H
