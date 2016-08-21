#ifndef D2Q4_H
#define D2Q4_H


#include <basicLBModel.h>

class D2Q4 : public basicLBModel {


    /* ----------------------  Public member functions ----------------------  */

public:

    // Constructors and destructors

    // Default constructor
    D2Q4();

    // Default destructor
    ~D2Q4();


    // Access members
    const uint& D() const;

    // Main index
    const bool is_principal(const uint& id) const;
    
};

#endif // D2Q4_H
