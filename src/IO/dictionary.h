#ifndef DICTIONARY_H
#define DICTIONARY_H

#include <vector>
#include <string>
#include <sstream>
#include <Vector3.h>
#include <pdf.h>
#include <boost/tokenizer.hpp>
#include <boost/foreach.hpp>
#include <boost/algorithm/string.hpp>

using std::string;
using std::vector;


class dictionary {



    
    /* ----------------------  Private members ----------------------  */

    // String vector that contains file content
    vector<string> _fileContent;

    // File name
    std::string _fname;


    
    
    /* ----------------------  Private member functions ----------------------  */


    // Search functions
    
    // Search for entry between enclosed brackets
    const vector<string> search(const vector<string>& entryString, const string& entryName) const;
    
    // Search for single entry definition
    const string singleEntry(const vector<string>& entryString, const string& entryName) const;

    // Look up for a certain entry
    const string lookUp(const string& entry) const;



    // Basic type conversion

    // String to vector
    const void extract(Vector3& v, const string& str) const;

    // String to string
    const void extract(string& st1, const string& st2) const;

    // String to int
    const void extract(double& i, const string& str) const;

    // String to vector<double>
    const void extract(vector<double>& v, const string& str) const;

    // String to pdf
    const void extract(pdf& v, const string& str) const;    


    // Extract from iterators
    const void extract(Vector3& v, std::vector<std::string>::iterator& it) const;
    const void extract(string& st1, std::vector<std::string>::iterator& it) const;
    const void extract(double& d, std::vector<std::string>::iterator& it) const;
    const void extract(vector<double>& v, std::vector<std::string>::iterator& it) const;
    const void extract(pdf& v, std::vector<std::string>::iterator& it) const;
    


    


    /* ----------------------  Public member functions ----------------------  */

public:

    // Constructors and destructors

    // Constructor with file name
    dictionary(const string& filename);

    // Default destructor
    ~dictionary();

    

    // Access members

    // Look single entry
    template<typename T>
    	T lookUpEntry(const string& entry) const;

    // Look list
    template<typename T>
	std::vector<T> lookUpEntryList(const string& entry) const;

    // Search for entry between enclosed brackets, using _fileContent
    const vector<string> search(const string& entryName) const;
    

};







template<typename T>
T dictionary::lookUpEntry(const string& entry) const {
    
    T _a;

    string output = lookUp( entry );

    extract(_a, output);
    
    return _a;
    
}


// Look list
template<typename T>
std::vector<T> dictionary::lookUpEntryList(const string& entry) const {


    std::vector<string> outEntry;
    
    // Tokenize entry
    std::vector<string> entryTree;
    boost::char_separator<char> sep("/");
    boost::tokenizer<boost::char_separator<char>> tokens(entry, sep);
    BOOST_FOREACH (string t, tokens) {	
	entryTree.push_back(t);
    }
    
    // Search entry
    outEntry = search( _fileContent, entryTree[0] );
    for(uint id = 1 ; id < entryTree.size(); id++) {
    	    outEntry = search(outEntry, entryTree[id]);
    }

    // Create and allocate entry list
    std::vector<T> entryList;
    entryList.resize( stoi(outEntry[0]) );
    int i = 0;

    for(std::vector<string>::iterator it = outEntry.begin() + 1 ; it != outEntry.end() ; it++, i++) {
	T val;
    	extract(val,it);
    	entryList[i] = val;
    }

    return entryList;

}



#endif // DICTIONARY_H
