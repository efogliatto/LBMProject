#include <shapesCreator.h>

using namespace std;

basicShape* shapesCreator::create(const string& stype, const string& sname) {

    if( stype.find("box")      != string::npos )  return new box(sname);
    if( stype.find("cylinder") != string::npos )  return new cylinder(sname);
    if( stype.find("sphere")   != string::npos )  return new sphere(sname);
    if( stype.find("bubble")   != string::npos )  return new bubble(sname);

    // Default 
    cout << endl << "Shape type " << stype << " does not exist" << endl << endl;
    exit(1);

    return 0;

}
