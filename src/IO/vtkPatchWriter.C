#include<vtkPatchWriter.h>

using namespace std;

/* ----------------------  Public members ----------------------  */

    
// Constructors and destructors

// Constructor with references
vtkPatchWriter::vtkPatchWriter( const Time& time, const uint& pid, const uint& worldSize, const string& lbmName, const bool& force ) : _time(time), _pid(pid), _worldSize(worldSize) {

    // Create case file
    if(   (_pid == 0)  &&  (force == true)   ) {
	ofstream outFile;
	outFile.open( "case.pvd" );
	outFile << "<VTKFile type=\"Collection\" version=\"0.1\" byte_order=\"LittleEndian\">" << endl;
	outFile << "  <Collection>" << endl;
	outFile << "  </Collection>" << endl;
	outFile << "</VTKFile>" << endl;	
	outFile.close();
    }


    // Read VTK cells

    // Open file
    {
	ostringstream fname;
	fname << "processor" << _pid << "/" << lbmName << "_lattice/vtkCells";
	ifstream inFile( fname.str().c_str() );

	// Read number of cells
	uint nCells;
	inFile >> nCells;
	_vtkCells.resize( nCells );

	// Read cells
	for(uint i = 0 ; i < nCells ; i++) {

	    // Number of elements per cell
	    uint nel;
	    inFile >> nel;

	    _vtkCells[i].resize( nel );

	    for(uint j = 0 ; j < nel ; j++) {

		inFile >> _vtkCells[i][j];
	    
	    }
	
	}
    }


    // Read lattice points
    {
	ostringstream fname;
	fname << "processor" << _pid << "/" << lbmName << "_lattice/points";
	ifstream inFile( fname.str().c_str() );

	// Read number of points
	uint nPoints;
	inFile >> nPoints;
	_points.resize( nPoints );

	// Read points
	for(uint i = 0 ; i < nPoints ; i++)
	    inFile >> _points[i];

    }    


}

// Default destructor
vtkPatchWriter::~vtkPatchWriter() { }


// Add latticeScalarField
const void vtkPatchWriter::add( IOPatch<double>* f, const std::string& name ) {
    _scalarFields.push_back( std::make_pair(name,f) );
}

// Add latticeVectorField
const void vtkPatchWriter::add( IOPatch<Vector3>* f, const std::string& name ) {
    _vectorFields.push_back( std::make_pair(name,f) );
}

// Add LBfield
const void vtkPatchWriter::add( IOPatch<pdf>* f, const std::string& name ) {
    _lbFields.push_back( std::make_pair(name,f) );
}








// Write fields
const void vtkPatchWriter::write() const {

   
    // Write vtk files
    if( (_time.write()) ||  (_time.currentTime() == _time.startTime()) ) {	

	// Single vtk files
	writeVTK();

	//  Fields in raw format
	if(_time.currentTime() == _time.startTime()) {
	    writeRAW();
	}

	// Time folder and .pvtu file
	if( _pid == 0 ) {


	    // Mayor case folder

	    ifstream caseFile;
	    caseFile.open( "case.pvd" );

	    // Read file line by line
	    string line;
	    vector<string> fileLines;
	    while( !caseFile.eof() ) {

		// Read line
		getline(caseFile, line);

		fileLines.push_back( line );

	    }

	    caseFile.close();


	    // Write mayor file
	    ofstream outCaseFile;
	    outCaseFile.open( "case.pvd" );
	    for(uint i = 0 ; i < fileLines.size() - 3 ; i++) {
		outCaseFile << fileLines[i] << endl;
	    }
	    ostringstream caseInfo;
	    caseInfo << "    <DataSet part=\"0\"  timestep=\"" << _time.currentTime() << "\" file=\"" << _time.currentTime() << "/fields.pvtu\" />";
	    outCaseFile << caseInfo.str() << endl;
	    outCaseFile << fileLines[ fileLines.size() - 3 ] << endl;
	    outCaseFile << fileLines[ fileLines.size() - 2 ] << endl;	    
	    outCaseFile.close();

	    
	    // Create time folder
	    ostringstream folder;
	    folder << "mkdir -p " << _time.currentTime();
	    int status = system( folder.str().c_str() );
	    if(status) {}

	    // Open file
	    ostringstream fileName;
	    fileName << _time.currentTime() << "/fields.pvtu";
	    ofstream outFile;
	    outFile.open( fileName.str().c_str() );
	    if( outFile.is_open() == false ){
		cout << "Cant't open file " << fileName.str() << endl;
		exit(1);
	    }

	    // Write info
	    outFile << "<?xml version=\"1.0\"?>" << endl;
	    outFile << "<VTKFile type=\"PUnstructuredGrid\" version=\"0.1\" byte_order=\"LittleEndian\">" << endl;
	    outFile << "  <PUnstructuredGrid GhostLevel=\"0\">" << endl;
	    outFile << "    <PPointData Scalars=\"";
	    for(uint i = 0 ; i < _scalarFields.size() ; i++) {
		if (i != (_scalarFields.size()-1) ) {
		    outFile << _scalarFields[i].first << " ";
		}
		else {
		    outFile << _scalarFields[i].first;
		}
	    }
	    outFile << "\" Vectors=\"";
	    for(uint i = 0 ; i < _vectorFields.size() ; i++) {
	    	outFile << _vectorFields[i].first << " ";
	    }
	    for(uint i = 0 ; i < _lbFields.size() ; i++) {
	    	if (i != (_lbFields.size()-1) ) {
	    	    outFile << _lbFields[i].first << " ";
	    	}
	    	else {
	    	    outFile << _lbFields[i].first;
	    	}
	    }
	
	    outFile << "\">" << endl;

	    for(uint i = 0 ; i < _scalarFields.size() ; i++) {
	    	outFile << "      <PDataArray type=\"Float32\" Name=\"" << _scalarFields[i].first << "\"/>" << endl;
	    }
	    for(uint i = 0 ; i < _vectorFields.size() ; i++) {
	    	outFile << "      <PDataArray type=\"Float32\" Name=\"" << _vectorFields[i].first << "\" NumberOfComponents=\"3\"/>" << endl;
	    }
	    for(uint i = 0 ; i < _lbFields.size() ; i++) {
	    	outFile << "      <PDataArray type=\"Float32\" Name=\"" << _lbFields[i].first << "\" NumberOfComponents=\"" << (_lbFields[i].second)->lbmodel()->Q() << "\"/>" << endl;
	    }	    	    
	    outFile << "    </PPointData>" << endl;

	    outFile << "    <PPoints>" << endl;
	    outFile << "      <PDataArray type=\"Float32\" NumberOfComponents=\"3\"/>" << endl;
	    outFile << "    </PPoints>" << endl;

	    for(uint pid = 0 ; pid < _worldSize ; pid++) {
	    	ostringstream fname;
	    	fname << "../processor" << pid << "/" << _time.currentTime() << "/fields.vtu";
	    	outFile << "    <Piece Source=\"" << fname.str() << "\"/>" << endl;
	    }
	    outFile << "  </PUnstructuredGrid>" << endl;
	    outFile << "</VTKFile>" << endl;
	    
	    
	}

	
    }    

}






// Write VTK field in XML format
const void vtkPatchWriter::writeVTK() const {

    // Create folder if it doesnt exist
    ostringstream folder;
    folder << "processor" << _pid << "/" << _time.currentTime();    
    system( ("mkdir -p " + folder.str()).c_str() );
    
    ostringstream fname;
    fname << "processor" << _pid << "/" << _time.currentTime() << "/fields.vtu";
    ofstream outFile( fname.str().c_str() );

    outFile << "<?xml version=\"1.0\"?>" << endl;
    outFile << "<VTKFile type=\"UnstructuredGrid\" version=\"0.1\" byte_order=\"LittleEndian\" compressor=\"vtkZLibDataCompressor\">" << endl;
    outFile << "  <UnstructuredGrid>" << endl;
    outFile << "    <Piece NumberOfPoints=\"" << _points.size() << "\" NumberOfCells=\"" << _vtkCells.size() << "\">" << endl;

	
    // ********************************************************** //
    //                         Write Points                       //
    // ********************************************************** //

    outFile << "      <Points>" << endl;
    outFile << "        <DataArray type=\"Float32\" NumberOfComponents=\"3\" format=\"ascii\">" << endl;

    for(vector<Vector3>::const_iterator pt = _points.begin() ; pt != _points.end() ; pt++) 
	outFile << "          " << pt->x() << "  " <<  pt->y() << "  " << pt->z() << endl;

    outFile << "        </DataArray>" << endl;
    outFile << "      </Points>" << endl;



    // ********************************************************** //
    //                          Write Cells                       //
    // ********************************************************** //	
	
    outFile << "      <Cells>" << endl;
    outFile << "        <DataArray type=\"Int32\" Name=\"connectivity\" format=\"ascii\">" << endl;
    for( auto cell : _vtkCells ) {

	outFile << "         ";

	for(auto cellId : cell) 
	    outFile << cellId << " ";

	outFile << endl;
	    
    }
	
    outFile << "        </DataArray>" << endl;
	
    outFile << "        <DataArray type=\"Int32\" Name=\"offsets\" format=\"ascii\">" << endl;

    uint count(0);
    for( auto cell : _vtkCells ) {
	outFile << "         " << cell.size() + count << endl;
	count += cell.size();
    }
	
    outFile << "        </DataArray>" << endl;

    outFile << "        <DataArray type=\"UInt8\" Name=\"types\" format=\"ascii\">" << endl;

    for( auto cell : _vtkCells ) {
	if( cell.size() == 4 ) {
	    outFile << "         8" << endl;
	}
    }
    outFile << "        </DataArray>" << endl;
	
    outFile << "      </Cells>" << endl;	







    // ********************************************************** //
    //                      Write Point data                      //
    // ********************************************************** //	

    outFile << "      <PointData Scalars=\"";
    for(uint i = 0 ; i < _scalarFields.size() ; i++) {
	if (i != (_scalarFields.size()-1) ) {
	    outFile << _scalarFields[i].first << " ";
	}
	else {
	    outFile << _scalarFields[i].first;
	}
    }
    outFile << "\" Vectors=\"";
    for(uint i = 0 ; i < _vectorFields.size() ; i++) {
	outFile << _vectorFields[i].first << " ";
    }
    for(uint i = 0 ; i < _lbFields.size() ; i++) {
	if (i != (_lbFields.size()-1) ) {
	    outFile << _lbFields[i].first << " ";
	}
	else {
	    outFile << _lbFields[i].first;
	}
    }
	
    outFile << "\">" << endl;

    // Write Scalar fields
    for(uint i = 0 ; i < _scalarFields.size() ; i++) {

	outFile << "        <DataArray type=\"Float32\" Name=\"" << _scalarFields[i].first << "\" format=\"ascii\">" << endl;
	    
	for(lbPatch_iterator<double> pt = (_scalarFields[i].second)->begin() ; pt != (_scalarFields[i].second)->end() ; ++pt)
	    outFile << "          " << *pt << endl;

	for(vector<double>::const_iterator pt = (_scalarFields[i].second)->ghostBegin() ; pt != (_scalarFields[i].second)->ghostEnd() ; ++pt)
	    outFile << "          " << *pt << endl;

	outFile << "        </DataArray>" << endl;
	    
    }

    // Write Vector fields
    for(uint i = 0 ; i < _vectorFields.size() ; i++) {

	outFile << "        <DataArray type=\"Float32\" Name=\"" << _vectorFields[i].first << "\"  NumberOfComponents=\"3\" format=\"ascii\">" << endl;
	    
	for(lbPatch_iterator<Vector3> pt = (_vectorFields[i].second)->begin() ; pt != (_vectorFields[i].second)->end() ; ++pt)
	    outFile << "          " << (*pt).x() << " " << (*pt).y() << " " << (*pt).z() << " " << endl;
	    
	for(vector<Vector3>::const_iterator pt = (_vectorFields[i].second)->ghostBegin() ; pt != (_vectorFields[i].second)->ghostEnd() ; ++pt) 
	    outFile << "          " << pt->x() << " " << pt->y() << " " << pt->z() << " " << endl;

	outFile << "        </DataArray>" << endl;	

    }	


    // Write LBfields
    for(uint i = 0 ; i < _lbFields.size() ; i++) {

	outFile << "        <DataArray type=\"Float32\" Name=\"" << _lbFields[i].first << "\"  NumberOfComponents=\"" << (_lbFields[i].second)->lbmodel()->Q() <<"\" format=\"ascii\">" << endl;
	    

	for(lbPatch_iterator<pdf> pt = (_lbFields[i].second)->begin() ; pt != (_lbFields[i].second)->end() ; ++pt) {

	    outFile << "          ";

	    for(uint j = 0 ; j < (*pt).size() ; j++) 
		outFile << (*pt)[j] << " ";

	    outFile << endl;
	    
	}
	    

	for(vector<pdf>::const_iterator pt = (_lbFields[i].second)->ghostBegin() ; pt != (_lbFields[i].second)->ghostEnd() ; ++pt) {
		
	    outFile << "          ";
		
	    for(uint j = 0 ; j < (*pt).size() ; j++) 
		outFile << (*pt)[j] << " ";

	    outFile << endl;
		
	}
	    
	outFile << "        </DataArray>" << endl;
	    
    }		


    outFile << "      </PointData>" << endl;		

    outFile << "    </Piece>" << endl;
    outFile << "  </UnstructuredGrid>" << endl;
    outFile << "</VTKFile>" << endl;

    outFile.close();

}





// Write VTK field in XML format
const void vtkPatchWriter::writeRAW() const {

    // Create folder if it doesnt exist
    ostringstream folder;
    folder << "processor" << _pid << "/" << _time.currentTime();    
    system( ("mkdir -p " + folder.str()).c_str() );
    

    // Write Scalar fields
    for(uint i = 0 ; i < _scalarFields.size() ; i++) {

	ostringstream fname;
	fname << "processor" << _pid << "/" << _time.currentTime() << "/" << _scalarFields[i].first;
	ofstream outFile( fname.str().c_str() );

	// Total number of elements
	outFile << _points.size() << endl;
	    
	for(lbPatch_iterator<double> pt = (_scalarFields[i].second)->begin() ; pt != (_scalarFields[i].second)->end() ; ++pt)
	    outFile << *pt << endl;

	for(vector<double>::const_iterator pt = (_scalarFields[i].second)->ghostBegin() ; pt != (_scalarFields[i].second)->ghostEnd() ; ++pt)
	    outFile << *pt << endl;

	outFile.close();
	    
    }

    // Write Vector fields
    for(uint i = 0 ; i < _vectorFields.size() ; i++) {

	ostringstream fname;
	fname << "processor" << _pid << "/" << _time.currentTime() << "/" << _vectorFields[i].first;
	ofstream outFile( fname.str().c_str() );

        // Total number of elements
	outFile << _points.size() << endl;	
	    
	for(lbPatch_iterator<Vector3> pt = (_vectorFields[i].second)->begin() ; pt != (_vectorFields[i].second)->end() ; ++pt)
	    outFile << (*pt).x() << " " << (*pt).y() << " " << (*pt).z() << " " << endl;
	    
	for(vector<Vector3>::const_iterator pt = (_vectorFields[i].second)->ghostBegin() ; pt != (_vectorFields[i].second)->ghostEnd() ; ++pt) 
	    outFile << pt->x() << " " << pt->y() << " " << pt->z() << " " << endl;

	outFile.close();

    }	


    // Write LBfields
    for(uint i = 0 ; i < _lbFields.size() ; i++) {


	ostringstream fname;
	fname << "processor" << _pid << "/" << _time.currentTime() << "/" << _lbFields[i].first;
	ofstream outFile( fname.str().c_str() );

        // Total number of elements
	outFile << _points.size() << endl;	

	for(lbPatch_iterator<pdf> pt = (_lbFields[i].second)->begin() ; pt != (_lbFields[i].second)->end() ; ++pt) {

	    for(uint j = 0 ; j < (*pt).size() ; j++) 
		outFile << (*pt)[j] << " ";

	    outFile << endl;
	    
	}
	    

	for(vector<pdf>::const_iterator pt = (_lbFields[i].second)->ghostBegin() ; pt != (_lbFields[i].second)->ghostEnd() ; ++pt) {
		
	    for(uint j = 0 ; j < (*pt).size() ; j++) 
		outFile << (*pt)[j] << " ";

	    outFile << endl;
		
	}
	    
	outFile.close();
	    
    }		

}


