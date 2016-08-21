#include <iostream>
#include <boundaryPatch.h>
#include <Time.h>
#include <LBModelCreator.h>

using namespace std;

int main() {

    LBModelCreator mc;
    
    basicLBModel* lbm = mc.create("D2Q9");
    
    boundaryPatch<int> parche(lbm,10000000);

    Time runTime;
    
    for(int i = 0 ; i < 500 ; i++) {
    	for(lbPatch_iterator<int> it = parche.begin() ; it != parche.end() ; ++it) {
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
    boundaryPatch<int> bdpatch(lbm);
    bdpatch.setId(0);
    bdpatch.setGlobalNeighbours( neigh, pid );


    
    return 0;

}
