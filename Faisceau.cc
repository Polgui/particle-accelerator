
#include "Faisceau.h"
#include "Case.h"
#include <iostream>
#include <cmath>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

using namespace std;

Faisceau::Faisceau (Particule const& f_type, double const& f_lambda, double const& f_dv, 
					double const& f_bunch, double const& f_em, double const& f_Aud, double const& f_Add, double const& nombre) : 
type(f_type), lambda(f_lambda), dv(f_dv), bunch(f_bunch), emittance(f_em), Aud(f_Aud), Add(f_Add), nombre_part(nombre) {}

/*Faisceau::Faisceau (Particule const& f_type, double const& f_lambda) : 
 type(f_type), lambda(f_lambda) {} */

Faisceau::~Faisceau () {}

double Faisceau::eng()const { 
	
	double somme(0);

	for(unsigned int i(0); i < size(); ++i) {
	
		somme+= (*this)[i].eng();
	
	}
	
	return somme/size(); // retourne l'eng moyenne des macro-particules du faisceau

}

void Faisceau::add_part (Particule const& part){ //ajout d'une particule 
	
	push_back (part);
	
}

void Faisceau::dessine(std::ostream& out)const {
	
	out << "Coefficient de macro-particules : " << lambda << endl << 
	
	"Le faisceau contient "<< size() << " macro-particule";
	
	if (size() > 1) out << "s";
	
	out << "." << endl << endl << 
	"Energie moyenne des macro-particules du faisceau : " << eng() << endl << endl ;
	
	out << "Emmitance en r : " << emR() << ", Emmitance en z : " << emZ() << endl <<
	"A11r : " << AuuR() << ", A12r : " << AudR() << ", A22r : " << AddR() << endl <<
	"A11z : " << AuuZ() << ", A12z : " << AudZ() << ", A22z : " << AddZ() << endl << endl;
	
	for(unsigned int i(0); i < size(); ++i) {
		
		(*this)[i].dessine(out);
		
		out << endl;
		
	}
	
}

void Faisceau::dessine() const
{
	for(unsigned int i(0); i < size(); ++i) {
		
		(*this)[i].dessine();
		
	}
}

double Faisceau::moyenne(string const& espece) const{ // dépendamment de la valeur de 'espece', retourne <r^2>, <vr^2> ou <r*vr>^2 
		
		double nombre (0);
	
	if (espece == "r^2") {
		
		for(unsigned int i(0); i< size(); ++i) {
		
		nombre += 
			( (*this)[i].getPosition() ).prod_scal( ((*this)[i].getElement())->u((*this)[i]) ) 
			* 
			( (*this)[i].getPosition() ).prod_scal( ((*this)[i].getElement())->u((*this)[i]) );
		}
		
		nombre = nombre/size();
	}
	
	else if (espece == "vr^2") {
	
		for(unsigned int i(0); i< size(); ++i) {
			
			nombre += 
			( (*this)[i].vitesse() ).prod_scal( ((*this)[i].getElement())->u((*this)[i]) ) 
			* 
			( (*this)[i].vitesse() ).prod_scal( ((*this)[i].getElement())->u((*this)[i]) );
		}
		
		nombre = nombre/size();
	
	}
	
	else if (espece == "rvr") {
	
		for(unsigned int i(0); i< size(); ++i) {
			
			nombre += ( (*this)[i].getPosition() ).prod_scal( ((*this)[i].getElement())->u((*this)[i]) ) 
			* 
			( (*this)[i].vitesse() ).prod_scal( ((*this)[i].getElement())->u((*this)[i]) );
		}
		
		nombre = nombre/size();
		
	}
	
	else if (espece == "z^2") {
		
		for(unsigned int i(0); i< size(); ++i) {
		
		nombre += ((*this)[i].getPosition()).getZ() * ((*this)[i].getPosition()).getZ();
			
		}
		
		nombre = nombre/size();
		
	}
	
	else if (espece == "vz^2") {
		
		for (unsigned int i(0); i < size(); ++i) {
		
		nombre += ((*this)[i].vitesse()).getZ() * ((*this)[i].vitesse()).getZ();
			
		}
		
		nombre = nombre/size();
		
	}
	
	else if (espece == "zvz") {
		
		for (unsigned int i(0); i < size(); ++i) {
		
		nombre += ((*this)[i].getPosition()).getZ() * ((*this)[i].vitesse()).getZ();
		
		}
		
		nombre = nombre/size();
		
	}
	
	else {
	
	cerr << "ATTENTION : SPECIFICATION DE MOYENNE INCORRECTE" << endl;
	
	}
	
		return nombre;
		

}

double Faisceau::emR() const { // retourne  l'émittance selon r

	return sqrt(moyenne("r^2")*moyenne("vr^2") - moyenne("rvr")*moyenne("rvr"));
	

}

double Faisceau::emZ() const{ // retourne l'émittance selon z
	
	return sqrt(moyenne("z^2")*moyenne("vz^2") - moyenne("zvz")*moyenne("zvz"));
		

}

double Faisceau::AuuR() const { // A11 selon r

	return moyenne("vr^2")/emR();

}

double Faisceau::AudR() const{ // A12 selon r

	return - moyenne("rvr")/emR();
}

double Faisceau::AddR() const{ // A22 selon r

	return moyenne("r^2")/emR();

}

double Faisceau::AuuZ() const{ // A11 selon z

	return moyenne("vz^2")/emZ();
}

double Faisceau::AudZ() const{ // A12 selon z

	return - moyenne("zvz")/emZ();

}

double Faisceau::AddZ() const { // A22 selon z

	return moyenne("z^2")/emZ();	

}

double Faisceau::Auu()const { // A11
	
	return (1 + Aud*Aud) / Add;
	
}

void init_hasard (unsigned int const& graine) {
	
    if (graine == 0) {
		
		srand(time(0));
		
    } 
	
	else {
		
		srand(graine);
		
	}
	
}

double gaussienne(double const& moyenne, double const& ecart_type) {
	
	double v1;
	double v2;
	double s ;
	
	do {
		v1 = uniforme(-1.0, 1.0);
		v2 = uniforme(-1.0, 1.0);
		s = v1*v1 + v2*v2;
	} while ((s >= 1.0) or (s == 0.0));
	
	double x(sqrt(-2.0 * log(s) / s));
	
	if (uniforme(0.0, 1.0) > 0.5)
		x *= v1;
	else
		x *= v2;
	
	return moyenne + ecart_type * x;
	
}

double uniforme(double const& a, double const& b) {
	
 return (a + (rand() / double(RAND_MAX)) * (b - a));
	
}

void Faisceau::creation (double const& dt) { // crée nombre_part particules, à une particule tous les dt
	
	if (nombre_part <= size()) {
		return;
	}
	
	double debit (nombre_part * 1e9 / bunch); // avec dt et bunch en ns
	
	double fraction(debit*dt); // debit "vrai", mais a priori non entier
	
	int nombre(fraction);      // partie entière
	
	fraction -= nombre;        // partie fractionnaire
	
	// on ajoute 1 au  hasard, proportionnellement à la partie fractionnaire :
	
	if ( uniforme(0.0, 1.0) < fraction ) {++nombre; }
	
	
	/////////////////////////////////////////////////////////////////////////////////////
	
	double theta (atan(2*Aud / (Auu() - Add)));
	
	double a, b;
	
	a = Auu()*cos(theta)*cos(theta) + 2*Aud*cos(theta)*sin(theta) + Add*sin(theta)*sin(theta);
	
	b = Auu()*sin(theta)*sin(theta) - 2*Aud*cos(theta)*sin(theta) + Add*cos(theta)*cos(theta);
	
	
	for (int i(0); i < nombre; ++i) {
		
		Particule part(type * lambda);
		// On copie la particule type, en la multipliant par lambda (macro-particules)
		
		double x, y;
		
		double r, vr; 
		
		double z, vz;
		
		double v; // norme de la vitesse
		
		
		x = gaussienne (0, sqrt(emittance/a));
		
		y = gaussienne (0, sqrt(emittance/b));
		
		r = cos(theta)*x + sin(theta)*y;
		
		vr = -sin(theta)*x + cos(theta)*y;
			
		
		
		x = gaussienne (0, sqrt(emittance/a));
		
		y = gaussienne (0, sqrt(emittance/b));
			
		z = cos(theta)*x + sin(theta)*y;
		
		vz = -sin(theta)*x + cos(theta)*y;
			
		
		
		v = gaussienne(sqrt((type.vitesse()).norme_carre()), dv);
		
		double composante_s( gaussienne (0, bunch * 1e-9 * Particule::c / 4)); // la longueur du bunch en [m] vaut la longeur en [s] * c
			
		Vecteur3D u((type.getElement())->u(type)); // u est différent si l'élément est courbe ou droit
		
		
		Vecteur3D vit (u * vr + Element::e3 * vz + (u ^Element::e3) * sqrt(v*v - vr*vr - vz*vz)); // vecteur vitesse
		
		
		Vecteur3D dpos (u * r + Element::e3 * z + (u ^Element::e3) * composante_s); // vecteur écart de position
		
		part.setPosition(type.getPosition() + dpos); // on met la position à la particule, qui vaut la position de la particule type plus un écart
		
		part.setQDM(vit * (part.getMasse() / sqrt((Particule::c * Particule::c) - vit.norme_carre()))); // qdm = gamma * m * v en SI => qdm = gamma * m * v / c en GEV
		
		push_back(part);
		
		(*this)[size()-1].setElement(type.getElement());
		
		(*this)[size()-1].setCase(NULL);
		
	}
	
}

