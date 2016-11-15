#ifndef BDINFO_H
#define BDINFO_H

#include <scalars_C.h>

struct bdInfo {

    
    // Number of boundaries
    unsigned int _nb;

    // Number of elements per boundary
    unsigned int* _nbel;

    // Boundary names
    char** _bdNames;


    // Number of fields that use boundaries
    unsigned int _nf;

    // Field names
    char** _fields;

    // Boundary condition
    char** _bc;
    
    
};

#endif // BDINFO_H
