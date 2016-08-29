#ifndef LATTICEPDFFIELD_H
#define LATTICEPDFFIELD_H

#include <latticeField.h>


class latticePdfField : public latticeField<pdf> {


    /* ----------------------  Public members ----------------------  */

public:

    
    // Constructors and destructors

    // Constructor with references
    latticePdfField( basicLBModel* lbm, mpi::environment& env, mpi::communicator& world, const std::string& name, const Time& time, const bool& read = true );

    // Default destructor
    ~latticePdfField();


    
    // Access
    
    // Iterator
    #include "latticePdfField_iterator.h"

    // Local nodes. Begin
    iterator begin() { return iterator( lbPatch<pdf>::begin(), this); }

    // Local nodes. End
    iterator end()   { return iterator( lbPatch<pdf>::end(), this); }



    // Member modification

    // Basic streamming
    const void stream();
    
    // Read values from current time
    void readAllValues();
    
};



#endif // LATTICEPDFFIELD_H
