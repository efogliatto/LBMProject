#include <fieldShape.h>

// Constructors and destructors

// Default constructor
fieldShape::fieldShape() : polyShapes("properties/setFieldDict"), _dict("properties/setFieldDict") {}

fieldShape::fieldShape(const string& dictName) : polyShapes(dictName), _dict("properties/setFieldDict") {}

fieldShape::fieldShape(const std::string& dictName, const std::string& shapeName) : polyShapes(dictName, shapeName), _dict("properties/setFieldDict") {}

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

	double in(0);
	
	in  = _dict.lookUpEntry<double>( fieldName + "/inside" );

	
	if ( locatePoint( point ) ) {
	    
	    val = _shapes[0]->value( point, in );
	    
	}
	
	else {
	    
	    val = nval;
	    
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


	else {

	    // Rayleigh - Taylor function
	    if( ffunc.compare("droplet") == 0 ) {

		// Read properties
		const double inside   = _dict.lookUpEntry<double>( fieldName + "/inside");
		const double outside  = _dict.lookUpEntry<double>( fieldName + "/outside");
		const double width    = _dict.lookUpEntry<double>( fieldName + "/width");
		const Vector3 origin  = _dict.lookUpEntry<Vector3>( fieldName + "/origin");
		const double ro       = _dict.lookUpEntry<double>( fieldName + "/radius");
		
		const double r = sqrt( (point - origin).sqMag() );
		 
		
		val = 0.5 * (inside + outside)   -   0.5 * (inside - outside) * tanh( 2*(r-ro)/width );

	    }

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
    if( ffunc.compare("none") == 0 ) {

	Vector3 in   = _dict.lookUpEntry<Vector3>( fieldName + "/inside" );
	Vector3 out  = _dict.lookUpEntry<Vector3>( fieldName + "/outside" );

	// if ( locatePoint( point ) ) {
	//     val = in;
	// }
	// else {
	//     val = nval;
	// }

	if ( locatePoint( point ) ) {
	    
	    val = _shapes[0]->value( point, in, out );
	    
	}
	
	else {
	    
	    val = nval;
	    
	}	
	    
    }



    
    else {
    
	// No function, only inside out
	if( ffunc.compare("zalesaksDisk") == 0 ) {

	    const double w = 0.025 * M_PI / 200,
		ux = -w*(point.y() - 100),
		uy = w*(point.x() - 100);
    
	    val = Vector3(ux, uy, 0);
    
	}

    }

    return val;

}




// Field value, related to mesh point
const pdf fieldShape::fieldValue( const string& fieldName, const Vector3& point, const pdf& nval) const {

    pdf val;
    
    // Search field function type
    const string ffunc = _dict.lookUpEntry<string>( fieldName + "/function");

    // No function, only inside out
    if( ffunc.compare("none") == 0 ) {

	pdf in  = _dict.lookUpEntry<pdf>( fieldName + "/inside" );

	if ( locatePoint( point ) ) {
	    val = in;
	}
	else {
	    val = nval;
	}
	    
    }


    return val;

}
