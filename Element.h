
#ifndef PRJ_ELEMENT_H
#define PRJ_ELEMENT_H


#include "Particule.h"
#include "Dessinable.h"

#include <string>

#include "wxIncludes"
#include "Couleur.h"

class Particule;

class Element : public Dessinable { // un élément contient une entree, sortie, rayon de chambre, champ et un éléement suivant
	
	// Tous les éléments sont dessinables, et contiennent chacun leur méthode de dessin
	
protected:
	
	Vecteur3D e_entree;
	
	Vecteur3D e_sortie;
	
	double e_rayon; //rayon de la chambre à vide;
	
	Vecteur3D e_champM; // Cet attribut représente, pour tous les éléments, le champ magnétique GLOBAL s'il y en a un 
						//(c-à-d si le champ magnétique que subit une particule ne dépend pas de sa position), 
						//et (0,0,0) si l'élément n'a pas de champ magnétique OU si le champ magnétique dépend la position de la particule
	
	Vecteur3D e_champE; // Représente le champ électrique global
	
	Element* e_suivant; // Représente l'élément suivant dans la chaîne d'éléments de l'accélérateur


	GLUquadric* quadrique; //Widget
	
	Couleur e_couleur;

	
public:
	
	static Vecteur3D e3;
	
	double longueur() const;
	
	Element(Vecteur3D entree=Vecteur3D(), Vecteur3D sortie=Vecteur3D(), double rayon =0.0, 
			Vecteur3D champM=Vecteur3D(), Vecteur3D champE=Vecteur3D(), Element* suivant = NULL);
	
	Element (Element const& autre);
	
	virtual Vecteur3D u(Particule const& part)const =0; // Renvoie le vecteur u, qui diffère si l'élément est courbe ou droit
	
	void setSuivant(Element* suivant);
	
	Element* getSuivant()const;
	
	Vecteur3D getEntree() const;

	Vecteur3D getSortie() const;
	
	double getRayon() const;
	
	virtual void dessine (std::ostream& out) const;
	
	bool passe_au_suivant(Particule const&)const; // true si la particule est dans le suivant
	
	virtual Vecteur3D champMExerce (Particule const&)const =0; // Nous renvoie le champ magnétique que subit la particule
	
	virtual Vecteur3D champEExerce (Particule const&, double const& t)const =0; // Nous renvoie le champ électrique que subit la particule
	
	virtual bool heurte_bord (Particule const&)const =0; // true si la particule a heurté le bord
	
	virtual std::string type ()const =0;
	
	virtual ~Element();
	
	virtual Element* copie() const =0;
	
	virtual void setSpecialChamp (double const&, Particule const&) =0; // Pour certains éléments, on doit regler le champ électrique ou magnétique, 
														//ou d'autres réglages, en fonction de la vitesse moyenne longitudinale des particules
	
	virtual void dessine() const;

	};


//-------------------------------------------------------------------------


class ElementCourbe : public Element { // a une courbure
	
	protected :
	
	double e_courbure; // 1/rayon de courbure
	
public:
	
	virtual Vecteur3D u(Particule const& part) const;
	
	Vecteur3D getCentre()const; // Pour avoir le centre de courbure
	
	ElementCourbe(Vecteur3D entree=Vecteur3D(), Vecteur3D sortie=Vecteur3D(),double rayon =0.0, 
				  Vecteur3D champM=Vecteur3D(), Vecteur3D champE=Vecteur3D(),double courbure =0.0, Element* suivant = NULL);
	
	ElementCourbe(ElementCourbe const& autre);

	double getAngle() const; //retourne l'angle entre entree et sortie autour du centre

	virtual void dessine (std::ostream& out) const;
	
	virtual bool heurte_bord (Particule const&)const; // si la particule a heurté le bord
	
	virtual ~ElementCourbe();
	
	virtual Vecteur3D champMExerce (Particule const&)const;
	
	virtual Vecteur3D champEExerce (Particule const&, double const& t)const;
	
	virtual ElementCourbe* copie() const;
	
	virtual std::string type()const;

	virtual void dessine() const;

	virtual void setSpecialChamp(double const&, Particule const&);
	

};


//-------------------------------------------------------------------------


class ElementDroit : public Element { // ElementDroit est un élément droit ..., avec une longueur défnit par entrée et sortie.
	
	
	
public:
	
	ElementDroit(Vecteur3D entree=Vecteur3D(), Vecteur3D sortie=Vecteur3D(),double rayon =0.0, 
				 Vecteur3D champM=Vecteur3D(), Vecteur3D champE=Vecteur3D(),Element* suivant = NULL);
	
	ElementDroit(ElementDroit const& autre);
	
	double s(Particule const& part)const;
	
	virtual Vecteur3D u(Particule const& part) const;
	
	virtual void dessine (std::ostream& out) const;

	virtual void dessine() const;
	
	virtual bool heurte_bord (Particule const&)const; // si la particule a heurté le bord

	virtual Vecteur3D unitaire() const; //vecteur unitaire, entrée--->sortie
	
	virtual ~ElementDroit();
	
	virtual Vecteur3D champMExerce (Particule const&)const;
	
	virtual Vecteur3D champEExerce (Particule const&, double const& t)const;
	
	virtual ElementDroit* copie()const;
	
	virtual std::string type()const;
	
	virtual void setSpecialChamp(double const&, Particule const&);
};


//-------------------------------------------------------------------------

class SectionDroite : public ElementDroit { // section droite n'a pas de champ 
	
	public :
	
	virtual void dessine(std::ostream& out)const;
	
	SectionDroite(Vecteur3D entree=Vecteur3D(), Vecteur3D sortie=Vecteur3D(), double rayon =0.0, Element* suivant = NULL);
	
	SectionDroite(SectionDroite const& autre);
	
	virtual ~SectionDroite();

	virtual void dessine() const;
	
	virtual Vecteur3D champMExerce (Particule const&)const;
	
	virtual Vecteur3D champEExerce (Particule const&, double const& t)const;
	
	virtual SectionDroite* copie()const;
	
	virtual std::string type()const;
	
	virtual void setSpecialChamp(double const&, Particule const&);
};

//-------------------------------------------------------------------------


class Dipole : public ElementCourbe { // a un champ uniquement vertical
	
public:
	
	virtual void dessine(std::ostream& out)const;
	
	Dipole(Vecteur3D entree=Vecteur3D(), Vecteur3D sortie=Vecteur3D(),double rayon =0.0, double champV = 0, double courbure =0.0, Element* suivant = NULL);
	
	Dipole(Dipole const& autre);
	
	double getChampV(); // Pour avoir le champ vertical
	
	virtual ~Dipole();

	virtual void dessine() const;
	
	virtual Vecteur3D champMExerce (Particule const&)const;
	
	virtual Vecteur3D champEExerce (Particule const&, double const& t)const;
	
	virtual Dipole* copie()const;
	
	virtual std::string type()const;
	
	virtual void setSpecialChamp(double const&, Particule const&);
};

//-------------------------------------------------------------------------

class Quadrupole : public ElementDroit {
	
protected:
	
	double e_constchamp;
	
public:
	
	virtual void dessine(std::ostream& out)const;
	
	Quadrupole(Vecteur3D entree=Vecteur3D(), Vecteur3D sortie=Vecteur3D(),double rayon =0.0, double constchamp =0, Element* suivant = NULL);
	
	Quadrupole(Quadrupole const& autre);
	
	virtual ~Quadrupole();

	virtual void dessine() const;
	
	virtual Vecteur3D champMExerce (Particule const&)const;
	
	virtual Vecteur3D champEExerce (Particule const&, double const& t)const;
	
	virtual Quadrupole* copie()const;
	
	virtual std::string type()const;
	
	virtual void setSpecialChamp(double const&, Particule const&);
};

//--------------------------------------------------------------------------
class MailleFODO : public ElementDroit {
	
	protected :
	
	Quadrupole QF; //focalisant
	
	SectionDroite section1; //premiere section
	
	Quadrupole QD; //défocalisant
	
	SectionDroite section2;	//seconde section
	
	public :
	//CONSTRUCTEUR DE FOLIE
	MailleFODO (Vecteur3D entree=Vecteur3D(),Vecteur3D sortie=Vecteur3D(),double rayon =0.0,double constchamp =0.0,double longueur=0.0,Element* suivant = NULL);
	
	MailleFODO(MailleFODO const& autre);
	
	virtual ~MailleFODO();

	virtual void dessine() const;
	
	virtual MailleFODO* copie()const;
	
	virtual void dessine(std::ostream& out)const;
	
	virtual std::string type()const;
	
	virtual Vecteur3D champMExerce (Particule const&)const;
	
	virtual Vecteur3D champEExerce (Particule const&, double const& t)const;
	
	virtual void setSpecialChamp(double const&, Particule const&);
};

//--------------------------------------------------------------------------

class Sextupole : public Quadrupole {
	
public:
	
	virtual void dessine(std::ostream& out)const;
	
	Sextupole(Vecteur3D entree=Vecteur3D(), Vecteur3D sortie=Vecteur3D(),double rayon =0.0, double constchamp =0, Element* suivant = NULL);
	
	Sextupole(Sextupole const& autre);
	
	virtual ~Sextupole();

	virtual void dessine() const;

	virtual Vecteur3D champMExerce (Particule const&)const;
	
	virtual Vecteur3D champEExerce (Particule const&, double const& t)const;
	
	virtual Sextupole* copie()const;
	
	virtual std::string type()const;
	
	virtual void setSpecialChamp(double const&, Particule const&);
	
};

//--------------------------------------------------------------------------

class CaviteRadio : public ElementDroit	{
	
private:
	
	double e_zero; // E0 du champ électrique
	
	double e_V; // Vitesse de l'onde, que l'on souhaite égale à la vitesse longitudinale moyenne des bunchs
	
	double e_lambda; // longueur d'onde du champ 
	
	double e_psi; // constante psi dans la formule du champ électrique
	
public:
	
	CaviteRadio (double zero, double V, double lambda, double psi, Vecteur3D entree=Vecteur3D(), 
				 Vecteur3D sortie=Vecteur3D(),double rayon =0.0,Element* suivant = NULL);
	
	virtual ~CaviteRadio();

	virtual void dessine() const;
	
	virtual void dessine (std::ostream& out) const;
	
	virtual std::string type()const;
	
	virtual CaviteRadio* copie()const;
	
	virtual Vecteur3D champMExerce (Particule const&)const;
	
	virtual Vecteur3D champEExerce (Particule const&, double const& t)const;
	
	virtual void setSpecialChamp(double const&, Particule const&);
};


#endif
