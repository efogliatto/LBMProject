#include <polyShapes.h>
#include <shapesCreator.h>

using namespace std;



/* ----------------------  Public member functions ----------------------  */


// Constructors and destructors

// Constructor with dictionary name
polyShapes::polyShapes(const string& dictName) : _bbox_min(Vector3(1000000,1000000,1000000)), _bbox_max(Vector3(-1000000,-1000000,-1000000)) {

    // Load dictionary properties
    dictionary dict(dictName);

    // Load list of shapes
    vector<string> shapesName = dict.search("Shapes");


    // Create shape from each name and load to _shapes
    for(auto sname : shapesName) {
	
	// Search shape type
	string stype = dict.lookUpEntry<string>(sname + "/type");
	
	// Create shape
	shapesCreator creator;
	basicShape* bShape = creator.create(stype, sname);

	// Read properties
	bShape->readProperties(dictName);

	// Update Overall bounding box
	double minX = _bbox_min.x(),
	    minY = _bbox_min.y(),
	    minZ = _bbox_min.z(),
	    maxX = _bbox_max.x(),
	    maxY = _bbox_max.y(),
	    maxZ = _bbox_max.z();

	// Compare with local bounding box
	tuple<Vector3, Vector3> bbox = bShape->boundingBox();
	
	if( get<0>(bbox).x() <= minX ) { minX = get<0>(bbox).x(); }
	if( get<0>(bbox).y() <= minY ) { minY = get<0>(bbox).y(); }
	if( get<0>(bbox).z() <= minZ ) { minZ = get<0>(bbox).z(); }

	if( get<1>(bbox).x() >= maxX ) { maxX = get<1>(bbox).x(); }
	if( get<1>(bbox).y() >= maxY ) { maxY = get<1>(bbox).y(); }
	if( get<1>(bbox).z() >= maxZ ) { maxZ = get<1>(bbox).z(); }

	_bbox_min = Vector3(minX, minY, minZ);
	_bbox_max = Vector3(maxX, maxY, maxZ);


	// Add to list
	_shapes.push_back(bShape);

    }

}




// Constructor with dictionary and shape name (only one shape)
polyShapes::polyShapes(const string& dictName, const std::string& shapeName) : _bbox_min(Vector3(1000000,1000000,1000000)), _bbox_max(Vector3(-1000000,-1000000,-1000000)) {

    // Load dictionary properties
    dictionary dict(dictName);

	
    // Search shape type
    string stype = dict.lookUpEntry<string>(shapeName + "/type");
	
    // Create shape
    shapesCreator creator;
    basicShape* bShape = creator.create(stype, shapeName);

    // Read properties
    bShape->readProperties(dictName);

    // Update Overall bounding box
    double minX = _bbox_min.x(),
	minY = _bbox_min.y(),
	minZ = _bbox_min.z(),
	maxX = _bbox_max.x(),
	maxY = _bbox_max.y(),
	maxZ = _bbox_max.z();

    // Compare with local bounding box
    tuple<Vector3, Vector3> bbox = bShape->boundingBox();
	
    if( get<0>(bbox).x() <= minX ) { minX = get<0>(bbox).x(); }
    if( get<0>(bbox).y() <= minY ) { minY = get<0>(bbox).y(); }
    if( get<0>(bbox).z() <= minZ ) { minZ = get<0>(bbox).z(); }

    if( get<1>(bbox).x() >= maxX ) { maxX = get<1>(bbox).x(); }
    if( get<1>(bbox).y() >= maxY ) { maxY = get<1>(bbox).y(); }
    if( get<1>(bbox).z() >= maxZ ) { maxZ = get<1>(bbox).z(); }

    _bbox_min = Vector3(minX, minY, minZ);
    _bbox_max = Vector3(maxX, maxY, maxZ);


    // Add to list
    _shapes.push_back(bShape);


}




// Default destructor
polyShapes::~polyShapes() {}






// Check if point is inside the domain
const bool polyShapes::locatePoint( const Vector3& v ) const {

    bool is_inside = true;

    for(auto shape : _shapes) {
	if ( !shape->locatePoint(v) ) {  is_inside = false;}
    }

    return is_inside;

}




// Bounding box
const tuple<Vector3, Vector3> polyShapes::boundingBox() const {
    return tuple<Vector3, Vector3>(_bbox_min, _bbox_max);
}



// Patches list
const vector<string> polyShapes::boundaryNames() const {

    vector<string> names;

    for(auto shape : _shapes) {
	vector<string> sname = shape->boundaryNames();
	names.insert( names.end(), sname.begin(), sname.end() );
    }

    return names;

}





// Check the patch that contains a point
const string polyShapes::pointOverBoundary(const Vector3& v, const double& tol) const {

    string name;

    for(auto shape : _shapes) {
	name = shape->pointOverBoundary(v, tol);
	if(!name.empty()) {
	    return name;
	}
    }

    // if(patch.empty()) {
    // 	cout << endl << "Unable to associate point " << v << " with patch" << endl << endl;
    // }

    return name;

}



// Value factor
const double polyShapes::value( const Vector3& v ) const {

    double val(1);

    for(auto shape : _shapes) {
	val = val * shape->value(v);
    }

    return val;
}
