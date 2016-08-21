#include <iostream>
#include <IOPatch.h>
#include <Time.h>
#include <LBModelCreator.h>

using namespace std;

int main() {

    LBModelCreator mc;
    
    basicLBModel* lbm = mc.create("D2Q9");
    
    IOPatch<int> parche(lbm,10000000);

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



    // Create boundaries
    map<string, vector<uint> > boundaries;
    for(uint i = 0 ; i < 9 ; i++) {

	if(i < 3)
	    boundaries["Y0"].push_back(i);

	if(i > 5)
	    boundaries["Y1"].push_back(i);	
	
    }
    
    

    
    // Communication patches
    vector< IOPatch<int> > parches;
    parches.push_back( IOPatch<int>(lbm) );
    parches.push_back( IOPatch<int>(lbm) );

    parches[0].setId(0);
    parches[1].setId(1);


    // Assign neighbours
    for(vector< IOPatch<int> >::iterator it = parches.begin() ; it != parches.end() ; it++)
    	it->setGlobalNeighbours( neigh, pid );

    // Assign boundaries
    for(vector< IOPatch<int> >::iterator it = parches.begin() ; it != parches.end() ; it++)
    	it->setGlobalBdMap( boundaries );    

    // Assign local values
    for(vector< IOPatch<int> >::iterator pit = parches.begin() ; pit != parches.end() ; pit++){
    	for(basicPatch_iterator<int> it = pit->begin() ; it != pit->end() ; ++it) {
    	    it.setValue( 1000*pit->id() );
    	}
    }

    // Set send maps
    for(uint i = 0 ; i < parches.size() ; i++) {

    	for(uint j = 0 ; j < parches.size() ; j++) {

    	    if( i != j ) {

    		parches[i].setSendMap( parches[j].id(), parches[j].ghostRecvGId( parches[i].id() ) );
		
    	    }
	    
    	}
	
    }


    // Send ghost values
    for(uint i = 0 ; i < parches.size() ; i++) {

    	for(uint j = 0 ; j < parches.size() ; j++) {

    	    if( i != j ) {

    		parches[i].recvGhostValues( parches[j].id(), parches[j].sendGhostValues( parches[i].id() ) );
		
    	    }
	    
    	}
	
    }    


    
    
    // Write patch information
    for(uint pid = 0 ; pid < parches.size() ; pid++) {

    	ostringstream folderName;
    	folderName << pid;

    	// Local values
    	parches[pid].writeLocalValues(  folderName.str(), folderName.str()  );

    	// Neighbours
    	parches[pid].writeNeighboursIds(  "neighbours", folderName.str() );

    	// Global Ids, local nodes
    	parches[pid].writeGlobalIdLocal(  "globalIds", folderName.str() );

    	// Global indices, ghost nodes
    	parches[pid].writeGlobalIdGhost(  "globalGhostsIds", folderName.str() );	

    	// Recv map indices
    	parches[pid].writeRecvMapsIds(  "recvMapIds", folderName.str() );

    	// Send map indices
    	parches[pid].writeSendMapsIds(  "sendMapIds", folderName.str() );

    	// Boundaries indices
    	parches[pid].writeBoundariesIds(  "boundary", folderName.str() );		
	
    }





    // New patches that read information
    vector< IOPatch<int> > nuevosParches;
    nuevosParches.push_back( IOPatch<int>(lbm) );
    nuevosParches.push_back( IOPatch<int>(lbm) );

    nuevosParches[0].setId(0);
    nuevosParches[1].setId(1);


    // Read patch information
    for(uint pid = 0 ; pid < nuevosParches.size() ; pid++) {

	ostringstream folderName;
	folderName << pid;

	// Neighbours
	nuevosParches[pid].readNeighboursIds(  "neighbours", folderName.str() );

	// Global Ids, local nodes
	nuevosParches[pid].readGlobalIdLocal(  "globalIds", folderName.str() );	

	// Global indices, ghost nodes
	nuevosParches[pid].readGlobalIdGhost(  "globalGhostsIds", folderName.str() );

	// neighbour linked list
	nuevosParches[pid].setNeighLinkedList();	

	// Recv map indices
	nuevosParches[pid].readRecvMapsIds(  "recvMapIds", folderName.str() );

	// Send map indices
	nuevosParches[pid].readSendMapsIds(  "sendMapIds", folderName.str() );

	// Boundaries indices
	nuevosParches[pid].readBoundariesIds(  "boundary", folderName.str() );

	// Local values
	nuevosParches[pid].readLocalValues(  folderName.str(), folderName.str()  );
	
    }


    // Send ghost values
    for(uint i = 0 ; i < nuevosParches.size() ; i++) {

    	for(uint j = 0 ; j < nuevosParches.size() ; j++) {

    	    if( i != j ) {

    		nuevosParches[i].recvGhostValues( nuevosParches[j].id(), nuevosParches[j].sendGhostValues( nuevosParches[i].id() ) );
		
    	    }
	    
    	}
	
    }


    // Access using iterators
    cout << endl << "Originales" << endl;
    for(uint pid = 0 ; pid < parches.size() ; pid++) {
	
    	cout << endl;
	
    	for(lbPatch_iterator<int> it = parches[pid].begin() ; it != parches[pid].end() ; ++it) {
	    
    	    for(vector< pair<uint, int*> >::iterator neighIt = it.neighBegin() ; neighIt != it.neighEnd() ; ++neighIt) {
		
    		cout << "(" << neighIt->first << ")" << *(neighIt->second) << "   " ;
		
    	    }
	    
    	    cout << endl;
	    
    	}
	
    	cout << endl;
	
    }    


    // Access using iterators
    cout << endl << "Lectura" << endl;
    for(uint pid = 0 ; pid < nuevosParches.size() ; pid++) {
	
    	cout << endl;
	
    	for(lbPatch_iterator<int> it = nuevosParches[pid].begin() ; it != nuevosParches[pid].end() ; ++it) {
	    
    	    for(vector< pair<uint, int*> >::iterator neighIt = it.neighBegin() ; neighIt != it.neighEnd() ; ++neighIt) {
		
    	    	cout << "(" << neighIt->first << ")" << *(neighIt->second) << "   " ;
		
    	    }
	    
    	    cout << endl;
	    
    	}
	
    	cout << endl;
	
    } 
    
    

    
    return 0;

}
