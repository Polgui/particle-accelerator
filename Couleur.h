#ifndef PRJ_COULEUR_H
#define PRJ_COULEUR_H


#include <iostream>


class Couleur
{
	protected:
	double c_rouge;
	double c_vert;
	double c_bleu;
	
	
	public:
	Couleur(double,double,double);//blanc par defaut
	Couleur();
	void setCouleur(double,double,double);
	double getRouge() const ;
	double getVert() const ;
	double getBleu() const;

    static const Couleur Noir; 
    static const Couleur Blanc;
    static const Couleur Rouge;
    static const Couleur Vert; 
    static const Couleur Bleu; 
    static const Couleur Jaune; 
    static const Couleur Magenta;
    static const Couleur Cyan; 
    static const Couleur Zinzolin; 
};



#endif
