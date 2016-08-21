#include <pdf.h>
#include <iostream>

using namespace std;

// Overloaded operator <<
ostream& operator<<(ostream& os, const pdf& c) {

    os << "( ";
    for(vector<double>::const_iterator it = c.begin() ; it != c.end() ; it++) {
    	os << *it << " ";
    }
    os << ")";

    return os;

}

// Overloaded operator <<
istream& operator >> (istream& is, pdf& c) {

    string aux;

    // Read "("
    is >> aux;
    
    is >> aux;
    while ( aux.find(")") == string::npos ) {
    	c.push_back( stod(aux) );
    	is >> aux;
    }

    return is;
    
}




// Reduce Operation (sum all elements)
const double pdf::reduce() {
    double sum = 0;
    for(vector<double>::const_iterator it = this->begin() ; it != this->end() ; it++) {
    	sum += *it;
    }
    return sum;
}
    

// Reduce Operation. Sum all elements weighting wits Vector3
const Vector3 pdf::reduce(const vector<Vector3>& v, const double& w) {

    Vector3 sum(0,0,0);

    if(this->size() != v.size()) {
	cout << endl << "*******ERROR*******" << endl << "Unable to reduce vectors" << endl << endl;
	exit(1);
    }
    else {
	vector<Vector3>::const_iterator vit = v.begin();
	for(vector<double>::const_iterator it = this->begin() ; it != this->end() ; it++) {
		sum += (*vit)*(*it)*w;
		vit++;
	}
    }
    
    return sum;
    
}







// Overloaded operators

// Addition
const pdf pdf::operator+ (const pdf& rv) const {

    pdf a;
    a.resize( rv.size() );
    
    if(rv.size() == size()) {
	for(uint i = 0 ; i < rv.size() ; i++) {
	    a[i] = rv[i] + at(i);
	}
    }
    else {
	cout << endl << "******ERROR******" << endl << "Unable to add pdfs. Size mismatch" << endl << endl;
	exit(1);
    }

    return a;
    
}



// Substraction
const pdf pdf::operator- (const pdf& rv) const {

    pdf a;
    a.resize( rv.size() );
    
    if(rv.size() == size()) {
	for(uint i = 0 ; i < rv.size() ; i++) {
	    a[i] = at(i) - rv[i];
	}
    }
    else {
	cout << endl << "******ERROR******" << endl << "Unable to substract pdfs. Size mismatch" << endl << endl;
	exit(1);
    }

    return a;
    
}


// Product by scalar
const pdf pdf::operator* (const scalar& sc) const {
    pdf a;
    a.resize(size());
    for(uint i = 0 ; i < size() ; i++) {
	a[i] = sc * at(i);
    }
    return a;
}

