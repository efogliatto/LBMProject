#include <dictionary.h>
#include <fstream>
#include <iostream>
#include <sstream>
#include <algorithm>

using namespace std;
using namespace boost;

typedef unsigned int uint;


/* ----------------------  Public member functions ----------------------  */


// Constructors and destructors

// Constructor with file name
dictionary::dictionary(const string& filename){


    // Save name
    _fname = filename;

    // Open file
    ifstream inFile;
    inFile.open(filename.c_str());
    if( inFile.is_open() == false ){
    	cout << "Cant't find file " << filename << endl;
    	exit(1);
    }

    // Read line by line, and remove comments
    string line;    
    while( !inFile.eof() ) {

	// Read line
	getline(inFile, line);

	// Check for comment mark
	if( line.find("//") ) {

	    // Split line into words and remove whitespaces
	    istringstream ss(line);
	    do {
		string sub;
		ss >> sub;
		
		if(!sub.empty()) {
		    _fileContent.push_back( sub );
		}
		
	    } while(ss);
	    
	}
	
    }


    // Close file
    inFile.close();

}

// Default destructor
dictionary::~dictionary() {}






/* ----------------------  Private member functions ----------------------  */


// Search for entry between enclosed brackets
const vector<string> dictionary::search(const vector<string>& entryString, const string& entryName) const {

    
    // Look for entry definition
    uint i = 0;
    bool find = false;
    vector<string>  entryContent;

    while( (i < entryString.size())   &&   (find == false) ) {

	// Find entry definition
	if(  (entryString.at(i).compare(entryName) == 0)   &&   ( entryString.at(i+1).compare("{") == 0 )) {
	    		
	    uint countOpen = 1,
		countClose = 0;
	    // bool find2 = false;
		
	    uint j = 2;

	    while( ((i+j) < entryString.size())   &&   (find == false)  ) {

		string word     = entryString.at(i+j);
		size_t findChar = word.find("}");

		if( findChar != string::npos ) {
		    countClose++;
		    if (countOpen == countClose) {
			find = true;
		    }
		}

		else{

		    findChar = word.find("{");
		    if( findChar != string::npos ) { countOpen++; }
		}

		
		if (countOpen != countClose) {
		    entryContent.push_back( word );
		}

		j++;
		
	    }	    

	}	

	i++;
    }



    if ( !find ) {
	cout << endl << "****** ERROR ******" << endl << endl << "Unable to find entry " << entryName << endl << endl;
	exit(1);
    }
    
    return entryContent;


}



// Search for entry between enclosed brackets
const vector<string> dictionary::search(const string& entryName) const {
    return dictionary::search(_fileContent, entryName);
}


// Search for single entry definition
const string dictionary::singleEntry(const vector<string>& entryString, const string& entryName) const {

    
    // Look for entry definition
    uint i = 0;
    bool find = false;
    string out;

    while( (i <= entryString.size())   &&   (find == false) ) {

    	string word = entryString[i];
	
    	if (   ( word.compare(entryName) == 0 )   &&   ( entryString[i+1].compare("{") != 0 )   ) {

    	    uint j = 1;
    	    while( ( (i+j) < entryString.size())   &&   (find == false) ) {

		string auxEntry = entryString[i+j];
		size_t findChar = auxEntry.find(";");
		
		if( findChar != string::npos ) {
		    auxEntry.erase(findChar);
		    find = true;
		}

		out = out + auxEntry + "  ";

		j++;
		
    	    }

	    
    	}


    	i++;
    }

    

    // Error message
    if ( !find ) {
	cout << endl << "****** ERROR ******" << endl << endl << "Unable to find entry " << entryName << endl << endl;
	exit(1);
    }

    return out;
    
}











// Access members

// Look up for a certain entry
// Entry definition can be concatenated, eg. "AAA/BBB/CCC/type" searches for something like
//AAA
//{
//  BBB
//	{
//	    CCC
//	    {
//		type XXXXXX;
//	    }
//	}
//}
const string dictionary::lookUp(const string& entry) const {

    string outEntry;
    
    // Tokenize entry
    vector<string> entryTree;
    boost::char_separator<char> sep("/");
    boost::tokenizer<boost::char_separator<char>> tokens(entry, sep);
    BOOST_FOREACH (string t, tokens) {	
	entryTree.push_back(t);
    }

    // Single entry
    vector<string> subEntry;
    if(entryTree.size() == 1) {
	outEntry = singleEntry( _fileContent, entry );
    }
    else {

	// Initial search
	subEntry = search( entryTree[0] );
	
	for(uint id = 1 ; id < entryTree.size() - 1 ; id++) {
	    
	    subEntry = search(subEntry, entryTree[id]);
	    
	}

	outEntry = singleEntry( subEntry, entryTree.back() );

    }    
    
    return outEntry;
    
}







// Basic type conversion

// String to vector
const void dictionary::extract(Vector3& v, const string& str) const {

    // Tokenize string
    vector<double> tokenized;
    boost::char_separator<char> sep("( )");
    boost::tokenizer<boost::char_separator<char>> tokens(str, sep);
    BOOST_FOREACH (string t, tokens) {	
	tokenized.push_back( stod(t) );
    }

    if( tokenized.size()!=3 ) {
	cout << endl << "Unable to convert " << str << " to Vector3" << endl << endl;
	exit(1);
    }
    else {
	v.setX( tokenized[0] );
	v.setY( tokenized[1] );
	v.setZ( tokenized[2] );
    }
    
}

// String to string
const void dictionary::extract(string& st1, const string& st2) const{
    st1 = st2;
    st1.erase(std::find_if(st1.rbegin(), st1.rend(), std::not1(std::ptr_fun<int, int>(std::isspace))).base(), st1.end());   /////// newwww
}

// String to int
const void dictionary::extract(double& i, const string& str) const{
    i = stod(str);
}


// String to vector<double>
const void dictionary::extract(vector<double>& v, const string& str) const {

    // Tokenize string    
    boost::char_separator<char> sep("( )");
    boost::tokenizer<boost::char_separator<char>> tokens(str, sep);
    BOOST_FOREACH (string t, tokens) {	
	v.push_back( stod(t) );
    }

}


// String to vector<double>
const void dictionary::extract(pdf& v, const string& str) const {

    // Tokenize string
    vector<double> tokenized;
    boost::char_separator<char> sep("( )");
    boost::tokenizer<boost::char_separator<char>> tokens(str, sep);
    BOOST_FOREACH (string t, tokens) {	
	v.push_back( stod(t) );
    }

}




// Extract from iterators
const void dictionary::extract(Vector3& v, vector<string>::iterator& it) const{

    it++;
    // cout << *it << endl;
    v.setX( stod(*it) );
    it++;
    // cout << *it << endl;
    v.setY( stod(*it) );
    it++;    
    // cout << *it << endl;
    v.setZ( stod(*it) );
    it++;
    
}


const void dictionary::extract(string& st1, vector<string>::iterator& it)  const{
    st1 = *it;
}

const void dictionary::extract(double& d, vector<string>::iterator& it) const{
    d = stod(*it);
}


const void dictionary::extract(vector<double>& v, vector<string>::iterator& it) const{

    it++;

    for(uint i = 0 ; i < v.size() ; i++) {
	v[i] = stod(*it);
    }
    
}


const void dictionary::extract(pdf& v, vector<string>::iterator& it) const{
    
    it++;

    while( it->find(")") == string::npos) {
    	v.push_back( stod(*it) );
    	it++;
    }
    
}
