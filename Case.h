#ifndef PRJ_CASE_H
#define PRJ_CASE_H


#include <iostream>

#include <vector>
#include <utility>

#include "Particule.h"

class Case : public std::vector< std::pair< unsigned int, unsigned int > >{ 
	
// Une case est une liste de paires d'entiers : 
// ces paires sont formées d'un numéro de faisceau dans l'accélérateur et d'un numéro de particule dans le faisceau
// Une particule est donc représentée par une paire d'entiers
	
protected:
	
	Case* c_suivant; // représente la case suivante dans la chaîne de l'accélérateur
	
	Case* c_precedent; // représente la case précédente
	
public:
	
	void pop (unsigned int const&, unsigned int const&);
	
	void setSuivant(Case* suivant);
	
	Case* getSuivant()const;
	
	void setPrecedent(Case* pre);
	
	Case* getPrecedent()const;
	
	virtual ~Case();
	
};

#endif

