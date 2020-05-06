#ifndef PRJ_ACCELERATEUR_H
#define PRJ_ACCELERATEUR_H


#include "Element.h"
#include "Faisceau.h"
#include "Dessinable.h"
#include "Particule.h"
#include "Case.h"

#include "Application.h"

#include <map>
#include <iostream>
#include <string>
#include <vector>


class Accelerateur : public Dessinable { // l'accélérateur est dessinable

public :
	
	Accelerateur(); //constructeur défaut défaut
	
	void setTypique(Particule const&);
	
	void setDT (double const&);
	
	void setEPS (double const&);

	void add_fais (Faisceau const& f); //ajout d'un faisceau

	void add_elem (Element const& e); //ajout d'un élément
	void clear_elem(); //vide la collection éléments

	void evolue(); // fais évoluer les particules sur un pas de temps dt
	
	void ajouteForcesChamps(); // ajoute les forces magnétiques pour toutes les particules
	
	void ajouteForcesInter();
	
	void progression(unsigned int const& fois, std::ostream& out);
	
	void progression(unsigned int const& fois, std::string const& nom);
	
	virtual void dessine(std::ostream& out)const; // dessine les faisceaux et les éléments

	void dessine()const;
	
	void dessine_fais(std::ostream& out)const; // dessine les faisceaux
	
	void dessine_elem(std::ostream& out) const; // dessine les éléments
	
	virtual ~Accelerateur();
	
	void lie_elements(); //chaque elements[i] a un pointeur sur elements[i+1]
	
	void lie_part_elem(Particule& part, double const& numero_elem); // la particule part a un pointeur
	// sur l'élément n°numero_elem
	
	void add_part_fais(Particule const& part, double const& num); // ajoute la particule part au faisceau n°num de l'accélérateur
	
	double longueur()const;
	
	void lie_parts_cases();
	
	double Vs() const; // retourne la vitesse longitudinale moyenne des particules étant dans un élément droit

	void ajouteTemps();
	
	Vecteur3D coord_part(); //retourne les coord de la 1ere particule du 1er faisceau
	
protected:

	//Widget

	GLUquadric* quadrique;

	// Attributs
	
	std::vector <Faisceau> faisceaux; //collection de Faisceaux

	std::vector <Element*> elements; //collection d'Eléments
	
	std::map< int, Case > decoupe; // L'Accelerateur contient une liste de Cases, qui représente un découpage perpendiculaire à l'abscisse curviligne
	
	double EPS; // EPSILON, le pas d'espace pour le découpage des éléments en cases
	
	double temps;
	
	double dt;
	
	
	Particule typique; // particule type que l'accélérateur contient (on considère qu'il ne contient qu'un type de particule [masse et charge])
	
	// méthodes privés
	
	Accelerateur& operator=(Accelerateur const&  autre); //operateur = qui fait rien

	Accelerateur (const Accelerateur&); //copie qui fait rien


	

};

#endif
