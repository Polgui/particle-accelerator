#include <iostream>
#include <cmath>
#include <string>
#include "Element.h"

using namespace std;


//****************************Element****************************

Vecteur3D Element::e3 = Vecteur3D(0,0,1); 

Element::Element(Vecteur3D entree, Vecteur3D sortie, double rayon, Vecteur3D champM, Vecteur3D champE, Element* suivant) 
: e_entree(entree), e_sortie(sortie), e_rayon(rayon), e_champM(champM), e_champE(champE)
{
	e_suivant = suivant;
	
	quadrique=gluNewQuadric(); //WIDGET
}

Element::Element(Element const& autre) 
: e_entree(autre.e_entree), e_sortie(autre.e_sortie), 
e_rayon(autre.e_rayon), e_champM(autre.e_champM), e_champE(autre.e_champE),e_suivant(autre.e_suivant){}

bool Element::passe_au_suivant(const Particule& part)const{
	
	if (Element::e3.prod_mixte(part.getPosition(), e_sortie) >= 0) return true;
	
	return false;
	
}

void Element::dessine() const {}

void Element::dessine (ostream& out) const{
	
	out << "Position d'entrée : " << e_entree << endl <<
	"Position de sortie : " << e_sortie << endl <<
	"Rayon de chambre : " << e_rayon << endl <<
	"Champ magnétique uniforme : " << e_champM << endl <<
	"Champ électrique uniforme : " << e_champE << endl;
}

void Element::setSuivant(Element* suivant) {

	e_suivant = suivant;

}

Element* Element::getSuivant()const{
	return e_suivant;
}

Vecteur3D Element::getEntree() const{

	return e_entree;

}

Vecteur3D Element::getSortie() const{
	
	return e_sortie;
	
}

double Element::getRayon() const {

	return e_rayon;

}

Element::~Element(){gluDeleteQuadric (quadrique);/*WIDGET*/}

void Element::setSpecialChamp(double const& V, Particule const& typique) {}

double Element::longueur()const {
	
	// Nous dirons, par approximation, que nous ne tenons pas compte de la courbure. Etant donné que cette méthode ne nous servira que pour séparer l'accélérateur en case, cela ne nous fera que des cases parallèles
	
	return sqrt((e_sortie-e_entree).norme_carre());
}

// ****************************ElementCourbe****************************

Vecteur3D ElementCourbe::getCentre() const{
	
	return (((e_sortie + e_entree)*(1.0/2.0)) + ((~(e_sortie - e_entree) ^ Element::e3)*(1.0/e_courbure)*sqrt(1.0 - (e_courbure*e_courbure*(e_sortie-e_entree).norme_carre()/4.0))));
	
}

ElementCourbe::ElementCourbe(Vecteur3D entree, Vecteur3D sortie, double rayon, Vecteur3D champM, Vecteur3D champE, double courbure, Element* suivant) 
: Element(entree, sortie, rayon, champM, champE, suivant), e_courbure(courbure)
{}

ElementCourbe::ElementCourbe(ElementCourbe const& autre) : Element (autre), e_courbure(autre.e_courbure){}

bool ElementCourbe::heurte_bord(Particule const& part) const {
	
	if ((part.getPosition() - getCentre() - u(part)*(1/abs(e_courbure))).norme_carre() > e_rayon*e_rayon) return true;
	
	return false;
}

void ElementCourbe::dessine() const{}

void ElementCourbe::dessine (ostream& out) const {
	
	out << "Type : Element Courbe" << endl;
	
	Element::dessine(out);
	
	out << "Centre de courbure : " << getCentre() << endl <<
	
	"Courbure : " << e_courbure << endl;
	
}

Vecteur3D ElementCourbe::u(Particule const& part) const {
	
	return ~(part.getPosition() - getCentre() - e3*((part.getPosition()).getZ()));
	
	;}

Vecteur3D ElementCourbe::champMExerce (Particule const& part)const {return e_champM;}

Vecteur3D ElementCourbe::champEExerce (Particule const& part, double const& t)const {return e_champE;}

ElementCourbe* ElementCourbe::copie()const {
	
	return new ElementCourbe(*this);
	
}

string ElementCourbe::type()const {return "Courbe";}

ElementCourbe::~ElementCourbe(){}

void ElementCourbe::setSpecialChamp(double const& V, Particule const& typique) {}

double ElementCourbe::getAngle() const {
	
	return acos( ( (getCentre()-e_entree).prod_scal(getCentre()-e_sortie) )/(sqrt( (getCentre()-e_entree).norme_carre())*sqrt( (getCentre()-e_sortie).norme_carre() ) ) );
	
	}

//****************************ElementDroit****************************

ElementDroit::ElementDroit(Vecteur3D entree, Vecteur3D sortie, double rayon, Vecteur3D champM, Vecteur3D champE, Element* suivant) 
: Element (entree, sortie, rayon, champM, champE, suivant){}

ElementDroit::ElementDroit(ElementDroit const& autre) : Element(autre) {}

bool ElementDroit::heurte_bord(Particule const& part) const {
	
	if ((part.getPosition() - e_entree - (~(e_sortie - e_entree)) * 
		 (part.getPosition() -e_entree).prod_scal(~(e_sortie - e_entree))).norme_carre() > e_rayon*e_rayon) return true;
	
	return false;
	
}

double ElementDroit::s(Particule const& part) const{

	Vecteur3D v (part.getPosition()-(part.getElement())->getEntree());
	
	Vecteur3D a ((part.getElement())->getSortie() - (part.getElement())->getEntree());
	
	return sqrt((	a * (v.prod_scal(a) / a.norme_carre()) 	).norme_carre());

}

Vecteur3D ElementDroit::u(Particule const& part) const {
	
	return e3 ^ (~(e_sortie - e_entree));
	
	;}

void ElementDroit::dessine (ostream& out) const {
	
	out << "Type : Element droit " << endl;
	
	Element::dessine(out);
	
}


void ElementDroit::dessine()const{
	
	GLUquadric* quadrique=gluNewQuadric();
	glPushMatrix();
    // le repère d'origine subit une translation

    glTranslated(e_entree.getX(), e_entree.getY(), e_entree.getZ());
	glRotated(90,e_entree.getY()-e_sortie.getY(),e_sortie.getX()-e_entree.getX(),0);
    gluQuadricDrawStyle(quadrique, GLU_LINE);
    gluCylinder(quadrique, e_rayon, e_rayon,longueur(),10,10);
    gluQuadricDrawStyle(quadrique,GLU_LINE);
    gluDisk(quadrique,e_rayon,6*e_rayon/5,20,5);
    
    // retour au contexte précédent
    // donc au repère d'origine
    glPopMatrix();
	gluDeleteQuadric(quadrique);
	
}

Vecteur3D ElementDroit::unitaire() const {
	
	return ~(e_sortie-e_entree);
	
}

Vecteur3D ElementDroit::champMExerce (Particule const& part)const {return e_champM;}

Vecteur3D ElementDroit::champEExerce (Particule const& part, double const& t)const {return e_champE;}

ElementDroit* ElementDroit::copie()const {
	
	return new ElementDroit(*this);
	
}

string ElementDroit::type()const {return "Droit";} 

ElementDroit::~ElementDroit(){}

void ElementDroit::setSpecialChamp(double const& V, Particule const& typique) {}

//****************************SectionDroite****************************

SectionDroite::SectionDroite(Vecteur3D entree, Vecteur3D sortie, double rayon, Element* suivant) 
: ElementDroit (entree, sortie, rayon, Vecteur3D (0, 0, 0), Vecteur3D(0,0,0), suivant){}

SectionDroite::SectionDroite(SectionDroite const& autre) : ElementDroit(autre){}


void SectionDroite::dessine (ostream& out) const {
	
	out << "Spécialisation : Section droite" << endl;
	
	ElementDroit::dessine(out);
	
}
void SectionDroite::dessine() const{
	
	glColor4d(Couleur::Blanc.getRouge(),Couleur::Blanc.getVert(),Couleur::Blanc.getBleu(), 1.0); 
	ElementDroit::dessine();
	
	}


Vecteur3D SectionDroite::champMExerce (Particule const& part)const {return Vecteur3D();}

Vecteur3D SectionDroite::champEExerce (Particule const& part, double const& t)const {return Vecteur3D();}

SectionDroite* SectionDroite::copie()const {
	
	return new SectionDroite(*this);
	
}

string SectionDroite::type()const {return "Section droite";}

SectionDroite::~SectionDroite(){}

void SectionDroite::setSpecialChamp(double const& V, Particule const& typique) {}

//****************************Dipole****************************

Dipole::Dipole(Vecteur3D entree, Vecteur3D sortie, double rayon, double champV, double courbure, Element* suivant) 
: ElementCourbe(entree, sortie, rayon, Vecteur3D(0,0,champV), Vecteur3D(0,0,0), courbure, suivant)
{}

Dipole::Dipole (Dipole const& autre) : ElementCourbe(autre){}

double Dipole::getChampV() {return e_champM.getZ();} 


void Dipole::dessine (ostream& out) const {
	
	out << "Spécialisation : Dipole" << endl;
	
	ElementCourbe::dessine(out);
	
}

Vecteur3D Dipole::champMExerce (Particule const& part)const {return e_champM;}

Vecteur3D Dipole::champEExerce (Particule const& part, double const& t)const {return Vecteur3D();}

Dipole* Dipole::copie()const {
	
	return new Dipole(*this);
	
}

void Dipole::dessine() const
{
	
	GLUquadric* quadrique=gluNewQuadric();
	glPushMatrix(); //origine
	
	
	glTranslated(e_entree.getX(), e_entree.getY(), e_entree.getZ());
	
	
    glRotated(90,e_entree.getX()-getCentre().getX(),e_entree.getY()-getCentre().getY(),0);
    glColor4d(0.1, 0.6, 0.1, 1.0); //entree verte kaki
    
    gluQuadricDrawStyle(quadrique, GLU_LINE);
    gluDisk(quadrique,e_rayon,6*e_rayon/5,20,5);
    
    glPopMatrix();
    
    glPushMatrix();
    glTranslated(getCentre().getX(),getCentre().getY(),getCentre().getZ());
    
    for (int i=0;i<18;++i)
    {
	glPushMatrix();
	glTranslated(-getCentre().getX(),-getCentre().getY(),-getCentre().getZ());
    glTranslated(e_entree.getX(), e_entree.getY(), e_entree.getZ());
    //dessin
	glPushMatrix();
	glRotated(90,e_entree.getX()-getCentre().getX(),e_entree.getY()-getCentre().getY(),0);
    glColor4d(Couleur::Vert.getRouge(), Couleur::Vert.getVert(), Couleur::Vert.getBleu(), 1.0);
    gluQuadricDrawStyle(quadrique, GLU_LINE);
    gluCylinder(quadrique, e_rayon, e_rayon,e_rayon,10,2);
	
	glPopMatrix();
	
	glPopMatrix();
    glRotated(getAngle()*180/(M_PI*18),0,0,-1);

	}
        
    glPopMatrix();
    
	gluDeleteQuadric(quadrique);
	
}



string Dipole::type()const {return "Dipole";}

Dipole::~Dipole(){}

void Dipole::setSpecialChamp(double const& V, Particule const& typique) {
	
	// La vitesse des particules étant essentiellement longitudinale, on ne considèrera pour le calcul de gamma que la vitesse Vs

	e_champM = Vecteur3D (0, 0 , typique.gamma() * typique.getMasse() * 1e9 * Particule::e * e_courbure * V / (Particule::c * Particule::c * typique.getCharge()));

}

//****************************Quadrupole****************************

Quadrupole::Quadrupole(Vecteur3D entree, Vecteur3D sortie, double rayon, double constchamp, Element* suivant) 
: ElementDroit(entree, sortie, rayon, Vecteur3D(0,0,0),Vecteur3D(0,0,0), suivant), e_constchamp(constchamp) {}

Quadrupole::Quadrupole(Quadrupole const& autre) : ElementDroit(autre), e_constchamp(autre.e_constchamp) {}


Vecteur3D Quadrupole::champMExerce (Particule const& part) const{ 
	// calcule le champ exercé sur une particule en fonction de sa position
	
	Vecteur3D d(~(e_sortie - e_entree));
	
	Vecteur3D u(Element::e3^d);
	
	Vecteur3D x = part.getPosition() - e_entree;
	
	return (Element::e3 * u.prod_scal(x - (d*(x.prod_scal(d)) )) + u*(part.getPosition()).getZ()) * e_constchamp;
	
}

Vecteur3D Quadrupole::champEExerce (Particule const& part, double const& t)const {return Vecteur3D();}

void Quadrupole::dessine(ostream& out) const {
	
	out << "Spécialisation : Quadrupole" << endl;
	
	ElementDroit::dessine(out);
	
	out << "Intensité magnétique : " << e_constchamp << endl;
}

Quadrupole* Quadrupole::copie()const {
	
	return new Quadrupole(*this);
	
}
void Quadrupole::dessine() const{
	
	
	glColor4d(Couleur::Cyan.getRouge(),Couleur::Cyan.getVert(),Couleur::Cyan.getBleu(), 1.0); //Cyan
	ElementDroit::dessine();
	
}

string Quadrupole::type()const{return "Quadrupole";}

Quadrupole::~Quadrupole(){}

void Quadrupole::setSpecialChamp(double const& V, Particule const& typique) {}

//****************************Maille FODO****************************

//#constructeur de folie#

MailleFODO::MailleFODO (Vecteur3D entree,Vecteur3D sortie,double rayon,double constchamp,double longueur,Element* suivant)
: 
ElementDroit(entree,sortie,rayon,Vecteur3D(0,0,0), Vecteur3D(0,0,0), suivant) 

,QF (Quadrupole(entree, 
				entree+MailleFODO::unitaire()*((MailleFODO::longueur()/2)-longueur),
				rayon,
				constchamp,
				&section1
				)
	 )

,section1  (SectionDroite(entree+MailleFODO::unitaire()*((MailleFODO::longueur()/2)-longueur),
						  entree+MailleFODO::unitaire()*(MailleFODO::longueur()/2),
						  rayon,
						  &QD)
			)

,QD (Quadrupole(entree+MailleFODO::unitaire()*(MailleFODO::longueur()/2),
				entree+MailleFODO::unitaire()*(MailleFODO::longueur()-longueur),
				rayon,
				-constchamp,
				&section2)
	 )

,section2  (SectionDroite(entree+MailleFODO::unitaire()*(MailleFODO::longueur()-longueur),
						  sortie,
						  rayon,
						  suivant)
			)
{}
//#/constructeur de folie#


MailleFODO::MailleFODO(MailleFODO const& autre) //copie
:ElementDroit(autre), QF(autre.QF),section1(autre.section1),QD(autre.QD),section2(autre.section2) {}

MailleFODO* MailleFODO::copie()const {
	
	return new MailleFODO(*this);
	
}
void MailleFODO::dessine() const{
		
	glColor4d(Couleur::Magenta.getRouge(),Couleur::Magenta.getVert(),Couleur::Magenta.getBleu(), 1.0); 
	ElementDroit::dessine();
	
}

void MailleFODO::dessine(ostream& out) const {
	
	out << "Spécialisation : Maille FODO" << endl;
	
	out << "Position d'entrée : " << e_entree << endl <<
	"Position de sortie : " << e_sortie << endl;
	
	out << "La Maille FODO contient ces éléments : " << endl;
	
	out << "1) "; QF.dessine(out);
	
	out << "2) "; section1.dessine(out);
	
	out << "3) "; QD.dessine(out);
	
	out << "4) "; section2.dessine(out);
	
}


string MailleFODO::type()const {return "MailleFODO";}

MailleFODO::~MailleFODO(){}

Vecteur3D MailleFODO::champMExerce (Particule const& part) const{ 
	// calcule le champ exercé sur une particule en fonction de sa position
	
	if (QF.passe_au_suivant(part) == false) {
		return QF.champMExerce(part);
	}
	
	else if (section1.passe_au_suivant(part) == false) {
		return section1.champMExerce(part);
	}
	else if (QD.passe_au_suivant(part) == false) {
		return QD.champMExerce(part);
	}
	else 
		return section2.champMExerce(part);
	
	
}

Vecteur3D MailleFODO::champEExerce (Particule const& part, double const& t)const {return Vecteur3D();}

void MailleFODO::setSpecialChamp(double const& V, Particule const& typique) {}

//****************************Sextupole****************************

Sextupole::Sextupole(Vecteur3D entree, Vecteur3D sortie, double rayon, double constchamp, Element* suivant) 
: Quadrupole(entree, sortie, rayon, constchamp, suivant) {}

Sextupole::Sextupole(Sextupole const& autre) : Quadrupole(autre) {}


Vecteur3D Sextupole::champMExerce (Particule const& part) const{ 
	// calcule le champ exercé sur une particule en fonction de sa position
	
	double R; // distance r selon le système de coordonnées du Complément
	
	Vecteur2D p (part.getPosition()); // particule sans la composante z
	
	Vecteur2D l (~(e_sortie - e_entree)); // Direction de l'élément sans la composante z
	
	Vecteur2D v (part.getPosition() - e_entree); // Position de la particule selon le point e_entree
	
	R = sqrt(v.norme_carre() - (l*(v.prod_scal(l))).norme_carre() ); // Par Pythagore, où le deuxième terme est 
																	//la norme au carre de la projection orthogonale de v sur l
	
	if ((e_entree + l*(v.prod_scal(l))).norme_carre() > (part.getPosition()).norme_carre()) {
	
		R = - R; // La particule a un R négatif si et seulement si la norme de la projection est plus grande que la norme de sa position
	
	}
	
	
	double Z; // distance z selon e3
	
	Z = (part.getPosition()).getZ() - e_entree.getZ();
	
	double Br; // représente la composante r du champ magnétique en coordonnées cylindriques
	
	Br = e_constchamp * R * Z;
	
	double Bz; // représente la composante z du champ magnétique en coordonnées cylindriques
	
	Bz = e_constchamp * (R*R - Z*Z)/2; 
	
	Vecteur3D r(~(part.getPosition() - (e_entree + l*(v.prod_scal(l))))); // représente la direction de la composante r de la 
																			//position de la particule en coordonnées cartésiennes
	
	Vecteur3D B; // représente le champ exercé sur la particule
	
	B = r*Br + e3* Bz; 
	
	return B;
	
}

Vecteur3D Sextupole::champEExerce (Particule const& part, double const& t)const {return Vecteur3D();}

void Sextupole::dessine(ostream& out) const {
	
	out << "Spécialisation : Sextupole" << endl;
	
	ElementDroit::dessine(out);
	
	out << "Intensité magnétique : " << e_constchamp << endl;
}

void Sextupole::dessine() const{
	
	glColor4d(Couleur::Zinzolin.getRouge(),Couleur::Zinzolin.getVert(),Couleur::Zinzolin.getBleu(), 1.0); 
	ElementDroit::dessine();
	
}

Sextupole* Sextupole::copie()const {
	
	return new Sextupole(*this);
	
}

string Sextupole::type()const{return "Sextupole";}

Sextupole::~Sextupole(){}

void Sextupole::setSpecialChamp(double const& V, Particule const& typique) {}

//****************************CaviteRadio****************************

CaviteRadio* CaviteRadio::copie()const {
	
	return new CaviteRadio(*this);
	
}

string CaviteRadio::type()const {return "CaviteRadio";} 

void CaviteRadio::dessine (ostream& out) const {
	
	out << "Spécialisation : Cavité Radiofréquence" << endl;
	
	ElementDroit::dessine(out);
	
}

CaviteRadio::CaviteRadio(double zero, double V, double lambda, double psi, Vecteur3D entree, Vecteur3D sortie, double rayon, Element* suivant) 
: ElementDroit (entree, sortie, rayon, Vecteur3D(), Vecteur3D(), suivant), e_zero(zero), e_V(V), e_lambda(lambda), e_psi(psi){}

CaviteRadio::~CaviteRadio() {}

Vecteur3D CaviteRadio::champMExerce (Particule const& part) const{return Vecteur3D();}

Vecteur3D CaviteRadio::champEExerce (Particule const& part, double const& t)const {

	return unitaire() * (e_zero * sin(e_V * 2 * M_PI/e_lambda * t + s(part) * 2 * M_PI/e_lambda + e_psi));

}

void CaviteRadio::setSpecialChamp(double const& V, Particule const& typique) {

	e_V = V;

}

void CaviteRadio::dessine() const{
	glColor4d(Couleur::Rouge.getRouge(),Couleur::Rouge.getVert(),Couleur::Rouge.getBleu(), 1.0); 
	ElementDroit::dessine();
	
}


