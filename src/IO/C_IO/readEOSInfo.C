// Read EOS information for c-written solvers

#include <readEOSInfo.h>
#include <dictionary.h>

#ifdef __cplusplus
extern "C" {
#endif


    struct EOSInfo readEOSInfo() {

	struct EOSInfo info;

	// Read time properties
	dictionary mp("properties/macroscopicProperties");

	
	// Read model
	string eosType = mp.lookUpEntry<string>("EOS/model");

	if( eosType.compare("idealGas") == 0 ) {
	
	    info._eosIdx = 0;

	    info._R = (c_scalar)mp.lookUpEntry<double>("EOS/R");

	    info._G = (c_scalar)mp.lookUpEntry<double>("EOS/G");
	
	}
    
	else {

	    if( eosType.compare("Carnahan-Starling") == 0 ) {

		info._eosIdx = 1;

		// Carnahan - Starling constants
    
		info._a = (c_scalar)mp.lookUpEntry<double>("EOS/a");
    
		info._b = (c_scalar)mp.lookUpEntry<double>("EOS/b");
    
		info._R = (c_scalar)mp.lookUpEntry<double>("EOS/R");

		info._G = (c_scalar)mp.lookUpEntry<double>("EOS/G");
	    
	    }

	    else {

		if( eosType.compare("Peng-Robinson") == 0 ) {

		    info._eosIdx = 2;

		    // Peng-Robinson constants
    
		    info._a = (c_scalar)mp.lookUpEntry<double>("EOS/a");
    
		    info._b = (c_scalar)mp.lookUpEntry<double>("EOS/b");
    
		    info._R = (c_scalar)mp.lookUpEntry<double>("EOS/R");

		    info._G = (c_scalar)mp.lookUpEntry<double>("EOS/G");

		    info._omega = (c_scalar)mp.lookUpEntry<double>("EOS/omega");		
	    
		}


		else {

		    if( eosType.compare("vanderWaals") == 0 ) {

			info._eosIdx = 3;

			// Peng-Robinson constants
    
			info._a = (c_scalar)mp.lookUpEntry<double>("EOS/a");
    
			info._b = (c_scalar)mp.lookUpEntry<double>("EOS/b");
    
			info._R = (c_scalar)mp.lookUpEntry<double>("EOS/R");

			info._G = (c_scalar)mp.lookUpEntry<double>("EOS/G");

			info._M = (c_scalar)mp.lookUpEntry<double>("EOS/M");
	    
		    }


		    else {

			printf("\n  [ERROR]   Unrecognized EOS %s\n\n", eosType.c_str());
			exit(1);

		    }

		}			

	    }	

	}




	// Gravity
	Vector3 gravity = mp.lookUpEntry<Vector3>("EOS/g");
	info._g[0] = gravity.x();
	info._g[1] = gravity.y();
	info._g[2] = gravity.z();

	// Reference density
	info.rho_0 = mp.lookUpEntry<double>("EOS/rho_0");
    


	return info;

	
    }


#ifdef __cplusplus
}
#endif
