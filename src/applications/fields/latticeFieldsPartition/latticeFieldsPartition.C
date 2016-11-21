/*
  latticeFieldPartition
 */

#include <iostream>
#include <Time.h>
#include <LBModelCreator.h>
#include <IOPatch.h>
#include <boost/program_options.hpp>
#include <vtkPatchWriter.h>
#include <fieldShape.h>

using namespace std;


int main(int argc, char** argv) {


    
    // ******************************************************************** //
    //                            Program options                           //
    // ******************************************************************** //

    // Define and parse the program options  
    namespace po = boost::program_options; 
    po::options_description desc("Options"); 
    desc.add_options() 
        ("help,h", "Print help messages")
	("DQmodel,d", po::value<string>()->required(), "LBM model type (D dimensions with Q velocities)")
	("processors,n", po::value<int>()->required(), "number of processors");

    po::variables_map vm;
    po::store(po::parse_command_line(argc, argv, desc), vm);
 
    // --help option  
    if ( vm.count("help")  ) 
    { 
        cout << endl << "Field partition" << endl << endl
	     << desc << std::endl; 
        return 0; 
    } 



    cout << endl;
    cout << "FIELDS PARTITIONING" << endl;
    
    Time runTime;





    
    // Read fields list
    dictionary initFieldsDict("properties/startFields");
    vector<string> fieldsList = initFieldsDict.lookUpEntryList<string>("fields/valuesList");

    // Read fields list for setFields
    dictionary setFieldsDict("properties/setFieldDict");
    vector<string> changeFields = setFieldsDict.lookUpEntryList<string>("Fields/valuesList");

    
    // Move over fields list and read type
    vector<string> fieldsType;
    for( vector<string>::const_iterator field = fieldsList.begin() ; field != fieldsList.end() ; field++ )
	fieldsType.push_back(   initFieldsDict.lookUpEntry<string>( *field + "/type" )   );

    LBModelCreator mcreator;
    basicLBModel* lbm = mcreator.create( vm["DQmodel"].as<string>() );
    



   

    // Split of processors
    const uint np = vm["processors"].as<int>();

    for(uint pid = 0 ; pid < np ; pid++) {

	cout << endl << "processor" << pid << ":" << endl;
	
	// Create writer
	vtkPatchWriter writer( runTime, pid, np, vm["DQmodel"].as<string>(), true );

	// Field container
	vector< pair<string, IOPatch<double>> >  scalarFields;
	vector< pair<string, IOPatch<Vector3>> > vectorFields;
	vector< pair<string, IOPatch<pdf>> >     pdfFields;

	// Points list
	ostringstream pointsFile;
	pointsFile << "processor" << pid << "/" << lbm->name() << "_lattice/points";
	ifstream inFile;
	inFile.open( pointsFile.str().c_str() );
	uint psize;
	inFile >> psize;
	vector<Vector3> meshPoints(psize);
	for(uint i = 0 ; i < psize ; i++)
	    inFile >> meshPoints[i];

	inFile.close();

	

	// Move over fields list, read value properties, set values and add to writer
	for(uint fid = 0 ; fid < fieldsList.size() ; fid++){


	    ostringstream folderName;
	    folderName << "processor" << pid << "/" << lbm->name() << "_lattice";

	    cout << "    " << fieldsList[fid] << endl;
	    
	    
	    if( fieldsType[fid].compare("latticeScalarField") == 0 ) {

		// Read value
		const double value = initFieldsDict.lookUpEntry<double>( fieldsList[fid] + "/value" );

		// Create patch
		IOPatch<double> fld(lbm);
		fld.setId(pid);

		// Read patch structure
		fld.readNeighboursIds(  "neighbours", folderName.str() );
		fld.readGlobalIdGhost(  "globalGhostsIds", folderName.str() );
		fld.readBoundariesIds(  "boundary", folderName.str() );
		fld.readBoundaryConditions(  fieldsList[fid], "start", true );

		// // Set local values
		// for(lbPatch_iterator<double> pt = fld.begin() ; pt != fld.end() ; ++pt)
		//     *pt = value;

		// // Set ghost values
		// for(vector<double>::iterator pt = fld.ghostBegin() ; pt != fld.ghostEnd() ; ++pt)
		//     *pt = value;

		
		// Set values using shapes
		if(  find( changeFields.begin(), changeFields.end(), fieldsList[fid] ) != changeFields.end()  ) {

		    string fnc = setFieldsDict.lookUpEntry<string>( fieldsList[fid] + "/function");

		    if( fnc.compare("none") == 0 ) {
		    
		    
			// Read list of shapes for this field
			vector<string> snames = setFieldsDict.lookUpEntryList<string>( fieldsList[fid] + "/shapesList");

			// Create map for this shapes
			vector<fieldShape> shMap;

			// Set values for each shape
			for(auto sn : snames) {    shMap.push_back( fieldShape("properties/setFieldDict", sn) );     }

		    
			uint pointId(0);
		    
			// Set local values
			for(lbPatch_iterator<double> pt = fld.begin() ; pt != fld.end() ; ++pt) {

			    double val(0);
			    int count(0);

			    // Set values for each shape
			    for(uint shid = 0 ; shid < shMap.size() ; shid++) {

				if( shMap[shid].locatePoint( meshPoints[pointId] ) ) {

				    val += shMap[shid].fieldValue( fieldsList[fid], meshPoints[pointId], *pt);
				    count++;

				}


			    }
			
			
			    // *pt = val / snames.size();

			    if(count == 0) {
				*pt = value;
			    }
			    else {			    
				*pt = val / count;
			    }
						    
			
			    pointId++;
			
			}


			// Set ghost values
			for(vector<double>::iterator pt = fld.ghostBegin() ; pt != fld.ghostEnd() ; ++pt) {


			    double val(0);
			    int count(0);

			    // Set values for each shape
			    for(uint shid = 0 ; shid < shMap.size() ; shid++) {

				if( shMap[shid].locatePoint( meshPoints[pointId] ) ) {

				    val += shMap[shid].fieldValue( fieldsList[fid], meshPoints[pointId], *pt);
				    count++;

				}


			    }
			
			
			    // *pt = val / snames.size();

			    if(count == 0) {
				*pt = value;
			    }
			    else {			    
				*pt = val / count;
			    }
						    
			
			    pointId++;
			

			    // double val(0);

			    // // Set values for each shape
			    // for(uint shid = 0 ; shid < shMap.size() ; shid++) {
		    
			    //     val += shMap[shid].fieldValue( fieldsList[fid], meshPoints[pointId], *pt);

			    // }
			
			
			    // *pt = val / snames.size();
			
			    // pointId++;
			
			}


		    }

		    else {
		    
		    
			fieldShape shape("properties/setFieldDict");

			uint pointId(0);

			// Set local values
			for(lbPatch_iterator<double> pt = fld.begin() ; pt != fld.end() ; ++pt) {
			    *pt = shape.fieldValue( fieldsList[fid], meshPoints[pointId], *pt);
			    pointId++;
			}

			// Set ghost values
			for(vector<double>::iterator pt = fld.ghostBegin() ; pt != fld.ghostEnd() ; ++pt) {
			    *pt = shape.fieldValue( fieldsList[fid], meshPoints[pointId], *pt);
			    pointId++;
			}			

		    }


		    
		    
		}
		
		
		    
		// Add field to container
		scalarFields.push_back( std::make_pair(fieldsList[fid],fld) );
		    
	    }




	    
	    else {

		if( fieldsType[fid].compare("latticeVectorField") == 0 ) {

		    
		    // Read value
		    const Vector3 value = initFieldsDict.lookUpEntry<Vector3>( fieldsList[fid] + "/value" );

		    // Create patch
		    IOPatch<Vector3> fld(lbm);
		    fld.setId(pid);

		    // Read patch structure
		    fld.readNeighboursIds(  "neighbours", folderName.str() );
		    fld.readGlobalIdGhost(  "globalGhostsIds", folderName.str() );
		    fld.readBoundariesIds(  "boundary", folderName.str() );
		    fld.readBoundaryConditions(  fieldsList[fid], "start", true );
		    

		    // // Set local values
		    // for(lbPatch_iterator<Vector3> pt = fld.begin() ; pt != fld.end() ; ++pt)
		    // 	*pt = value;

		    // // Set ghost values
		    // for(vector<Vector3>::iterator pt = fld.ghostBegin() ; pt != fld.ghostEnd() ; ++pt)
		    // 	*pt = value;
		    



		    
		    // Set values using shapes
		    if(  find( changeFields.begin(), changeFields.end(), fieldsList[fid] ) != changeFields.end()  ) {
		    
		    
			// Read list of shapes for this field
			vector<string> snames = setFieldsDict.lookUpEntryList<string>( fieldsList[fid] + "/shapesList");

			// Create map for this shapes
			vector<fieldShape> shMap;

			// Set values for each shape
			for(auto sn : snames) {    shMap.push_back( fieldShape("properties/setFieldDict", sn) );     }

		    
			uint pointId(0);
		    
			// Set local values
			for(lbPatch_iterator<Vector3> pt = fld.begin() ; pt != fld.end() ; ++pt) {

			    Vector3 val(0,0,0);

			    // Set values for each shape
			    for(uint shid = 0 ; shid < shMap.size() ; shid++) {
		    
			    	val += shMap[shid].fieldValue( fieldsList[fid], meshPoints[pointId], *pt);

			    }
			
			
			    *pt = val / snames.size();


			    
			    // double vx(0),vy(0),vz(0);

			    // // Set values for each shape
			    // for(uint shid = 0 ; shid < shMap.size() ; shid++) {
		    
			    // 	vx += shMap[shid].fieldValue( fieldsList[fid], meshPoints[pointId], (*pt).x() );
			    // 	vy += shMap[shid].fieldValue( fieldsList[fid], meshPoints[pointId], (*pt).y() );
			    // 	vz += shMap[shid].fieldValue( fieldsList[fid], meshPoints[pointId], (*pt).z() );
				

			    // }
			
			
			    // *pt = Vector3(vx,vy,vz) / snames.size();


			    
			    pointId++;
			
			}


			// Set Ghost values
			for(vector<Vector3>::iterator pt = fld.ghostBegin() ; pt != fld.ghostEnd() ; ++pt) {

			    Vector3 val(0,0,0);

			    // Set values for each shape
			    for(uint shid = 0 ; shid < shMap.size() ; shid++) {
		    
			    	val += shMap[shid].fieldValue( fieldsList[fid], meshPoints[pointId], *pt);

			    }
			
			
			    *pt = val / snames.size();


			    // double vx(0),vy(0),vz(0);

			    // // Set values for each shape
			    // for(uint shid = 0 ; shid < shMap.size() ; shid++) {
		    
			    // 	vx += shMap[shid].fieldValue( fieldsList[fid], meshPoints[pointId], (*pt).x() );
			    // 	vy += shMap[shid].fieldValue( fieldsList[fid], meshPoints[pointId], (*pt).y() );
			    // 	vz += shMap[shid].fieldValue( fieldsList[fid], meshPoints[pointId], (*pt).z() );
				

			    // }
			
			
			    // *pt = Vector3(vx,vy,vz) / snames.size();
			    
			    
			
			    pointId++;
			
			}			

		    }

		    

		    // Add field to container
		    vectorFields.push_back( std::make_pair(fieldsList[fid],fld) );
		    
		}




		
		else {

		    if( fieldsType[fid].compare("latticePdfField") == 0 ) {

			// Read value
			const pdf value = initFieldsDict.lookUpEntry<pdf>( fieldsList[fid] + "/value" );

			// Create patch
			IOPatch<pdf> fld(lbm);
			fld.setId(pid);

			// Read patch structure
			fld.readNeighboursIds(  "neighbours", folderName.str() );
			fld.readGlobalIdGhost(  "globalGhostsIds", folderName.str() );

			// Set local values
			for(lbPatch_iterator<pdf> pt = fld.begin() ; pt != fld.end() ; ++pt)
			    *pt = value;

			// Set ghost values
			for(vector<pdf>::iterator pt = fld.ghostBegin() ; pt != fld.ghostEnd() ; ++pt)
			    *pt = value;







		    // Set values using shapes
		    if(  find( changeFields.begin(), changeFields.end(), fieldsList[fid] ) != changeFields.end()  ) {
		    
		    
			// Read list of shapes for this field
			vector<string> snames = setFieldsDict.lookUpEntryList<string>( fieldsList[fid] + "/shapesList");

			// Create map for this shapes
			vector<fieldShape> shMap;

			// Set values for each shape
			for(auto sn : snames) {    shMap.push_back( fieldShape("properties/setFieldDict", sn) );     }

		    

			uint pointId(0);
		    
			// Set local values
			for(lbPatch_iterator<pdf> pt = fld.begin() ; pt != fld.end() ; ++pt) {

			    pdf val;
			    

			    // Set values for each shape
			    for(uint shid = 0 ; shid < shMap.size() ; shid++) {

				if( shMap[shid].locatePoint( meshPoints[pointId] ) ) {

				    val = shMap[shid].fieldValue( fieldsList[fid], meshPoints[pointId], *pt);

				}


			    }
						    
			
			    pointId++;
			
			}


			// Set ghost values
			for(vector<pdf>::iterator pt = fld.ghostBegin() ; pt != fld.ghostEnd() ; ++pt) {


			    pdf val;
			    int count(0);

			    // Set values for each shape
			    for(uint shid = 0 ; shid < shMap.size() ; shid++) {

				if( shMap[shid].locatePoint( meshPoints[pointId] ) ) {

				    val = shMap[shid].fieldValue( fieldsList[fid], meshPoints[pointId], *pt);
				    count++;

				}


			    }

						    
			
			    pointId++;

			
			}
			

		    }




			

			
			// Add field to container
			pdfFields.push_back( std::make_pair(fieldsList[fid],fld) );			

		    }

		}

	    }

	}






	// Link fields with writer
	for(uint i = 0 ; i < scalarFields.size() ; i++)
	    writer.add( &scalarFields[i].second, scalarFields[i].first );

	for(uint i = 0 ; i < vectorFields.size() ; i++)
	    writer.add( &vectorFields[i].second, vectorFields[i].first );

	for(uint i = 0 ; i < pdfFields.size() ; i++)
	    writer.add( &pdfFields[i].second, pdfFields[i].first );


	// Write fields
	writer.write();

    }



    cout << endl << "Finished fields decomposition" << endl << endl;

    
    return 0;


}
