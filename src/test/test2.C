#include <iostream>
#include <lbPatch.h>
#include <testPatch.h>
#include <Time.h>
#include <LBModelCreator.h>

using namespace std;

int main() {

    LBModelCreator mc;
    
    basicLBModel* lbm = mc.create("D2Q9");
    
    lbPatch<int> parche(lbm,10000000);

    Time runTime;
    
    for(int i = 0 ; i < 500 ; i++) {
    	for(lbPatch_iterator<int> it = parche.begin() ; it != parche.end() ; ++it) {
    	    it.setValue(i);
    	}
    }

    cout << "Nuevo:   " << runTime.elapsedTime() << endl;    
    



    lbPatch<int> nbpatch(lbm);
    nbpatch.setId(0);
    
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
    nbpatch.setGlobalNeighbours( neigh, pid );
    vector< vector<int> > localNeigh_0 = nbpatch.neighbours();
    vector< vector<int> > globalNeigh_0 = nbpatch.neighbours_globalId();
    
    cout << endl;
    for(uint i = 0 ; i < localNeigh_0.size() ; i++) {
    	for(uint j = 0 ; j < lbm->Q() ; j++) {
    	    cout << globalNeigh_0[i][j] << "(" <<localNeigh_0[i][j] << ")" << "  ";
    	}
    	cout << endl;
    }
    


    lbPatch<int> nbpatch_1(lbm);
    nbpatch_1.setId(1);

    // Assign neighbours
    nbpatch_1.setGlobalNeighbours( neigh, pid );
    
    vector< vector<int> > localNeigh_1 = nbpatch_1.neighbours();
    vector< vector<int> > globalNeigh_1 = nbpatch_1.neighbours_globalId();
    
    cout << endl;
    for(uint i = 0 ; i < localNeigh_1.size() ; i++) {
    	for(uint j = 0 ; j < lbm->Q() ; j++) {
    	    cout << globalNeigh_1[i][j] << "(" <<localNeigh_1[i][j] << ")" << "  ";	    
    	}
    	cout << endl;
    }





    // Access using iterators
    cout << endl;
    for(lbPatch_iterator<int> it = nbpatch.begin() ; it != nbpatch.end() ; ++it) {
	for(vector< pair<uint, int*> >::iterator neighIt = it.neighBegin() ; neighIt != it.neighEnd() ; ++neighIt) {
	    cout << neighIt->first << "   ";
	}
	cout << endl;
    }
    
    return 0;

}
