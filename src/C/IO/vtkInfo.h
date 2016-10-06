#ifndef VTKINFO_H
#define VTKINFO_H

struct vtkInfo {

    // Points
    double** points;

    // Cells
    unsigned int** cells;

    // Total number of points
    unsigned int np;

    // Total number of cells
    unsigned int ncells;

    // Total number of scalar fields
    unsigned int nscalar;

    // Total number of vector fields
    unsigned int nvector;

    // Total number of pdf fields
    unsigned int npdf;

    // Scalar fields
    char** scalarFields;

    // Vector fields
    char** vectorFields;

    // Pdf fields
    char** pdfFields;    
    
};

#endif // VTKINFO_H
