#include <iostream>
#include <commPatch.h>
#include <Time.h>
#include <LBModelCreator.h>

using namespace std;

int main() {

    LBModelCreator mc;
    
    basicLBModel* lbm = mc.create("D2Q9");
    
    lbPatch<int> parche(lbm,10000000);

    Time runTime;
    
    for(int i = 0 ; i < 500 ; i++) {
    	for(basicPatch_iterator<int> it = parche.begin() ; it != parche.end() ; ++it) {
    	    it.setValue(i);
    	}
    }

    cout << "Nuevo:   " << runTime.elapsedTime() << endl;    
    



    
    // Create neighbour indices
    vector< vector<int> > neigh;
    neigh.resize( 9 );
    for (uint i = 0 ; i < 9 ; i++) {
    	neigh[i].resize(9);
    }
    
    neigh[0] = {  0, -1, -1,  1,  3, -1, -1,  4, -1  };
    neigh[1] = {  1,  0, -1,  2,  4, -1, -1,  5,  3  };
    neigh[2] = {  2,  1, -1, -1,  5, -1, -1, -1,  4  }; 
    neigh[3] = {  3, -1,  0,  4,  6, -1,  1,  7, -1  }; 
    neigh[4] = {  4,  3,  1,  5,  7,  0,  2,  8,  6  };
    neigh[5] = {  5,  4,  2, -1,  8,  1, -1, -1,  7  };  
    neigh[6] = {  6, -1,  3,  7, -1, -1,  4, -1, -1  }; 
    neigh[7] = {  7,  6,  4,  8, -1,  3,  5, -1, -1  }; 
    neigh[8] = {  8,  7,  5, -1, -1,  4, -1, -1, -1  };

    vector<uint> pid(9);
    for(uint i = 0 ; i < 6 ; i++)
	pid[i] = 0;

    for(uint i = 6 ; i < 9 ; i++)
	pid[i] = 1;    


    // Assign neighbours
    commPatch<int> nbpatch_0(lbm);
    nbpatch_0.setId(0);
    nbpatch_0.setGlobalNeighbours( neigh, pid );

    commPatch<int> nbpatch_1(lbm);
    nbpatch_1.setId(1);
    nbpatch_1.setGlobalNeighbours( neigh, pid );
    

    // Assign values for patch 0
    for(basicPatch_iterator<int> it = nbpatch_0.begin() ; it != nbpatch_0.end() ; ++it) 
	it.setValue(1);

    // Assign values for patch 1
    for(basicPatch_iterator<int> it = nbpatch_1.begin() ; it != nbpatch_1.end() ; ++it) 
    	it.setValue(1000);


    // Set send map for patch 1
    nbpatch_1.setSendMap(0, nbpatch_0.ghostRecvGId( nbpatch_1.id() ) );

    // Send map from patch 1 to patch 0
    nbpatch_0.recvGhostValues( nbpatch_1.id(), nbpatch_1.sendGhostValues(0) );


    // Set send map for patch 0
    nbpatch_0.setSendMap(1, nbpatch_1.ghostRecvGId( nbpatch_0.id() ) );

    // Send map from patch 0 to patch 1
    nbpatch_1.recvGhostValues( nbpatch_0.id(), nbpatch_0.sendGhostValues(1) );


    // Access using iterators
    cout << endl;
    for(lbPatch_iterator<int> it = nbpatch_0.begin() ; it != nbpatch_0.end() ; ++it) {
    	for(vector< pair<uint, int*> >::iterator neighIt = it.neighBegin() ; neighIt != it.neighEnd() ; ++neighIt) {
    	    cout << "(" << neighIt->first << ")" << *(neighIt->second) << "   " ;
    	}
    	cout << endl;
    }

    cout << endl;
    for(lbPatch_iterator<int> it = nbpatch_1.begin() ; it != nbpatch_1.end() ; ++it) {
    	for(vector< pair<uint, int*> >::iterator neighIt = it.neighBegin() ; neighIt != it.neighEnd() ; ++neighIt) {
    	    cout << "(" << neighIt->first << ")" << *(neighIt->second) << "   " ;
    	}
    	cout << endl;
    }
    
    return 0;

}
