
#ifndef PRJ_DESSINABLE_H
#define PRJ_DESSINABLE_H


#include <iostream>

class Dessinable {
	
	public :
	
	virtual void dessine(std::ostream& out) const=0;
	
	virtual void dessine() const =0;

	virtual ~Dessinable() =0;
	
	
	
};

#endif

