#include <fieldShape.h>

// Constructors and destructors

// Default constructor
fieldShape::fieldShape() : polyShapes("properties/setFieldDict"), _dict("properties/setFieldDict") {}

fieldShape::fieldShape(const string& dictName) : polyShapes(dictName), _dict("properties/setFieldDict") {}

// Default destructor
fieldShape::~fieldShape() {}



// Member access

// Field value, related to mesh point
const double fieldShape::fieldValue( const string& fieldName, const Vector3& point, const double& nval) const {

    double val(0);
    
    // Search field function type
    const string ffunc = _dict.lookUpEntry<string>( fieldName + "/function");

    // No function, only inside out
    if( ffunc.compare("none") == 0 ) {

	double in(0),
	    out(0);
	in  = _dict.lookUpEntry<double>( fieldName + "/inside" );
	out = _dict.lookUpEntry<double>( fieldName + "/outside" );

	if ( locatePoint( point ) ) {
	    val = in * value( point );
	}
	else {
	    val = out * value( point );
	}
	    
    }

    
    else {

	// Rayleigh - Taylor function
	if( ffunc.compare("Rayleigh-Taylor") == 0 ) {

	    // Read properties
	    const double d      = _dict.lookUpEntry<double>( fieldName + "/d");
	    const double lambda = _dict.lookUpEntry<double>( fieldName + "/lambda");
	    const double D      = _dict.lookUpEntry<double>( fieldName + "/D");
		
	    const double h = 2*d + 0.05*d*cos(2*M_PI*point.x()/lambda);
	    
	    val = tanh(  2*(point.y() - h)/D  );

	}

    }





    return val;
    

}






// Field value, related to mesh point
const Vector3 fieldShape::fieldValue( const string& fieldName, const Vector3& point, const Vector3& nval) const {

    Vector3 val(0,0,0);
    
    // Search field function type
    const string ffunc = _dict.lookUpEntry<string>( fieldName + "/function");

    // No function, only inside out
    if( ffunc.compare("zalesaksDisk") == 0 ) {

	const double w = 0.025 * M_PI / 200,
    	ux = -w*(point.y() - 100),
    	uy = w*(point.x() - 100);
    
	val = Vector3(ux, uy, 0);
    
    }


    return val;

}
