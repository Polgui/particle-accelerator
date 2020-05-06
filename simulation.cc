
#include <iostream>
#include "Accelerateur.h"
#include "Element.h"
#include "Vecteur3D.h"
#include "Parseur.h"

using namespace std;

int main() {
	
	init_hasard (1);
	
	Accelerateur* acc;
	
	acc = new Accelerateur;
	
	try {
		
		Parseur pars("documents/simulation.txt");
		
		pars.extraire(acc);
	
	
	}
	
	catch (string const& erreur) {
		
		cerr << "ERREUR : " << erreur << endl;
		
	}
	
	acc->progression(10000,cout);
	
	delete acc;
	
	return 0;
}
