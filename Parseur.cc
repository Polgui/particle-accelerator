
#include "Parseur.h"
#include "Accelerateur.h"
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;


double str2double(string const& str) {
	
	double extracted(0.0); 
	
	istringstream is(str); 
	
	is >> extracted; 
	
	return extracted;
}

// CONSTRUCTEUR + DESTRUCTEUR

Parseur::Parseur (string const& chaine) {
	
	 fichier.open(chaine.c_str());
	
		if (fichier.fail()) {throw string("PROBLEME LORS DE L'OUVERTURE DU FICHIER " + chaine);}
	
}

Parseur::~Parseur(){
	
	fichier.close();

}

// TROUVE LA BALISE SUIVANTE + ENREGISTRE LE CONTENU D'UNE BALISE

string Parseur::chercheBalise(){
	
	char trace(' ');
	
	while (!fichier.eof() and trace != '<') {
		
		fichier.get(trace);
		
	}
	
	string balise("");
	
	while (!fichier.eof() and trace!= '>') {
		
		fichier.get(trace);
		
		if (trace != '>') balise += trace;
		
	}
	
	return balise;
	
}

string Parseur::enregistreBalise (string const& str) {
	
	string valeur("");
	
	char trace(' ');
	
	while (!fichier.eof() and trace != '<') {
		
		fichier.get(trace);
		
		valeur += trace;
		
	}
	
	string balise("");
	
	while (!fichier.eof() and trace!= '>') {
		
		fichier.get(trace);
		
		if (trace != '<' and trace != '>' and trace != ' ') balise += trace;
		
	}
	
	if (balise == "/"+str) return valeur;
	
	else throw string ("BALISE INCORRECTE DANS " + str + " (mauvaise balise fermante ou nouvelle balise ouvrante)");
	
	
}

// METHODES EXTRAIRE[...]

void Parseur::extraire (Accelerateur* acc) {
	
	while (!fichier.eof()) {
	
		string balise (chercheBalise());
		
		if (balise == "systeme") {
			
			extraireSysteme(acc);
			
			acc->lie_elements();
		}
		
		else if (balise == "") {return;}
		
		else throw string ("BALISE INCORRECTE EN PREMIERE COUCHE");
	}
	
}

void Parseur::extraireSysteme(Accelerateur* acc) {

	string balise ("");
	
	while (!fichier.eof()) {
	
		balise = chercheBalise();
		
		if (balise == "/systeme") return;
		
		else if (balise == "dt") acc->setDT(trouveDouble("dt"));
		
		else if (balise == "eps") acc->setEPS(trouveDouble("eps"));
		
		else if (balise == "accelerateur") extraireAccelerateur (acc);
		
		else throw string ("BALISE INCORRECTE DANS SYSTEME");
		
	}

}

void Parseur::extraireAccelerateur (Accelerateur* acc) {
	
	string balise ("");
	
	while (!fichier.eof()) {
		
		balise = chercheBalise();
		
		if (balise == "/accelerateur") return;
		
		else if (balise == "typique") {extraireTypique (acc);}
		
		else if (balise == "section") {extraireSection(acc);}
		
		else if (balise == "dipole") {extraireDipole(acc);}
		
		else if (balise == "quadrupole") {extraireQuadrupole(acc);}
		
		else if (balise == "fodo") {extraireFODO(acc);}
		
		else if (balise == "sextupole") {extraireSextupole(acc);}
		
		else if (balise == "cavite") {extraireCavite(acc);}
		
		else if (balise == "faisceau") {extraireFaisceau (acc);}
		
		else throw string ("BALISE INCORRECTE DANS ACCELERATEUR");
		
	}
	
}

void Parseur::extraireTypique (Accelerateur* acc) {
	
	Particule typ;
	
	string balise ("");
	
	while (!fichier.eof()) {
		
		balise = chercheBalise();
		
		if (balise == "/typique") {acc->setTypique(typ); return;}
		
		else if (balise == "masse") typ.setMasse (trouveDouble("masse"));
		
		else if (balise == "charge") typ.setCharge (trouveDouble("charge"));
		
		else throw string ("BALISE INCORRECTE DANS TYPIQUE");
		
	}
}

void Parseur::extraireSection(Accelerateur* acc) {

	string balise ("");
	
	Vecteur3D entree, sortie;
	
	double rayon;
	
	while (!fichier.eof()) {
		
		balise = chercheBalise();
		
		if (balise == "/section") {
			
			SectionDroite sec (entree, sortie, rayon);
			
			acc->add_elem(sec); 
			
			return;}
		
		else if (balise == "entree") entree = trouveVecteur3D("entree");
		
		else if (balise == "sortie") sortie = trouveVecteur3D("sortie");
		
		else if (balise == "rayon") rayon = trouveDouble("rayon");
		
		else throw string ("BALISE INCORRECTE DANS SECTION");
		
	}

}

void Parseur::extraireDipole(Accelerateur* acc) {
	
	string balise ("");
	
	Vecteur3D entree, sortie;
	
	double rayon, Bz, k; // le rayon, le champ vertical et la courbure
	
	while (!fichier.eof()) {
		
		balise = chercheBalise();
		
		if (balise == "/dipole") {
			
			Dipole dip (entree, sortie, rayon, Bz, k);
			
			acc->add_elem(dip); 
			
			return;}
		
		else if (balise == "entree") entree = trouveVecteur3D("entree");
		
		else if (balise == "sortie") sortie = trouveVecteur3D("sortie");
		
		else if (balise == "rayon") rayon = trouveDouble("rayon");
		
		else if (balise == "Bz") Bz = trouveDouble("Bz");
		
		else if (balise == "k") k = trouveDouble("k");
		
		else throw string ("BALISE INCORRECTE DANS DIPOLE");
		
	}
	
}

void Parseur::extraireQuadrupole(Accelerateur* acc) {
	
	string balise ("");
	
	Vecteur3D entree, sortie;
	
	double rayon, b;
	
	while (!fichier.eof()) {
		
		balise = chercheBalise();
		
		if (balise == "/quadrupole") {
			
			Quadrupole quad (entree, sortie, rayon, b);
			
			acc->add_elem(quad); 
			
			return;}
		
		else if (balise == "entree") entree = trouveVecteur3D("entree");
		
		else if (balise == "sortie") sortie = trouveVecteur3D("sortie");
		
		else if (balise == "rayon") rayon = trouveDouble("rayon");
		
		else if (balise == "b") b = trouveDouble("b");
		
		else throw string ("BALISE INCORRECTE DANS QUADRUPOLE");
		
	}
	
}

void Parseur::extraireSextupole(Accelerateur* acc) {
	
	string balise ("");
	
	Vecteur3D entree, sortie;
	
	double rayon, b;
	
	while (!fichier.eof()) {
		
		balise = chercheBalise();
		
		if (balise == "/sextupole") {
			
			Sextupole sex (entree, sortie, rayon, b);
			
			acc->add_elem(sex); 
			
			return;}
		
		else if (balise == "entree") entree = trouveVecteur3D("entree");
		
		else if (balise == "sortie") sortie = trouveVecteur3D("sortie");
		
		else if (balise == "rayon") rayon = trouveDouble("rayon");
		
		else if (balise == "b") b = trouveDouble("b");
		
		else throw string ("BALISE INCORRECTE DANS SEXTUPOLE");
		
	}
	
}

void Parseur::extraireFODO(Accelerateur* acc) {
	
	string balise ("");
	
	Vecteur3D entree, sortie;
	
	double rayon, b, L;
	
	while (!fichier.eof()) {
		
		balise = chercheBalise();
		
		if (balise == "/fodo") {
			
			MailleFODO fodo (entree, sortie, rayon, b, L);
			
			acc->add_elem(fodo); 
			
			return;}
		
		else if (balise == "entree") entree = trouveVecteur3D("entree");
		
		else if (balise == "sortie") sortie = trouveVecteur3D("sortie");
		
		else if (balise == "rayon") rayon = trouveDouble("rayon");
		
		else if (balise == "b") b = trouveDouble("b");
		
		else if (balise == "L") L = trouveDouble("L");
		
		else throw string ("BALISE INCORRECTE DANS MAILLE FODO");
		
	}
	
}

void Parseur::extraireCavite(Accelerateur* acc) {
	
	string balise ("");
	
	Vecteur3D entree, sortie;
	
	double rayon, zero, psi, V, lambda;
	
	while (!fichier.eof()) {
		
		balise = chercheBalise();
		
		if (balise == "/cavite") {
			
			CaviteRadio cav (zero, V, lambda, psi, entree, sortie, rayon);
			
			acc->add_elem(cav); 
			
			return;}
		
		else if (balise == "entree") entree = trouveVecteur3D("entree");
		
		else if (balise == "sortie") sortie = trouveVecteur3D("sortie");
		
		else if (balise == "rayon") rayon = trouveDouble("rayon");
		
		else if (balise == "zero") zero = trouveDouble("zero");
		
		else if (balise == "psi") psi = trouveDouble("psi");
		
		else if (balise == "V") V = trouveDouble("V");
		
		else if (balise == "lambda") lambda = trouveDouble("lambda");
		
		else throw string ("BALISE INCORRECTE DANS CAVITE RADIO FREQUENCE");
		
	}
	
}

void Parseur::extraireFaisceau(Accelerateur* acc) {
	
	string balise ("");
	
	Particule type;
	
	double lambda, nombre, bunch, dv, emittance, aud, add, numero;
	
	while (!fichier.eof()) {
		
		balise = chercheBalise();
		
		if (balise == "/faisceau") {
			
			acc->lie_part_elem(type, numero);
			
			Faisceau fais (type, lambda, dv, bunch, emittance, aud, add, nombre);
			
			acc->add_fais(fais); 
			
			return;}
		
		else if (balise == "type") type = trouveParticule("type");
		
		else if (balise == "lambda") lambda = trouveDouble("lambda");
		
		else if (balise == "nombre") nombre = trouveDouble("nombre");
		
		else if (balise == "bunch") bunch = trouveDouble("bunch");
		
		else if (balise == "dv") dv = trouveDouble("dv");
		
		else if (balise == "emittance") emittance = trouveDouble("emittance");
		
		else if (balise == "aud") aud = trouveDouble("aud");
		
		else if (balise == "add") add = trouveDouble("add");
		
		else if (balise == "element") numero = trouveDouble ("element");
		
		else throw string ("BALISE INCORRECTE DANS FAISCEAU");
		
	}
	
}

// METHODE TROUVEdouble + TROUVEvecteur3D + TROUVEparticule

double Parseur::trouveDouble(string const& Balise) {

	string chaine = enregistreBalise (Balise);
	
	return str2double (chaine);

}

Vecteur3D Parseur::trouveVecteur3D(string const& Balise) {

	double x(-100), y(-101), z(-102); // valeurs de x, y et z du vecteur
	
	bool a(false), b(false), c(false); // représente si, respectivement, x, y et z ont été définis
	
	char trace(' ');
	
	string str ("");
	
	while (!fichier.eof() and trace != '<' and a == false) {
		
		fichier.get(trace);
		
		if (trace != ' ' and trace != '<') {
			
			str += trace;
		
		}
		
		if ((trace == ' ' and str != "") or trace == '<') {
			
			x = str2double (str);
			
			a = true;
		
		}
		
	}
	
	str = "";
	
	while (!fichier.eof() and trace != '<' and b == false) {
		
		fichier.get(trace);
		
		if (trace != ' ' and trace != '<') {
			
			str += trace;
			
		}
		
		if ((trace == ' ' and str != "") or trace == '<') {
			
			y = str2double (str);
			
			b = true;
			
		}
		
	}
	
	str = "";
	
	while (!fichier.eof() and trace != '<' and c == false) {
		
		fichier.get(trace);
		
		if (trace != ' ' and trace != '<') {
			
			str += trace;
			
		}
		
		if ((trace == ' ' and str != "") or trace == '<') {
			
			z = str2double (str);
			
			c = true;
			
		}
		
	}
	
	str = "";
	
	if (c == false) throw string ("COEFFICIENTS DE VECTEUR INCORRECTS DANS " + Balise + " (did you forget the '&' ?)" );
	
	Vecteur3D vecteur(x, y, z);
	
	string balise("");
	
	while (!fichier.eof() and trace!= '>') {
		
		fichier.get(trace);
		
		if (trace != '<' and trace != '>' and trace != ' ') balise += trace;
		
	}
	
	if (balise == "/"+Balise) return vecteur;
	
	else throw string ("BALISE INCORRECTE DANS " + Balise + " (mauvaise balise fermante ou nouvelle balise ouvrante)");
	

}

Particule Parseur::trouveParticule (string const& Balise) {

	string balise ("");
	
	double energie, masse, charge;
	
	Vecteur3D position, direction;
	
	while (!fichier.eof()) {
		
		balise = chercheBalise();
		
		if (balise == "/" + Balise) {
			
			Particule part (position, energie, direction, masse, charge);
			
			return part;}
		
		else if (balise == "energie") energie = trouveDouble("energie");
		
		else if (balise == "masse") masse = trouveDouble("masse");
		
		else if (balise == "charge") charge = trouveDouble("charge"); 
		
		else if (balise == "position") position = trouveVecteur3D("position");
		
		else if (balise == "direction") direction = trouveVecteur3D("direction");
		
		else throw string ("BALISE INCORRECTE DANS LA PARTICULE " + Balise);
		
	}

throw string ("PAS DE PARTICULES TROUVEE DANS " + Balise);}
