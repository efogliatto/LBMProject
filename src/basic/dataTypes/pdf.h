#ifndef PDF_H
#define PDF_H

#include <vector>
#include <iostream>
#include <istream>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/serialization/vector.hpp>
#include <Vector3.h>

class pdf : public std::vector<double> {


    
    friend class boost::serialization::access;
    
    template<class Archive>
    void serialize(Archive & ar, const unsigned int version)
    {
	ar & boost::serialization::base_object<vector<double>>(*this);
    }
    
public:
    
    // Overloaded operator <<
    friend std::ostream& operator<<(std::ostream& os, const pdf& c);
    
    // Overloaded operator <<
    friend std::istream& operator >> (std::istream& is, pdf& c);


    // Reduce Operation (sum all elements)
    const double reduce();

    // Reduce Operation. Sum all elements weighting wits Vector3
    const Vector3 reduce(const std::vector<Vector3>& v, const double& w = 1);


    
    // Overloaded operators

    // Addition
    const pdf operator+ (const pdf& rv) const;

    // Substraction
    const pdf operator- (const pdf& rv) const;

    // Product by scalar
    const pdf operator* (const double& sc) const;    
    
    
};

#endif // PDF_H
