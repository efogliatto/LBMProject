#ifndef IOPATCH_H
#define IOPATCH_H

#include <commPatch.h>

template<typename T>
class IOPatch : public commPatch<T> {

    
    /* ----------------------  Public members ----------------------  */

public:

    
    // Constructors and destructors

    // Constructor with reference to LBModel
    IOPatch( basicLBModel* lbm );

    // Constructor with reference to LBModel and local nodes size
    IOPatch( basicLBModel* lbm, const uint& sz );

    // Default destructor
    ~IOPatch();


    
    // Write members

    // Local values
    const void writeLocalValues(const std::string& fileName, const std::string& folderName) const;

    // All values
    const void writeAllValues(const std::string& fileName, const std::string& folderName) const;    

    // Neighbour local indices
    const void writeNeighboursIds(const std::string& fileName, const std::string& folderName) const;

    // Global indices, local nodes
    const void writeGlobalIdLocal(const std::string& fileName, const std::string& folderName) const;

    // Global indices, ghost nodes
    const void writeGlobalIdGhost(const std::string& fileName, const std::string& folderName) const;

    // Recv map indices
    const void writeRecvMapsIds(const std::string& fileName, const std::string& folderName) const;

    // Send map indices
    const void writeSendMapsIds(const std::string& fileName, const std::string& folderName) const;

    // Boundaries indices
    const void writeBoundariesIds(const std::string& fileName, const std::string& folderName) const;

    // VTK Cells
    const void writeVTKCells(const std::string& fileName, const std::string& folderName, const std::vector< std::vector<uint> >& vtkCells) const;
     

    

    // Read members
    
    // Local values
    const void readLocalValues(const std::string& fileName, const std::string& folderName);

    // Neighbour local indices
    const void readNeighboursIds(const std::string& fileName, const std::string& folderName);

    // Global indices, local nodes
    const void readGlobalIdLocal(const std::string& fileName, const std::string& folderName);

    // Global indices, ghost nodes
    const void readGlobalIdGhost(const std::string& fileName, const std::string& folderName);    

    // Recv map indices
    const void readRecvMapsIds(const std::string& fileName, const std::string& folderName);

    // Send map indices
    const void readSendMapsIds(const std::string& fileName, const std::string& folderName);        

    // Boundaries indices
    const void readBoundariesIds(const std::string& fileName, const std::string& folderName);
    
    
};



// Constructors and destructors


// Constructor with reference to LBModel
template<typename T>
IOPatch<T>::IOPatch( basicLBModel* lbm ) : commPatch<T>( lbm ) {}


// Constructor with reference to LBModel and local size
template<typename T>
IOPatch<T>::IOPatch( basicLBModel* lbm, const uint& sz ) : commPatch<T>(lbm,sz) {}


// Default destructor
template<typename T>
IOPatch<T>::~IOPatch() {}



// Local values
template<typename T>
const void IOPatch<T>::writeLocalValues(const std::string& fileName, const std::string& folderName) const {

    // Create folder if it does not exist
    system( ("mkdir -p " + folderName).c_str() );
    
    // Open file
    std::ofstream outFile;
    outFile.open( (folderName + "/" + fileName).c_str() );
    if( !outFile.is_open() ) {
    	std::cout << "Unable to open file " << fileName << std::endl;
    	exit(1);
    }

    // Write total number of elements
    outFile << this->_localValues.size() << std::endl;

    // Write values
    for(typename std::vector<T>::const_iterator it = this->_localValues.begin() ; it != this->_localValues.end() ; it++) {
	outFile << *it << std::endl;
    }

    // Close file
    outFile.close();
    
}




// All values
template<typename T>
const void IOPatch<T>::writeAllValues(const std::string& fileName, const std::string& folderName) const {

    // Create folder if it does not exist
    system( ("mkdir -p " + folderName).c_str() );
    
    // Open file
    std::ofstream outFile;
    outFile.open( (folderName + "/" + fileName).c_str() );
    if( !outFile.is_open() ) {
    	std::cout << "Unable to open file " << fileName << std::endl;
    	exit(1);
    }

    // Write total number of elements
    outFile << this->_localValues.size() + this->_ghostValues.size() << std::endl;

    // Write values
    for(typename std::vector<T>::const_iterator it = this->_localValues.begin() ; it != this->_localValues.end() ; it++) {
	outFile << *it << std::endl;
    }

    for(typename std::vector<T>::const_iterator it = this->_ghostValues.begin() ; it != this->_ghostValues.end() ; it++) {
	outFile << *it << std::endl;
    }    

    // Close file
    outFile.close();
    
}


// Local values
template<typename T>
const void IOPatch<T>::readLocalValues(const std::string& fileName, const std::string& folderName) {

    // Open file
    std::ifstream inFile;
    inFile.open( (folderName + "/" + fileName).c_str() );
    if( !inFile.is_open() ) {
    	std::cout << "Unable to open file " << fileName << std::endl;
    	exit(1);
    }

    // Read total number of elements and resize
    uint nlocal;
    inFile >> nlocal;
    if( this->_localValues.empty() ) {
	this->_localValues.resize( nlocal );
	this->_swapValues.resize( nlocal );
	this->_oldValues.resize( nlocal );
    }

    // Read values
    for(typename std::vector<T>::iterator it = this->_localValues.begin() ; it != this->_localValues.end() ; it++) {
	inFile >> *it;
    }

    // Close file
    inFile.close();    
    
}








// Neighbours indices. Local indexing
template<typename T>
const void IOPatch<T>::writeNeighboursIds(const std::string& fileName, const std::string& folderName) const {

    // Create folder if it does not exist
    system( ("mkdir -p " + folderName).c_str() );
    
    // Open file
    std::ofstream outFile;
    outFile.open( (folderName + "/" + fileName).c_str() );
    if( !outFile.is_open() ) {
    	std::cout << "Unable to open file " << fileName << std::endl;
    	exit(1);
    }

    // Write total number of elements
    outFile << this->_localValues.size() << std::endl;    

    // Write values
    for(uint i = 0 ; i < this->_neighbours.size() ; i++) {
	for(uint j = 0 ; j < this->_lbm->Q() ; j++) {
	    outFile << this->_neighbours[i][j] << "  ";
	}
	outFile << std::endl;
    }

    // Close file
    outFile.close();
    
}


// Neighbours indices. Local indexing
template<typename T>
const void IOPatch<T>::readNeighboursIds(const std::string& fileName, const std::string& folderName) {

    // Open file
    std::ifstream inFile;
    inFile.open( (folderName + "/" + fileName).c_str() );
    if( !inFile.is_open() ) {
    	std::cout << "Unable to open file " << fileName << std::endl;
    	exit(1);
    }

    // Read total number of elements and resize
    uint nlocal;
    inFile >> nlocal;

    if( this->_neighbours.empty() ) {
	this->_neighbours.resize( nlocal );
	for(uint i = 0 ; i < nlocal ; i++) {
	    this->_neighbours[i].resize( this->_lbm->Q() );
	}
    }

    if( this->_localValues.empty() ) {
	this->_localValues.resize( nlocal );
	this->_swapValues.resize( nlocal );
	this->_oldValues.resize( nlocal );
    }
    

    // Read values
    for(uint i = 0 ; i < this->_neighbours.size() ; i++) {
	for(uint j = 0 ; j < this->_lbm->Q() ; j++) {
	    inFile >> this->_neighbours[i][j];
	}
    }

    // Close file
    inFile.close();    
    
}







// Global indices, local nodes
template<typename T>
const void IOPatch<T>::writeGlobalIdLocal(const std::string& fileName, const std::string& folderName) const {

    // Create folder if it does not exist
    system( ("mkdir -p " + folderName).c_str() );
    
    // Open file
    std::ofstream outFile;
    outFile.open( (folderName + "/" + fileName).c_str() );
    if( !outFile.is_open() ) {
    	std::cout << "Unable to open file " << fileName << std::endl;
    	exit(1);
    }

    // Write total number of elements
    outFile << this->_globalId_localNodes.size() << std::endl;

    // Write values
    for(uint i = 0 ; i < this->_globalId_localNodes.size() ; i++) {
	outFile << this->_globalId_localNodes[i] << std::endl;
    }

    // Close file
    outFile.close();
    
}


// Global indices, local nodes
template<typename T>
const void IOPatch<T>::readGlobalIdLocal(const std::string& fileName, const std::string& folderName) {

    // Open file
    std::ifstream inFile;
    inFile.open( (folderName + "/" + fileName).c_str() );
    if( !inFile.is_open() ) {
    	std::cout << "Unable to open file " << fileName << std::endl;
    	exit(1);
    }

    // Read total number of elements and resize
    uint nlocal;
    inFile >> nlocal;

    if( this->_globalId_localNodes.empty() )
	this->_globalId_localNodes.resize( nlocal );    

    // Read values
    for(uint i = 0 ; i < this->_globalId_localNodes.size() ; i++) {
	inFile >> this->_globalId_localNodes[i];
    }

    // Close file
    inFile.close();
    
}





// Global indices, ghost nodes
template<typename T>
const void IOPatch<T>::writeGlobalIdGhost(const std::string& fileName, const std::string& folderName) const {

    // Create folder if it does not exist
    system( ("mkdir -p " + folderName).c_str() );
    
    // Open file
    std::ofstream outFile;
    outFile.open( (folderName + "/" + fileName).c_str() );
    if( !outFile.is_open() ) {
    	std::cout << "Unable to open file " << fileName << std::endl;
    	exit(1);
    }

    // Write total number of elements
    outFile << this->_globalId_ghostNodes.size() << std::endl;

    // Write values
    for(uint i = 0 ; i < this->_globalId_ghostNodes.size() ; i++) {
	outFile << this->_globalId_ghostNodes[i] << std::endl;
    }

    // Close file
    outFile.close();
    
}


// Global indices, local nodes
template<typename T>
const void IOPatch<T>::readGlobalIdGhost(const std::string& fileName, const std::string& folderName) {

    // Open file
    std::ifstream inFile;
    inFile.open( (folderName + "/" + fileName).c_str() );
    if( !inFile.is_open() ) {
    	std::cout << "Unable to open file " << fileName << std::endl;
    	exit(1);
    }

    // Read total number of elements and resize
    uint nghost;
    inFile >> nghost;
    this->_globalId_ghostNodes.resize( nghost );
    this->_ghostValues.resize( nghost );


    // Read values
    for(uint i = 0 ; i < this->_globalId_ghostNodes.size() ; i++) {
	inFile >> this->_globalId_ghostNodes[i];
    }

    // Close file
    inFile.close();


    /* std::cout << std::endl; */
    /* for(uint i = 0 ; i < this->_globalId_ghostNodes.size() ; i++) { */
    /* 	std::cout << this->_globalId_ghostNodes[i] << std::endl; */
    /* } */
    
}



// Send Map Indices
template<typename T>
const void IOPatch<T>::writeRecvMapsIds(const std::string& fileName, const std::string& folderName) const {

    // Create folder if it does not exist
    system( ("mkdir -p " + folderName).c_str() );
    
    // Open file
    std::ofstream outFile;
    outFile.open( (folderName + "/" + fileName).c_str() );
    if( !outFile.is_open() ) {
    	std::cout << "Unable to open file " << fileName << std::endl;
    	exit(1);
    }

    // Write total number of elements
    outFile << this->_ghostRecvMap.size() << std::endl;

    // Write local values for each patch
    for( auto patch : this->_ghostRecvId ) {

	// Patch Id
	uint patchId = patch.first;
	outFile << patchId << std::endl;

	// Number of elements
	outFile << patch.second.size() << std::endl;

	// Local indices
	for( auto id : patch.second )
	    outFile << id << std::endl;

	// Global indices
	for( auto id : this->_ghostRecvMap_globalId.at(patchId) )
	    outFile << id << std::endl;

    }


    // Close file
    outFile.close();
    
}




// Global indices, local nodes
template<typename T>
const void IOPatch<T>::readRecvMapsIds(const std::string& fileName, const std::string& folderName) {

    // Open file
    std::ifstream inFile;
    inFile.open( (folderName + "/" + fileName).c_str() );
    if( !inFile.is_open() ) {
    	std::cout << "Unable to open file " << fileName << std::endl;
    	exit(1);
    }

    // Read total number of patchs
    uint npatch;
    inFile >> npatch;


    // Read values
    for(uint i = 0 ; i < npatch ; i++) {

	// Read patch Id
	uint pid;
	inFile >> pid;

	// Number of elements per patch
	uint nel;
	inFile >> nel;

	// Read ids
	std::vector<uint> lid( nel ),
	    gid( nel );

	for(uint j = 0 ; j < nel ; j++)
	    inFile >> lid[j];

	for(uint j = 0 ; j < nel ; j++)
	    inFile >> gid[j];


	// Set recv maps
	commPatch<T>::setRecvLocalMaps( pid, lid, gid );
    }

    // Close file
    inFile.close();

    
    /* // Write local values for each patch */
    /* std::cout << std::endl; */
    /* for( auto patch : this->_ghostRecvId ) { */

    /* 	// Patch Id */
    /* 	uint patchId = patch.first; */
    /* 	std::cout << patchId << std::endl; */

    /* 	// Number of elements */
    /* 	std::cout << patch.second.size() << std::endl; */

    /* 	// Local indices */
    /* 	for( auto id : patch.second ) */
    /* 	    std::cout << id << std::endl; */

    /* 	// Global indices */
    /* 	for( auto id : this->_ghostRecvMap_globalId.at(patchId) ) */
    /* 	    std::cout << id << std::endl; */

    /* } */
    

    /* for(uint i = 0 ; i < this->_globalId_ghostNodes.size() ; i++) { */
    /* 	std::cout << this->_globalId_ghostNodes[i] << std::endl; */
    /* } */    
    
}







// Send Map Indices
template<typename T>
const void IOPatch<T>::writeSendMapsIds(const std::string& fileName, const std::string& folderName) const {

    // Create folder if it does not exist
    system( ("mkdir -p " + folderName).c_str() );
    
    // Open file
    std::ofstream outFile;
    outFile.open( (folderName + "/" + fileName).c_str() );
    if( !outFile.is_open() ) {
    	std::cout << "Unable to open file " << fileName << std::endl;
    	exit(1);
    }

    // Write total number of elements
    outFile << this->_ghostSendId.size() << std::endl;

    // Write local values for each patch
    for( auto patch : this->_ghostSendId ) {

	// Patch Id
	outFile << patch.first << std::endl;

	// Number of elements
	outFile << patch.second.size() << std::endl;

	// Local indices
	for( auto id : patch.second )
	    outFile << id << std::endl;

    }


    // Close file
    outFile.close();
    
}




// Send map indices
template<typename T>
const void IOPatch<T>::readSendMapsIds(const std::string& fileName, const std::string& folderName) {

    // Open file
    std::ifstream inFile;
    inFile.open( (folderName + "/" + fileName).c_str() );
    if( !inFile.is_open() ) {
    	std::cout << "Unable to open file " << fileName << std::endl;
    	exit(1);
    }

    // Read total number of patchs
    uint npatch;
    inFile >> npatch;


    // Read values
    for(uint i = 0 ; i < npatch ; i++) {

	// Read patch Id
	uint pid;
	inFile >> pid;

	// Number of elements per patch
	uint nel;
	inFile >> nel;

	// Read ids
	std::vector<uint> lid( nel );

	for(uint j = 0 ; j < nel ; j++)
	    inFile >> lid[j];

	// Set recv maps
	commPatch<T>::setSendLocalMaps( pid, lid );
    }

    // Close file
    inFile.close();





    /* // Write local values for each patch */
    /* std::cout << std::endl; */
    /* for( auto patch : this->_ghostSendId ) { */

    /* 	// Patch Id */
    /* 	std::cout << patch.first << std::endl; */

    /* 	// Number of elements */
    /* 	std::cout << patch.second.size() << std::endl; */

    /* 	// Local indices */
    /* 	for( auto id : patch.second ) */
    /* 	    std::cout << id << std::endl; */

    /* } */
    
}





// Boundaries indices
template<typename T>
const void IOPatch<T>::writeBoundariesIds(const std::string& fileName, const std::string& folderName) const {

    // Create folder if it does not exist
    system( ("mkdir -p " + folderName).c_str() );
    
    // Open file
    std::ofstream outFile;
    outFile.open( (folderName + "/" + fileName).c_str() );
    if( !outFile.is_open() ) {
    	std::cout << "Unable to open file " << fileName << std::endl;
    	exit(1);
    }

    // Write total number of boundaries
    outFile << this->_boundaryMap.size() << std::endl;

    // Write local values for each patch
    for( auto patch : this->_boundaryMap ) {

	// Boundary name
	outFile << patch.first << std::endl;

	// Number of elements
	outFile << patch.second.size() << std::endl;

	// Local indices
	for( auto id : patch.second )
	    outFile << id << std::endl;

    }


    // Close file
    outFile.close();
    
}




// Boundaries indices
template<typename T>
const void IOPatch<T>::readBoundariesIds(const std::string& fileName, const std::string& folderName) {

    // Open file
    std::ifstream inFile;
    inFile.open( (folderName + "/" + fileName).c_str() );
    if( !inFile.is_open() ) {
    	std::cout << "Unable to open file " << fileName << std::endl;
    	exit(1);
    }

    // Read total number of boundaries
    uint npatch;
    inFile >> npatch;


    // Read values
    for(uint i = 0 ; i < npatch ; i++) {

	// Read boundary name
	string bdName;
	inFile >> bdName;

	// Number of elements per boundary
	uint nel;
	inFile >> nel;

	// Read ids
	std::vector<uint> lid( nel );

	for(uint j = 0 ; j < nel ; j++)
	    inFile >> lid[j];

	// Set recv maps
	boundaryPatch<T>::setLocalBdMap( bdName, lid );
    }

    // Close file
    inFile.close();
    
}





// VTK Cells
template<typename T>
const void IOPatch<T>::writeVTKCells(const std::string& fileName, const std::string& folderName, const std::vector< std::vector<uint> >& vtkCells) const {

    // Create global to local map
    std::map<uint, uint> g2l;

    // Add indices for local nodes
    for(uint i = 0 ; i < this->_globalId_localNodes.size() ; i++)
	g2l[ this->_globalId_localNodes[i] ] = i;

    // Add indices for ghost nodes
    for(uint i = 0 ; i < this->_globalId_ghostNodes.size() ; i++)
	g2l[ this->_globalId_ghostNodes[i] ] = i + this->_globalId_localNodes.size();    
    

    
    // Local vtk cell indices
    std::vector< std::vector<uint> > _localVTK;

    // Move over vtkCells and check ownership
    for( auto gcell : vtkCells  ) {

	// check ownership
	std::vector<uint> _lcell;
	for( auto gcellId : gcell ) {

	    if( g2l.find( gcellId ) != g2l.end() ) {

		_lcell.push_back( g2l[gcellId] );
		
	    }
	    
	}

	// Add to global list
	if( _lcell.size() == gcell.size() )
	    _localVTK.push_back( _lcell );
	
    }




    // Write info to file
    
    // Create folder if it does not exist
    system( ("mkdir -p " + folderName).c_str() );
    
    // Open file
    std::ofstream outFile;
    outFile.open( (folderName + "/" + fileName).c_str() );
    if( !outFile.is_open() ) {
    	std::cout << "Unable to open file " << fileName << std::endl;
    	exit(1);
    }

    // Write total number cells
    outFile << _localVTK.size() << std::endl;

    // Write individual cells
    for( auto cell : _localVTK ) {

	outFile << cell.size() << " ";

	for(auto cellId : cell)
	    outFile << cellId << " ";

	outFile << std::endl;

    }

    outFile.close();
    
    
}

#endif // IOPATCH_H
