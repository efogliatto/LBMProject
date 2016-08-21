#ifndef FIELDSHAPE_H
#define FIELDSHAPE_H

#include <polyShapes.h>

class fieldShape : public polyShapes {


    /* ----------------------  Protected member functions ----------------------  */

protected:

    const dictionary _dict;
    
    
    /* ----------------------  Public member functions ----------------------  */

public:

    // Constructors and destructors

    // Default constructor
    fieldShape();

    // Constructor with dictionary name
    fieldShape(const std::string& dictName);

    // Default destructor
    ~fieldShape();



    // Member access

    // Field value, related to mesh point
    const double fieldValue( const string& fieldName, const Vector3& point, const double& nval) const;

    // Field value, related to mesh point
    const Vector3 fieldValue( const string& fieldName, const Vector3& point, const Vector3& nval) const;    
    
    
};

#endif // FIELDSHAPE_H
