#ifndef FIELDSTIME_H
#define FIELDSTIME_H

#include <basicTime.h>
#include <latticeScalarField.h>
#include <latticeVectorField.h>
#include <LBfield.h>


class fieldsTime : public basicTime {



protected:

    // references to external fields
    std::map<string, latticeScalarField*> _externalScalarFields;

    // References to external fields
    std::map<string, latticeVectorField*> _externalVectorFields;

    // References to external fields
    std::map<string, LBfield*> _externalLBfields;

    

public:

    /* ----------------------  Public member functions ----------------------  */

    // Default constructor
    fieldsTime();

    // Default Destructor
    ~fieldsTime();

    // The copy-constructor
    fieldsTime(const fieldsTime& t);




    // Add latticeScalarField to map
    const void addExternalField(latticeScalarField* f);

    // Add latticeVectorField to map
    const void addExternalField(latticeVectorField* f);

    // Add LBfield to map
    const void addExternalField(LBfield* f);


    
    // Get reference to external latticeScalarField
    const latticeScalarField* getExternalScalarField(const std::string& fieldName) const;

    // Get reference to external latticeScalarField
    latticeVectorField* getExternalVectorField(const std::string& fieldName);

    // Get reference to external latticeScalarField
    LBfield* getExternalLBfield(const std::string& fieldName);
    

    
};

#endif // FIELDSTIME_H
