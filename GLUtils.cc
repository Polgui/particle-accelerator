/*
 * EPFL
 * CAESV3
 * Guide wxWidgets et OpenGL
 * Mini-Projet
 */

#include "GLUtils.h"

void dessinerRepere(unsigned int alpha)
{
	
	//On met les paramètres actuels sur la pile
	glPushAttrib(GL_ALL_ATTRIB_BITS);
	
	//Activer la gestion de la transparence
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	
	glEnable(GL_LINE_SMOOTH); //Lignes anti-aliasées
	glLineWidth(5); //Epaisseur

	glBegin(GL_LINES);
	//Axe x
	glColor4ub(255,0,0,alpha); //Rouge
	glVertex3d(0,0,0);
	glVertex3d(100,0,0);
	//Axe y
	glColor4ub(0,255,0,alpha); //Vert
	glVertex3d(0,0,0);
	glVertex3d(0,100,0);
	//Axe z
	glColor4ub(0,0,255,alpha); //Bleu
	glVertex3d(0,0,0);
	glVertex3d(0,0,100);
	glEnd();
	 
	//Et on restore les paramètres précédents
	glPopAttrib();
}
