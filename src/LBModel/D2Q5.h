#ifndef D2Q5_H
#define D2Q5_H


#include <basicLBModel.h>

class D2Q5 : public basicLBModel {


    /* ----------------------  Public member functions ----------------------  */

public:

    // Constructors and destructors

    // Default constructor
    D2Q5();

    // Default destructor
    ~D2Q5();



    // Access members
    const uint& D() const;

    // Main index
    const bool is_principal(const uint& id) const;    
};

#endif // D2Q5_H
