#ifndef D3Q7_H
#define D3Q7_H


#include <basicLBModel.h>

class D3Q7 : public basicLBModel {


    /* ----------------------  Public member functions ----------------------  */

public:

    // Constructors and destructors

    // Default constructor
    D3Q7();

    // Default destructor
    ~D3Q7();



    // Access members
    const uint& D() const;

    // Main index
    const bool is_principal(const uint& id) const;    
};

#endif // D3Q7_H
