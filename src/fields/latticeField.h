#ifndef LATTICEFIELD_H
#define LATTICEFIELD_H

#include <mpiPatch.h>
#include <Time.h>


template<typename T>
class latticeField : public mpiPatch<T> {
    
    
    /* ----------------------  Protected members ----------------------  */

protected:
    
    // Field name
    const std::string _name;

    // Reference to time
    const Time& _time;

    // Lattice velocity
    double _c;

    // Lattice speed of sound (square)
    double _cs2;

    // Lattice size
    double _lsize;

    


    
    /* ----------------------  Public members ----------------------  */


public:
    
    // Constructors and destructors

    // Constructor wit references
    latticeField( basicLBModel* lbm, mpi::environment& env, mpi::communicator& world, const std::string& name, const Time& time, const bool& read = true );

    // Default destructor
    ~latticeField();




    // Field name
    const std::string& name() const {	return _name;    }
    
    
};




// Constructors and destructors

// Constructor with references
template<typename T>
latticeField<T>::latticeField(  basicLBModel* lbm,
				mpi::environment& env,
				mpi::communicator& world,
				const std::string& name,
				const Time& time,
				const bool& read ) : mpiPatch<T>(lbm,env,world), _name(name), _time(time)   {


    if(this->_world.rank() == 0) {
	std::cout << std::endl << "Reading field " << this->_name << std::endl << std::endl;
    }


    // Synchronize ghost values
    mpiPatch<T>::syncSkeletons();
    
    // Read values from start time
    if(read) {
	/* mpiPatch<T>::readValues( this->_name, this->_time.startTime() ); */
	mpiPatch<T>::readValues( this->_name, this->_time.countTs() );
	mpiPatch<T>::syncGhostValues();
    }
	

    


    // Set lattice size and speed
    dictionary dict("properties/latticeProperties");
    this->_lsize = dict.lookUpEntry<double>("latticeSize");
    this->_c = this->_lsize / this->_time.timeStep();
    this->_cs2 = this->_c * this->_c * this->_lbm->cs2();
    

    
}


// Default destructor
template<typename T>
latticeField<T>::~latticeField() {}



#endif // LATTICEFIELD_H
