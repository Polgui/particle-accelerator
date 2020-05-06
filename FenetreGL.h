/*
 * EPFL
 * CAESV3
 * Guide wxWidgets et OpenGL
 * Mini-Projet
 */

#ifndef FENETREGL_H
#define FENETREGL_H

#include "wxIncludes"
#include "VueOpenGL.h"


class FenetreGL: public wxFrame
{
public:
	FenetreGL(wxString const& titre, wxSize const& taille);
	
	void rafraichir();
private:
	VueOpenGL* vueOpenGL;
};
#endif
