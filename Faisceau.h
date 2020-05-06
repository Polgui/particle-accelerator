
#ifndef PRJ_FAISCEAU_H
#define PRJ_FAISCEAU_H

#include "Particule.h"
#include "Dessinable.h"

#include <vector>
#include <iostream>

class Faisceau : public std::vector<Particule>, public Dessinable {
	
protected:
	
	Particule type; // La particule type (non existante) du faisceau
	
	double lambda; // coefficient de facteur des macros-particules
	
	double dv; // écart-type pour la vitesse
	
	double bunch; // longueur de bunch en ns (temps qu'il faut à des particules de vitesse c pour parcourir le bunch)
	
	double emittance; // On suppose emittanceR = emittanceZ
	
	double Aud; // A12 désiré, avec AudR = AudZ
	
	double Add; // A22 désiré, avec AddR = AddZ
	
	double nombre_part; // nombre de MICRO-particules que l'on veut créer au commencement du faisceau
	
	
	double moyenne(std::string const& espece) const; // dépendamment de la valeur de 'espece', retourne <r^2>, <vr^2>, <r*vr>^2, etc.
	
public:
	
	double Auu ()const; // A11
	
	Faisceau (Particule const&, double const&, double const&, double const&, double const&, double const&, double const&, double const&);
	
//	Faisceau (Particule const&, double const&);
	
	virtual ~Faisceau ();
	
	double eng() const; // énergie moyenne des particules du faisceau
	
	virtual void dessine(std::ostream& out)const;

	void dessine() const;
	
	void add_part (Particule const& part); //ajout d'une particule
	
	double emR() const; // retourne  l'émittance selon r
	
	double emZ() const; // retourne l'émittance selon z
	
	double AuuR() const; // A11 selon r
	
	double AudR() const; // A12 selon r
	
	double AddR() const; // A22 selon r
	
	double AuuZ() const; // A11 selon z
	
	double AudZ() const; // A12 selon z
	
	double AddZ() const; // A22 selon z
	
	void creation (double const& dt); // crée des particule en dt jusqu'à nombre_part
	
	
	
};

void init_hasard (unsigned int const&);

double gaussienne(double const&, double const&);

double uniforme(double const&, double const&);

#endif
