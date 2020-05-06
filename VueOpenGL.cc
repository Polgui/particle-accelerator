#include "VueOpenGL.h"
#include "Application.h"
#include "GLUtils.h"
#include <iostream>

using namespace std;

VueOpenGL::VueOpenGL(wxWindow* parent, wxSize const& taille, wxPoint const& position)
 :wxGLCanvas(parent, wxID_ANY, NULL,position, taille, wxSUNKEN_BORDER|wxFULL_REPAINT_ON_RESIZE|WX_GL_DOUBLEBUFFER),
  centreX(0),centreY(0),centreZ(0), context(this)
{
	//Evènements
	Connect(wxEVT_PAINT, wxPaintEventHandler(VueOpenGL::dessine));
    Connect(wxEVT_KEY_DOWN, wxKeyEventHandler(VueOpenGL::appuiTouche));
    
	Connect(wxEVT_MOUSEWHEEL, wxMouseEventHandler(VueOpenGL::moletteSouris));
	Connect(wxEVT_MOTION, wxMouseEventHandler(VueOpenGL::mouvementSouris));
	Connect(wxEVT_LEFT_DOWN, wxMouseEventHandler(VueOpenGL::clicSouris));
	Connect(wxEVT_LEFT_UP, wxMouseEventHandler(VueOpenGL::clicSouris));
	Connect(wxEVT_RIGHT_DOWN, wxMouseEventHandler(VueOpenGL::clicSouris));
	Connect(wxEVT_RIGHT_UP, wxMouseEventHandler(VueOpenGL::clicSouris));
	
	SetCursor(wxCURSOR_SIZENESW);
	SetFocus();
}



void VueOpenGL::InitOpenGL() 
{
    context.SetCurrent(*this);

	glEnable(GL_DEPTH_TEST);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluPerspective(65.0, 4./3., 0.001, 100.0);
	glClearColor(0.0, 0.0, 0.0, 1.0);
	
	glMatrixMode(GL_MODELVIEW);
}
void VueOpenGL::dessine(wxPaintEvent& event)
{
	
    context.SetCurrent(*this);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	
	glLoadIdentity();
	
if (boucle) //mode particule
	{
		centreX=wxGetApp().coordX_part();
		centreY=wxGetApp().coordY_part();
		centreZ=wxGetApp().coordZ_part();
	}


	camera.setVue(centreX,centreY,centreZ);

	dessinerRepere(100);
	

	wxGetApp().dessine();
	
	
	glFlush();
	SwapBuffers();

	
}

 
void VueOpenGL::appuiTouche(wxKeyEvent& event)
{

	switch(event.GetKeyCode())
	{
			case WXK_LEFT:
			camera.setPhi(camera.getPhi() + 0.03);
			break;
			case WXK_RIGHT:
			camera.setPhi(camera.getPhi() - 0.03);
			break;
			case WXK_UP:
				camera.setTheta(camera.getTheta() - 0.03);
			break;
			case WXK_DOWN:
				camera.setTheta(camera.getTheta() + 0.03);
			break;
			case 'Q':
				camera.setR(camera.getR() - 0.1);
			break;
			case 'E':
				camera.setR(camera.getR() + 0.1);
			break;
			case 'R': //reset totalement la camera
				camera.resetVue();
				centreX=0;
				centreY=0;
				centreZ=0;
			break;
			case 'W':
				centreX+=0.1*sin(camera.getPhi()+(M_PI));//permet de faire avancer le point fixé par rapport au point ou on se trouve
				centreY+=0.1*cos(camera.getPhi()+(M_PI));
			break;
			case 'A':
				centreX+=0.1*sin(camera.getPhi()+(M_PI/2));
				centreY+=0.1*cos(camera.getPhi()+(M_PI/2));
			break;
			case 'S':
				centreX+=0.1*sin(camera.getPhi());
				centreY+=0.1*cos(camera.getPhi());
			break;
			case 'D':
				centreX+=0.1*sin(camera.getPhi()+(3*M_PI/2));
				centreY+=0.1*cos(camera.getPhi()+(3*M_PI/2));
			break;
			case WXK_PAGEUP:
				centreZ+=0.1;
			break;
			case WXK_PAGEDOWN:
				centreZ-=0.1;
			break;
			case WXK_SPACE: //permet de mettre en pause l'accelerateur
				wxGetApp().pause();
			break;
			case 'P':
				
			if (boucle) {boucle=false;}
			else boucle=true;
				

			break;
			case 'Z':
			camera.zoom0(); //zoom au max
			break;
			case '1':
			wxGetApp().vitesse1();
			break;
			case '2':
			wxGetApp().vitesse2();
			break;
			case '3':
			wxGetApp().vitesse3(); //attention entraine parfois quelques erreurs
			break;
			case WXK_ESCAPE :
			wxGetApp().~Application();
			exit(1);
			break;
	}

	
}

void VueOpenGL::moletteSouris(wxMouseEvent& event)
{
    camera.setR(camera.getR()-event.GetWheelRotation()/1200.0);
   
}

void VueOpenGL::clicSouris(wxMouseEvent& event)
{
   event.GetPosition(&lxSouris,&lySouris);
}

void VueOpenGL::mouvementSouris(wxMouseEvent& event)
{
    if (event.LeftIsDown())
    {
        int x(0), y(0);
        event.GetPosition(&x,&y);
        
        double xdouble((lxSouris-x)), ydouble((lySouris-y));//pour permettre de diviser la différence

        camera.setTheta(camera.getTheta()-(ydouble/60));
        camera.setPhi(camera.getPhi()+((xdouble/60)));
         
        event.GetPosition(&lxSouris,&lySouris);

    }
} 

