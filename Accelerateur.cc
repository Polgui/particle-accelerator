#include <iostream>
#include <string>
#include <cmath>
#include <fstream>
#include <iterator>

#include "Element.h"
#include "Accelerateur.h"
#include "wxIncludes"

using namespace std;

Accelerateur::Accelerateur() : temps(0)
{quadrique=gluNewQuadric();};	


void Accelerateur::dessine(ostream& out)const //Affiche globalement l'accélérateur
{
	  
	out << "============================================================" << endl <<
		"|Après " << int(temps/dt) -1 << " pas| (1 pas = " << dt << " secondes)" << endl <<
		endl;
		
		dessine_fais(out);	
}

void Accelerateur::dessine_fais(ostream& out)const // n'affiche que les particules
{
	out <<endl<<endl
	<<"L'accelerateur contient:  " << faisceaux.size() << " faisceau";
	
	if (faisceaux.size() > 1) {out << "x";}
	
	out << "." <<endl<<
	"-------------------------------------------------------" << endl << endl;
	
	for (unsigned int i(0);i<faisceaux.size();++i)
	{	
		out << "FAISCEAU " << i + 1 << " : " << endl << endl;
		
		faisceaux[i].dessine(out);
		
		out << "-------------------------------------------------------" << endl << endl;
	}
	out <<"øøøøøøøøøøøøøøøøøøøøøøøøøøøøøøøøøøøøøøøøøøøøøøøøøøøøøøøøøøøøø"<<endl;
}

void Accelerateur::dessine()const //Dessine l'accélérateur
{
	for (unsigned int i=0; i<elements.size();++i)
	{
		elements[i]->dessine();
	}

	for (unsigned int i(0);i<faisceaux.size();++i)
	{	
		faisceaux[i].dessine();
	}

}

void Accelerateur::dessine_elem(ostream& out)const  // n'affiche que les éléments
{
	
	out <<"øøøøøøøøøøøøøøøøøøøøøøøøøøøøøøøøøøøøøøøøøøøøøøøøøøøøøøøøøøøøø"<<endl;
	
	out <<"L'accelerateur contient: "<<elements.size()<<" élément";
	
	if(elements.size() > 1) {out << "s";}
	
	out <<"."<<endl << endl;
	
	for (unsigned int i=0;i<elements.size();++i)
	{
		(*(elements[i])).dessine(out);
		
		out << endl;
	}
	out << endl;
	
}

Vecteur3D Accelerateur::coord_part(){

if (faisceaux.size()==0) Vecteur3D(0,0,0);

else if (faisceaux[0].size()== 0) return Vecteur3D(0,0,0);
		
return	faisceaux[0][0].getPosition();		
	
}

void Accelerateur::add_fais (Faisceau const& f) //ajoute un faisceau f
	{
	 faisceaux.push_back(f);
	}


void Accelerateur::add_elem (Element const& e) //ajoute un élément e
	{	
	elements.push_back(e.copie());											
	}

void Accelerateur::evolue(){ 
	
	for(unsigned int i(0); i < faisceaux.size(); ++i) {
		
		faisceaux[i].creation(dt);
		
		for (unsigned int j(0); j < faisceaux[i].size(); ++j) {
			
			faisceaux[i][j].bouger(dt);
			
			if (	( faisceaux[i][j].getElement() )->passe_au_suivant(faisceaux[i][j])		) { 
				// Si la particule est passée à l'élément suivant, 
				//le pointeur doit pointer sur ce dernier
				
				faisceaux[i][j].setElement(	(faisceaux[i][j].getElement())->getSuivant()	);
				
			}
			
			if (( faisceaux[i][j].getElement() )->heurte_bord(faisceaux[i][j]) ) { 
				
				// si la particule a heurté le bord, on la supprime
				
				(faisceaux[i][j].getCase())->pop(i, j);
				
				if (faisceaux[i][faisceaux[i].size()-1].getCase() != NULL) {
					
					(faisceaux[i][faisceaux[i].size()-1].getCase())->pop(i, faisceaux[i].size()-1);
				
					(faisceaux[i][faisceaux[i].size()-1].getCase())->push_back(pair<unsigned int, unsigned int> (i, j)); // La "signature" de la dernière particule devient (i, j)
						
				}
				
				faisceaux[i][j] = faisceaux[i][faisceaux[i].size()-1];
				
				//on supprime la particule à supprimer, et on place la dernière à sa place
				
				faisceaux[i].pop_back();
				
			}
			
		}
	}
}

Accelerateur& Accelerateur::operator=(Accelerateur const& autre) {return (*this);} //operateur =fait rien
	
Accelerateur::Accelerateur (const Accelerateur&) {} //copie fait rien

void Accelerateur::lie_elements () // lie chaque élément avec son suivant et découpe l'accélérateur en cases, puis lie chaque case avec sa précédente et sa suivante
{

	for (unsigned int i(0); i < elements.size() -1; ++i) {
		
		elements[i]->setSuivant(elements[i+1]); //chaque elements[i] a un pointeur sur elements[i+1]
		
	}

	elements[elements.size()-1]->setSuivant(elements[0]);
	
	//++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	
	for (int i(1); i <= int(longueur() / EPS); ++i) {
		
		decoupe[i] = Case(); // on ajoute le nombre de cases voulu
		
	}
	
	//++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	
	for (map<int, Case>::iterator i (decoupe.begin()); i != decoupe.end(); ++i) {
		
		if (i->first != int(decoupe.size())) {
		
		(i->second).setSuivant(&decoupe[i->first +1]); //chaque decoupe[i] a un pointeur sur decoupe[i+1]
		
		}
	}
	
	decoupe[decoupe.size()].setSuivant(&decoupe[1]);
	
	//++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	
	for (map<int, Case>::iterator i (decoupe.begin()); i != decoupe.end(); ++i) {
		
		if (i->first != 1) {
		
		i->second.setPrecedent(&decoupe[i->first -1]); //chaque decoupe[i] a un pointeur sur decoupe[i+1]
		
		}
	}
	
	decoupe[1].setPrecedent(&decoupe[decoupe.size()]);
	
}

void Accelerateur::lie_part_elem(Particule& part, double const& numero_elem) { // la particule part a 
//un pointeur sur l'élément n°numero_elem

	part.setElement(elements[numero_elem-1]);
	
}

void Accelerateur::ajouteForcesChamps () {

//ajoute les forces magnétiques et électriques respectives de toutes les particules de chaque faisceau
	
	for(unsigned int i(0); i < faisceaux.size(); ++i) {
		
		for(unsigned int j(0); j < faisceaux[i].size(); ++j) {
			
			faisceaux[i][j].ajouteForceMagnetique((faisceaux[i][j].getElement())->champMExerce(faisceaux[i][j]), dt);
			
			faisceaux[i][j].ajouteForceElectrique((faisceaux[i][j].getElement())->champEExerce(faisceaux[i][j], temps));
			
		}
	}
}

void Accelerateur::lie_parts_cases (){

	for (unsigned int i(0); i < faisceaux.size(); ++i) {
		
		for (unsigned int j(0); j < (faisceaux[i]).size(); ++j) {
						
			// on supprime la particule de sa case
			
			if (faisceaux[i][j].getCase() != NULL) { // seulement si la particule est déjà dans une case
				
				faisceaux[i][j].getCase() -> clear(); // on supprime toutes les particules de toutes les cases
				
							
			}
			// on détermine la longueur de l'abscisse curviligne de la particule
			
			
			double l (0);
			
			int k(0);
			
			while (elements[k] != faisceaux[i][j].getElement()) {
				
				l += elements[k]->longueur();
				
				++k;
				
			}
			
			// Un peut de géométrie qu'on espère correcte
			
			Vecteur3D v (faisceaux[i][j].getPosition()-(faisceaux[i][j].getElement())->getEntree());
			
			Vecteur3D a ((faisceaux[i][j].getElement())->getSortie() - (faisceaux[i][j].getElement())->getEntree());
			
			l += sqrt((	a * (v.prod_scal(a) / a.norme_carre()) 	).norme_carre());
			
			// on lie la particule à la case correspondante
			
			faisceaux[i][j].setCase (&decoupe[ (int(l/EPS))%(int(longueur()/EPS)) + 1]); /* l/EPS est la case normale, mais lors des calculs, 			
 il se peut, si la particule est à la fin du dernier élément, que la position de la particule soit projetée légèrement devant le dernier élément, nous donnant une longeur
plus grande que l'accélérateur. Nous prendrons donc le reste de la division avec longueur()/EPS. Mais ce calcul pouvant nous donner 0 si l vaut 0, nous ajoutons 1 (ainsi la première case est la case 1 et non la case 0) */
			
			// on l'ajoute à sa case
			
			(faisceaux[i][j].getCase())->push_back(pair<unsigned int, unsigned int> (i, j));
			
		}
	}
		
	}

void Accelerateur::ajouteForcesInter() {

// ajoute les forces inter-particules respectives de chaque couple de chaque particule dans chaque faisceau
	
	for(unsigned int i(0); i < faisceaux.size(); ++i) {
		
		for (unsigned int j(0); j < faisceaux[i].size(); ++j) {
			
			for (unsigned int l(0); l < (faisceaux[i][j].getCase())->size(); ++l) { // ajoute la force pour la case atuelle
				
				if ( ((*(faisceaux[i][j].getCase()))[l]).first != i || ((*(faisceaux[i][j].getCase()))[l]).second != j) {
					
					faisceaux[i][j].ajouteForceInter(	faisceaux[ (*((faisceaux[i][j]).getCase()))[l].first ][ (*((faisceaux[i][j]).getCase()))[l].second ]	); // on ajoute la force qu'exerce la particule dans la case pointée par i sur i
		
				} 
			}
			
			for (unsigned int l(0); l < ((faisceaux[i][j].getCase())->getSuivant())->size(); ++l) { // ajoute la force pour la case suivante
				
			faisceaux[i][j].ajouteForceInter(	faisceaux[ (*(((faisceaux[i][j]).getCase())->getSuivant()))[l].first ][ (*(((faisceaux[i][j]).getCase())->getSuivant()))[l].second ]	); // on ajoute la force qu'exerce la particule dans la case pointée par i sur i
				
			}
			
			for (unsigned int l(0); l < ((faisceaux[i][j].getCase())->getPrecedent())->size(); ++l) { // ajoute la force pour la case précédente
				
				faisceaux[i][j].ajouteForceInter(	faisceaux[ (*(((faisceaux[i][j]).getCase())->getPrecedent()))[l].first ][ (*(((faisceaux[i][j]).getCase())->getPrecedent()))[l].second ]	); // on ajoute la force qu'exerce la particule dans la case pointée par i sur i
				
			}
			
		}
	
	}
}

double Accelerateur::Vs() const { // Retourne la vitesse moyenne longitudinale des particules. 
	//La plupart des particules étant dans un élément droit, il n'est pas restrictif à long terme de ne considérer que ceux-ci

	pair<double, double> Vs(0, 0);
	
	for (unsigned int i(0); i < faisceaux.size(); ++i) {
		for (unsigned int j(0); j < faisceaux[i].size(); ++j) {
			
			Vecteur3D a ((faisceaux[i][j].getElement())->getSortie() - (faisceaux[i][j].getElement())->getEntree());
			
			Vs.first += sqrt((	a * ((faisceaux[i][j].vitesse()).prod_scal(a) / a.norme_carre()) 	).norme_carre());
			
			Vs.second += 1;
			
			}
		}

	return Vs.first/Vs.second;}
	
void Accelerateur::ajouteTemps() {temps += dt;}

void Accelerateur::progression(unsigned int const& fois, ostream& out) {
	// fait évoluer l'accélérateur plusieurs fois, et affiche le résultat à chaque pas via out
	
	
	for (unsigned int i(1); i <=fois ; ++i) {
		
		ajouteTemps();
		
		/*double V(Vs()); // vitesse moyenne longitudinale des particules
		
		
		for (unsigned int j(0); j < elements.size(); ++j) {
			
			if (elements[j]->type() == "CaviteRadio" or elements[j]->type() == "Dipole") {
				
	//			elements[j]->setSpecialChamp(V, typique); // on ajuste la vitesse de l'onde électrique des Cavité RadioFréquences avec la vitesse moyenne des particules
												// ou on met le bon champ au dipole, en fonction de la vitesse des particules et de la charge des particules
			}
			
			
		}*/
		
		ajouteForcesChamps(); // On ajoute une force magnétique et une force électrique à chaque particule de chaque faisceau de l'accélérateur. 
		//Les "champs" spnt en fait les champs exercés par l'élément pointé par la particule sur celle-ci
		
		lie_parts_cases();
		
		ajouteForcesInter(); // On ajoute, pour chaque faisceau, les forces inter-particules
		
		dessine(out);
		
		evolue();
	}
}

void Accelerateur::progression(unsigned int const& fois, string const& nom) {
	
	// fait évoluer l'accélérateur plusieurs fois, et écrit le résultat à chaque pas dans le fichier 'nom'

	ofstream sortie (nom.c_str());
	
	if (sortie.fail()) {cout << "ERREUR LORS DE L'ECRITURE DU FICHIER '"<< nom <<"' "<< endl; return;}

	progression(fois, sortie);
	
	sortie.close();
}

Accelerateur::~Accelerateur(){
	
	for(unsigned int i(0); i < elements.size(); ++i) {
		
		delete elements[i];
		
	}
	
	gluDeleteQuadric (quadrique);
	
}

void Accelerateur::add_part_fais(Particule const& part, double const& num){

	faisceaux[num-1].add_part(part);

}

double Accelerateur::longueur() const { // longueur de l'accélérateur

	double l(0);
	
	for (unsigned int i(0); i < elements.size(); ++i) {
		
		l += elements[i]->longueur();
		
	}

	return l;
	
}

void Accelerateur::setTypique(Particule const& part) {

	typique = part;

}

void Accelerateur::setDT (double const& d) {
	dt = d;
}

void Accelerateur::setEPS (double const& e) {
	EPS = e;}
