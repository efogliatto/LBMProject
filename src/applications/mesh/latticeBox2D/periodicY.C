#include <vector>
#include <iostream>
#include <map>
#include <string>

typedef unsigned int uint;

using namespace std;



map<string, vector<uint>> periodicY( vector< vector<int> >& neigh, const uint nx, const uint ny, const uint Q ) {


    // Boundary map
    map<string, vector<uint>> bmap;    


    // Move over X-boundary points
    for( uint id = nx ; id < (nx-1)*ny ; id+=nx) {

    	bmap["X0"].push_back(id);
	
    	bmap["X1"].push_back(id + nx - 1);

    }


    // Move over Y-boundary points
    for( uint id = 0 ; id < nx ; id++) {

    	bmap["Y0"].push_back(id);
	
    	bmap["Y1"].push_back(id + (nx-1)*ny);


	// Assign periodic neighbours
	for( uint velId = 1 ; velId < Q ; velId++ ) {

	    if(neigh[id][velId] == -1) {

		neigh[id][velId] = neigh[id + (nx-1)*ny][velId];

	    }

	    if(neigh[id+(nx-1)*ny][velId] == -1) {

		neigh[id + (nx-1)*ny][velId] = neigh[id][velId];

	    }
	    
	}	

    }    


    return bmap;
    
}
