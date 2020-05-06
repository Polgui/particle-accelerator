
#ifndef PRJ_PARSEUR_H
#define PRJ_PARSEUR_H

#include <iostream>
#include <string>
#include <fstream>
#include "Accelerateur.h"

double str2double (std::string const&);

class Parseur {
	
protected:
	
	std::ifstream fichier;
	
	std::string chercheBalise();
	
	std::string enregistreBalise (std::string const&);
	
// Méthodes extraire
	
	void extraireSysteme (Accelerateur*);
	
	void extraireAccelerateur (Accelerateur*);
	
	void extraireTypique (Accelerateur*);
	
	void extraireFaisceau (Accelerateur*);
	
	void extraireSection (Accelerateur*);
	
	void extraireDipole (Accelerateur*);
	
	void extraireQuadrupole (Accelerateur*);
	
	void extraireSextupole (Accelerateur*);
	
	void extraireFODO (Accelerateur*);
	
	void extraireCavite (Accelerateur*);
	
// Méthodes trouve
	
	double trouveDouble(std::string const&); // renvoie le double de la balise donnée en argument
	
	Vecteur3D trouveVecteur3D(std::string const&); // renvoie le vecteur de la balise donnée en argument
	
	Particule trouveParticule(std::string const&); // renvoie la particule de la balise donnée en argument
	
public:
	
	Parseur (std::string const&);
	
	virtual ~Parseur ();
	
	void extraire (Accelerateur*);
};





#endif