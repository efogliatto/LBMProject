#ifndef VTKPATCHWRITER_H
#define VTKPATCHWRITER_H

/*
  This class is used for writing fields into vtk format (deprecates the use of write() methods)
 */

#include <IOPatch.h>
#include <Time.h>


class vtkPatchWriter {

    
    /* ----------------------  Protected members ----------------------  */

protected:

    // Reference to time
    const Time& _time;

    // Patches Id
    uint _pid;

    // World size
    uint _worldSize;
    
    // references to external fields
    std::vector< std::pair<std::string, IOPatch<double>*> > _scalarFields;

    // References to external fields
    std::vector< std::pair<std::string, IOPatch<Vector3>*> > _vectorFields;

    // References to external fields
    std::vector< std::pair<std::string, IOPatch<pdf>*> > _lbFields;

    // VTK Cells
    std::vector< std::vector<uint> > _vtkCells;

    // Lattice points
    std::vector<Vector3> _points;



    // Write vtk files
    const void writeVTK() const;

    // Write vtk files
    const void writeRAW() const;

    

    /* ----------------------  Public members ----------------------  */

public:

    
    // Constructors and destructors

    // Constructor with references
    vtkPatchWriter( const Time& time, const uint& pid, const uint& worldSize, const string& lbmName, const bool& force = false );

    // Default destructor
    ~vtkPatchWriter();


    // Add latticeScalarField
    const void add( IOPatch<double>* f, const std::string& name);

    // Add latticeVectorField
    const void add( IOPatch<Vector3>* f, const std::string& name );

    // Add LBfield
    const void add( IOPatch<pdf>* f, const std::string& name );




    // Write fields
    const void write() const;
    
    
};

#endif // VTKPATCHWRITER_H
