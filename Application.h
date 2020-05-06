
#ifndef APPLICATION_H
#define APPLICATION_H


#include "wxIncludes"
#include "Accelerateur.h"
#include "FenetreGL.h"


class Accelerateur;

class Application : public wxApp
{
	public:
		
		~Application();

		void dessine();
	
		void pause();
		
		void vitesse1();
		void vitesse2();
		void vitesse3();
		
		double coordX_part();
		double coordY_part();
		double coordZ_part();
	private:
		
		FenetreGL* fenetreGL;
		bool OnInit();
		
		bool loaded;
		
		void rafraichir(wxTimerEvent& event);
		
		Accelerateur* accelerateur;
		
		wxTimer* timer;
		
		bool en_pause;

		

};
DECLARE_APP(Application);

#endif
