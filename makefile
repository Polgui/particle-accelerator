CC  = g++
CXX = g++

CXXFLAGS= `wx-config --cxxflags` -g -Wall
LDLIBS   = `wx-config --libs gl,core,base`

VPATH=src

all: Application
Vecteur3D.o: Vecteur3D.cc Vecteur3D.h
Particule.o: Particule.cc Particule.h
Element.o: Element.cc Element.h
Accelerateur.o: Accelerateur.cc Accelerateur.h
Dessinable.o: Dessinable.cc Dessinable.h
Faisceau.o: Faisceau.cc Faisceau.h
Case.o: Case.cc Case.h
Couleur.o: Couleur.cc Couleur.h
VueOpenGL.o: VueOpenGL.cc VueOpenGL.h GLUtils.h
FenetreGL.o: FenetreGL.cc FenetreGL.h
Camera.o: Camera.cc Camera.h
Parseur.o: Parseur.cc Parseur.h
GLUtils.o: GLUtils.cc GLUtils.h
Application: Application.o VueOpenGL.o FenetreGL.o Camera.o GLUtils.o Vecteur3D.o Particule.o Element.o Accelerateur.o Dessinable.o Faisceau.o Case.o Couleur.o Parseur.o

godzilla: 
	@echo "GREEEUUUUUUHHHHHHH !!!!!"
	rm -f *.o core
	rm -f $(EXEC)
	rm -f *.txt core

clean:
	@echo "Godzilla!"
