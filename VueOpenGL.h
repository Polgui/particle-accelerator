/*
 * EPFL
 * CAESV3
 * Guide wxWidgets et OpenGL
 * Mini-Projet
 */

#ifndef VUEOPENGL_H
#define VUEOPENGL_H

#include "wxIncludes"
#include "Camera.h"

class VueOpenGL: public wxGLCanvas
{
public:
	VueOpenGL(wxWindow* parent, wxSize const& taille=wxDefaultSize, wxPoint const& position=wxDefaultPosition);
	
	virtual ~VueOpenGL() {}
	
	void InitOpenGL();
	
private:
    
    wxGLContext context;
    
	void dessine(wxPaintEvent& event);

//Evenements
	void appuiTouche(wxKeyEvent& event);
	void moletteSouris(wxMouseEvent& event);
	void mouvementSouris(wxMouseEvent& event);
	void clicSouris(wxMouseEvent& event);

	int lxSouris;
	int lySouris;

	Camera camera;
	
	double centreX;		//coordonnés en x du point fixé par la camera	
	double centreY;		//			    y
	double centreZ;		//			    z
	
	bool boucle;
	
};
#endif
