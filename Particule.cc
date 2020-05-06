#include <iostream>
#include <cmath>
#include "Particule.h"
#include "Couleur.h"


using namespace std;

double Particule::c = 299792458;

double Particule::e = 1.6021765*1e-19;

Particule::Particule (double x, double y, double z , double dx , double dy , double dz , //dx, dy et dz sont les qdm
		   double masse , double charge , double fx , double fy , double fz )
{
	
	m_position.setX(x);
	m_position.setY(y);
	m_position.setZ(z);
	m_qdm.setX(dx);
	m_qdm.setY(dy);
	m_qdm.setZ(dz);
	m_masse = masse;
	m_charge = charge;
	m_force.setX(fx);
	m_force.setY(fy);
	m_force.setZ(fz); 


}

Particule::Particule (Vecteur3D position, Vecteur3D qdm, double masse, double charge, Vecteur3D force) {

	m_position = position;
	m_qdm = qdm;
	m_masse = masse;
	m_charge = charge;
	m_force = force;
	

}

Particule::Particule (Vecteur3D position, double ener, Vecteur3D direction, double masse, double charge, Vecteur3D force) {
	
	m_position = position;
	m_masse = masse;
	m_charge = charge;
	m_force = force;
	
	double gamm; // le facteur gamma
	
	gamm = ener/m_masse; //car E = gamma * m * c^2 en SI 
	
	
	Vecteur3D vitesse;
	
	vitesse = (~direction)*(c * sqrt(1 -	(m_masse*m_masse)/(ener*ener)	));// car gamma = 1 / racine (1 - v^2/c^2)
	
	
	m_qdm = vitesse * (m_masse / sqrt(	(c*c) - (vitesse.norme_carre())	));
	
	
}

void Particule::dessine(ostream& out) const{

	out << *this;

}

double Particule::gamma() const{

	return 1/sqrt(1-(vitesse().norme_carre() / (c*c)));

}
				  
				  
double Particule::eng() const{

	return gamma() * m_masse;

}

Vecteur3D Particule::vitesse()const {
	
	return m_qdm * (c/sqrt(m_masse*m_masse + m_qdm.norme_carre()));
	
	}


void Particule::ajouteForceMagnetique (Vecteur3D const& B, double const& dt) { // ajoute une force magnétique en fonction du champ magnétique
	
	Vecteur3D forcemagn((vitesse() ^ B) * m_charge);
	
	forcemagn.rotation(vitesse() ^ forcemagn, asin (dt * sqrt(forcemagn.norme_carre()) / (2 * gamma() * m_masse * sqrt(vitesse().norme_carre()))));
	
	m_force += forcemagn;
	
}

void Particule::ajouteForceElectrique (Vecteur3D const& E) { // ajoute une force électrique en fonction du champ électrique

	m_force += E * m_charge;
	
}

void Particule::ajouteForceInter (Particule const& part) { // ajoute une force inter-particule avec part
	
	m_force += (m_position - part.m_position) * (m_charge*m_charge / (	gamma()*gamma() * 4 * M_PI * 8.85*1e-12 * (m_position - part.m_position).norme_carre()*sqrt((m_position - part.m_position).norme_carre())	));
} 

void Particule::bouger (double const& dt) {

	m_qdm += m_force * (dt * c /(e * 1e9));
		
	m_position += vitesse() *dt;
	
	m_force = Vecteur3D();

}

Particule Particule::operator * (double const& scal) const {
	
	Particule part(m_position, m_qdm * scal, m_masse * scal, m_charge * scal, Vecteur3D());
	
	return part;
	
}


Particule::~Particule(){}

void Particule::dessine() const
{
	
	GLUquadric* quadrique=gluNewQuadric();
	glPushMatrix();
	
	glTranslated(m_position.getX(),m_position.getY(),m_position.getZ());
    
    glColor4d(Couleur::Bleu.getRouge(),Couleur::Bleu.getVert(),Couleur::Bleu.getBleu(), 0);
    gluQuadricDrawStyle(quadrique, GLU_FILL);
    gluSphere(quadrique,0.005,15,15);
	
    glPopMatrix();
	gluDeleteQuadric(quadrique);	
	
}

ostream& operator<< (ostream& sortie, Particule const& particule) {
	
	sortie << "Se trouve dans un(e) : " << (*(particule.m_element)).type() << endl <<
	"Position [m] : " << particule.m_position << endl <<
	"Quantité de mouvement [GeV/c] : " << particule.m_qdm << endl <<
	"Vitesse [m/s] : " << particule.vitesse() << endl <<
	"Gamma : " << particule.gamma() << endl <<
	"Energie [GeV] : " << particule.eng() << endl<<
	"Masse [GeV/c^2] : " << particule.m_masse << endl <<
	"Charge [C] : " << particule.m_charge << endl <<
	"Force [N] : " << particule.m_force << endl;
	
	return sortie;
}

Vecteur3D Particule::getPosition () const {return m_position;}

void Particule::setPosition(Vecteur3D const& pos) {m_position = pos;}

void Particule::setQDM(Vecteur3D const& qdm) {m_qdm = qdm;}

void Particule::setMasse(double const& masse) {m_masse = masse;}

void Particule::setCharge (double const& charge) {m_charge = charge;}

double Particule::getMasse() const {return m_masse;}

double Particule::getCharge() const {return m_charge;}

Element* Particule::getElement() const{return m_element;}

void Particule::setElement(Element* element) {m_element = element;}

Case* Particule::getCase() const{return m_case;}

void Particule::setCase(Case* cas) {m_case = cas;}


