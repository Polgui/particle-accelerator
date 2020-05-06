
#include "Couleur.h"
#include <iostream>

Couleur::Couleur(double rouge,double vert,double bleu)
:c_rouge(rouge),c_vert(vert),c_bleu(bleu){}

Couleur::Couleur()
:c_rouge(0),c_vert(0),c_bleu(0)
{}

void Couleur::setCouleur(double rouge,double vert,double bleu) {
	c_rouge=rouge;
	c_vert=vert;
	c_bleu=bleu;
	
}

double Couleur::getRouge()const{return c_rouge;}
double Couleur::getVert()const{return c_vert;}
double Couleur::getBleu()const{return c_bleu;}

const Couleur Couleur::Noir(0, 0, 0);
const Couleur Couleur::Blanc(1, 1, 1);
const Couleur Couleur::Rouge(1, 0, 0);
const Couleur Couleur::Vert(0.1, 0.6, 0.1);
const Couleur Couleur::Bleu(0, 0, 1);
const Couleur Couleur::Jaune(1, 1, 0);
const Couleur Couleur::Magenta(1, 0, 1);
const Couleur Couleur::Cyan(0, 1, 1);
const Couleur Couleur::Zinzolin(0.3, 0, 0.29);
