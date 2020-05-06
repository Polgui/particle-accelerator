
#include "Case.h"
#include <iostream>

using namespace std;

Case::~Case() {}

void Case::setSuivant(Case* suivant) {
	
	c_suivant = suivant;
	
}

Case* Case::getSuivant()const{
	return c_suivant;
}

void Case::setPrecedent(Case* pre) {
	
	c_precedent = pre;
	
}

Case* Case::getPrecedent()const{
	return c_precedent;
}

void Case::pop (unsigned int const& a, unsigned int const& b) {

	for (unsigned int i(0); i < size(); ++i) {
		
		if ((*this)[i].first == a && (*this)[i].second == b) {
		
			(*this)[i] = (*this)[size()-1];
			
			pop_back();
			
			return;
		
		}
		
	}

}
