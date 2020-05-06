
#ifndef PRJ_PARTICULE_H
#define PRJ_PARTICULE_H

#include "Vecteur3D.h"
#include "Particule.h"
#include "Element.h"
#include "Dessinable.h"

#include <iostream>
#include <vector>

class Element;

class Case;

class Particule;

class Particule : public Dessinable {
	
public:

	void dessine() const;	
	
	// Attributs static, utilisable dans tout les programmes incluant "Particule.h"
	
	static double c ; // [m/s], vitesse de la lumière
	static double e ; // [C], charge d'un proton
	
	//Méthodes
	
	virtual void dessine(std::ostream& out)const;

		// Constructeurs
	
	Particule (double x=0.0, double y=0.0, double z=0.0, double dx=0.0, double dy= 0.0, double dz=0.0,
			   double masse=0.938272, double charge= e, 
				double forcex=0.0, double forcey=0.0, double forcez=0.0); // Si rien de spécifié, crée un proton au repos
	
	Particule (Vecteur3D position, Vecteur3D qdm, double masse =0.938272, double charge = e, Vecteur3D force = Vecteur3D()); // pour la vitesse : Vecteur qdm
	
	Particule (Vecteur3D position, double eng, Vecteur3D direction, double masse=0.938272,
			   double charge = e, Vecteur3D force = Vecteur3D()); // pour la vitesse : Vecteur direction + eng
	
		//
	
	double gamma()const; // facteur relativiste, 1/(1- v^2/c^2)^1/2
	
	double eng()const; // énergie de la particule en GeV

	Vecteur3D vitesse()const;
	
	void ajouteForceMagnetique (Vecteur3D const&, double const&dt); // ajoute une force de Lorentz + rotation 
	
	void ajouteForceElectrique (Vecteur3D const&); // ajoute la force électrique
	
	void ajouteForceInter (Particule const& part); // ajoute une force inter-particule avec part
	
	friend std::ostream& operator<< (std::ostream&, Particule const&);
	
	void bouger (double const& temps); // temps sera donné en secondes
	
	Vecteur3D getPosition()const;
	
	void setPosition(Vecteur3D const&);
	
	void setQDM (Vecteur3D const&);
	
	void setMasse (double const&);
	
	void setCharge (double const&);
	
	double getMasse() const;
	
	double getCharge() const;
	
	void setElement (Element* element);
	
	Element* getElement() const;
	
	void setCase (Case* cas);
	
	Case* getCase() const;
	
	virtual ~Particule();
	
	Particule operator*(double const& scal) const;
	
private:
	
	//Attributs
	
	Vecteur3D m_position; // [m]
	Vecteur3D m_qdm; // vecteur quantité de mouvement en [GeV/c]
	double m_masse; // [GeV/c^2]
	double m_charge; // [C] coulomb
	Vecteur3D m_force; // Force agissant sur la particule
	
	Element* m_element; // Pas de constructeur définissant un élément de départ : nous considérons cet attribut comme "à part" et implémentons des getters/setters 
	// C'est un pointeur sur un élément, pratique pour l'inclusion circulaire avec Element
	Case* m_case; // Tout comme pour Element, Particule a un pointeur sur la case qu'elle occupe, afin de toujours connaître cette case.
	
	
};


#endif
