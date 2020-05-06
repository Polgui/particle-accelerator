

#include "Application.h"
#include "Parseur.h"
#include <string>


bool Application::OnInit()
{
	init_hasard (0);
	
	accelerateur = new Accelerateur;
	
	en_pause=false;
	
	try {
		
		Parseur pars("documents/simulation.txt");
		
		pars.extraire(accelerateur);
	
	
	}
	
	catch (std::string const& erreur) {
		
		std::cerr << "ERREUR : " << erreur << std::endl;
		
	}
	
	fenetreGL=new FenetreGL(wxT("Accelerateur"), wxSize(1000, 800));
	
	
	timer=new wxTimer(this);
	timer->Start(100);
		Connect(wxID_ANY, wxEVT_TIMER, wxTimerEventHandler(Application::rafraichir));
	
	return (fenetreGL!=0);
	
}

void Application::pause(){
	if (en_pause) en_pause=false;
	else en_pause=true;
}


void Application::dessine()
{	if (!en_pause){	
		accelerateur->ajouteTemps();
		
		accelerateur->ajouteForcesChamps(); // On ajoute une force magnétique et une force électrique à chaque particule de chaque faisceau de l'accélérateur. 
		//Les "champs" spnt en fait les champs exercés par l'élément pointé par la particule sur celle-ci
		
		accelerateur->lie_parts_cases();
		
		accelerateur->ajouteForcesInter(); // On ajoute, pour chaque faisceau, les forces inter-particules
		
		accelerateur->dessine(std::cout);
		
		accelerateur->evolue();

}		

		accelerateur->dessine();


}

double Application::coordX_part(){
	return accelerateur->coord_part().getX();	
}

double Application::coordY_part(){
	return accelerateur->coord_part().getY();	
}

double Application::coordZ_part(){
	return accelerateur->coord_part().getZ();	
}

void Application::vitesse1(){
accelerateur->setDT(5e-11);
}

void Application::vitesse2(){
accelerateur->setDT(10e-11);		
}

void Application::vitesse3(){
accelerateur->setDT(20e-11);		
}

void Application::rafraichir(wxTimerEvent& event)
{
fenetreGL->rafraichir();
}

Application::~Application(){
delete accelerateur;
std::cout<<"shutting down"<<std::endl;}

IMPLEMENT_APP(Application);
