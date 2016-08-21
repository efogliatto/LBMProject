#include <iostream>
#include <basicPatch.h>
#include <testPatch.h>
#include <Time.h>

using namespace std;

int main() {

    basicPatch<int> parche(10000000);
    testPatch<int> basico;

    basico.resizeLocal(10000000);
  

    Time runTime;
    
    for(int i = 0 ; i < 500 ; i++) {
    	for(vector<int>::iterator it = basico.localBegin() ; it != basico.localEnd() ; ++it) 
    	    *it = i;
    }

    cout << "Basico:   " << runTime.elapsedTime() << endl;



    
    
    Time runTime2;
    
    for(int i = 0 ; i < 500 ; i++) {
    	for(basicPatch_iterator<int> it = parche.begin() ; it != parche.end() ; ++it) {
    	    it.setValue(i);
    	}
    }

    cout << "Nuevo:   " << runTime2.elapsedTime() << endl;    

    
    
    return 0;

}
