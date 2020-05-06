#include <iostream>
#include <vector>
#include <cmath>
#include "Vecteur3D.h"
using namespace std;


	Vecteur3D::Vecteur3D (double X,double Y,double Z) // valeurs par défaut
	
	: x(X),y(Y),z(Z) 
	
	{} 

	Vecteur3D::Vecteur3D () : x(0), y(0), z(0) {}
	
	 
	ostream& operator<<(ostream& out, Vecteur3D const& vect)
	
	{
		out << "(" << vect.x << "," << vect.y << "," << vect.z << ")";
		return out;
	}
	
		
	double Vecteur3D::getX ()const{
		
		return x;
		
		}
	
	double Vecteur3D::getY () const{
		
		return y;
		
		}
		
	double Vecteur3D::getZ () const{
		
		return z;
		
		}
	
	bool Vecteur3D::operator== (Vecteur3D const& vect1) const {  // retourne true si les vecteurs sont égaux
	
	if (vect1.x == x && vect1.y == y && vect1.z == z) {
		
		return true;
		
		}
	else return false;
	}  
	
	
	Vecteur3D Vecteur3D::operator +(Vecteur3D const& autre) const  {
		
		Vecteur3D vect(autre.x + x, autre.y + y, autre.z +z); //retourne vect = Vecteur principal + autre
		
		return vect; 
		
		}
	
	Vecteur3D& Vecteur3D::operator +=(Vecteur3D const& vect)  {
		
		return (*this = *this + vect);; 
		
		}
		
	Vecteur3D Vecteur3D::operator -(Vecteur3D const& autre) const {
		
		Vecteur3D vect(-autre.x + x, -autre.y + y, -autre.z +z); // vect = Vecteur principal - autre
		
		return vect; 
		
		}
		
	Vecteur3D& Vecteur3D::operator -=(Vecteur3D const& vect)  {
		
		return (*this = *this - vect);; 
		
		}	
		
	Vecteur3D Vecteur3D::operator * (double const& scal) const {
		
		Vecteur3D vect(x * scal, y * scal, z * scal); //vect = Vecteur principal * l
		
		return vect;
		
		}
	
	double Vecteur3D::prod_scal(Vecteur3D const& autre) const {
		
		return x*autre.x + y*autre.y + z*autre.z ; 
		
		}
		

		
	Vecteur3D Vecteur3D::operator ^(Vecteur3D const& autre) const {
		
		Vecteur3D vect((y*autre.z - autre.y*z),(-x*autre.z + autre.x*z),(x*autre.y - autre.x*y)); // vect est le produit vectoriel de Vecteur principal et autre
		
		return vect;
		
		}	
		
	double Vecteur3D::prod_mixte (Vecteur3D const& v, Vecteur3D const& w) const{
		
		double prod; // prod = Vecteur principal ° (v^w)
		
		Vecteur3D u(x, y, z);
		
		prod = u.prod_scal(v^w);
		
		return prod;
		
		}
		
	Vecteur3D Vecteur3D::oppose() const { //retourne le vecteur opposé
		
		Vecteur3D vect(-x,-y,-z); 
		
		return vect;
		
		}
	
	double Vecteur3D::norme_carre() const { //retourne le CARRE de la norme
	
		return (x*x+y*y+z*z);
		
		}
		
	Vecteur3D Vecteur3D::operator~ () const  { //retourne le vecteur unitaire  (norme ==1)
	  
		Vecteur3D vect  (x/sqrt (norme_carre()),
						 y/sqrt (norme_carre()),
						 z/sqrt (norme_carre())
						 );
		
		return vect;
		
	    }
	    
	    
	Vecteur3D Vecteur3D::rotation(Vecteur3D a,double t) const { //a=axe de rot; t=angle en Radians
		
		a=~a;
		Vecteur3D X(x,y,z);
		Vecteur3D V_rot( X*cos(t)+(a*( (1-cos(t) ) * (a.prod_scal(X)) ) )+ (a^X)*sin(t) );

		
		return V_rot;
		
		}    
	    
	void Vecteur3D::set (double X, double Y, double Z) { // Affecte toutes les valeurs d'un vecteur
		
		x = X; y = Y; z = Z;
		
		}
	
	void Vecteur3D::setX (double X) { // Affecte la coordonnée x
		
		x = X;
		
		}
		
	void Vecteur3D::setY (double Y) { // Affecte la coordonnée y
		
		y = Y;
		
		}
	void Vecteur3D::setZ (double Z) { // Affecte la coordonnée z
		
		z = Z;
		
		}

///////////////////////////////////////////////////////////////////////////////////////////

Vecteur2D::Vecteur2D (double X,double Y) // valeurs par défaut

: Vecteur3D(X, Y, 0) {} 

Vecteur2D::Vecteur2D (Vecteur3D const& vect) : Vecteur3D(vect.getX(), vect.getY(), 0) {}

Vecteur2D::Vecteur2D () : Vecteur3D() {}


