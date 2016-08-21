#ifndef PERIODICBOX_H
#define PERIODICBOX_H

#include <box.h>
#include <basicLBModel.h>
#include <map>

class periodicBox : public box {
    

    /* ----------------------  Private members ----------------------  */

    // Total number of elements
    uint _nx,
	_ny,
	_nz;

    // Lattice size
    double _lsize;


    /* ----------------------  Public member functions ----------------------  */

public:

    // Constructors and destructors

    // Default constructor
    periodicBox();

    // Constructor with name
    periodicBox(const std::string& name);

    // Default destructor
    ~periodicBox();



    // Member modification

    // Reading properties
    void readProperties(const std::string& dictName);



    // Mesh construction
    const std::vector<Vector3> points() const;

    // Neighbour construction
    const std::vector< std::vector<int> > neighbours(const basicLBModel* lbm, const std::vector<Vector3>& points) const;

    // Boundary map
    const std::map<std::string, std::vector<uint>> boundaryMap() const; 

    // VTK Cells
    const std::vector< std::vector<uint> > VTKCells(const basicLBModel* lbm, const std::vector<Vector3>& points, const std::vector< std::vector<int> >& nbr) const;

};


#endif // SEMIPERIODICBOX_H
