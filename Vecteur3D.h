#ifndef PRJ_VECTEUR_H
#define PRJ_VECTEUR_H
#include <iostream>

class Vecteur3D {
	
	protected :
	
	// Attributs
	
	double x;
	
	double y;
	
	double z;
	
	public :
	
	// Méthodes
	
	Vecteur3D (double X, double Y, double Z);
	
	Vecteur3D ();


	// Operator


	friend std::ostream& operator<<(std::ostream& out, Vecteur3D const& vect);

	
	
	bool operator==(Vecteur3D const& vect) const; //booléen renvoyant true si ==

	Vecteur3D operator+(Vecteur3D const& autre)const;// Vecteur + autre

	Vecteur3D& operator +=(Vecteur3D const& vect);

	Vecteur3D operator-(Vecteur3D const& autre)const;// Vecteur - autre

	Vecteur3D& operator -=(Vecteur3D const& vect);

	Vecteur3D operator*(double const& scal) const;// Vecteur * scal
	
	Vecteur3D operator^(Vecteur3D const& autre)const;//Vecteur^autre
		
	Vecteur3D operator~ () const; //vecteur unitaire(norme==1)
	

	Vecteur3D rotation(Vecteur3D a,double t)const; //Rotation d'angle t(radian) par rapport à l'axe a

	//
	void set (double X, double Y, double Z); // affecte les valeurs pour toutes les coordonnées
	
	void setX (double X); 
		
	void setY (double Y);

	void setZ (double Z);
		
	double getX ()const;
	
	double getY ()const;
		
	double getZ ()const;

	double prod_scal(Vecteur3D const& autre)const;//Vecteur°autre (produit scalaire)
		
	double prod_mixte (Vecteur3D const& v, Vecteur3D const& w)const; // Vecteur * (v^w)
		
	Vecteur3D oppose() const ; // opposé du vecteur
	
	double norme_carre() const ; // sa norme au carré
	
	};

class Vecteur2D : public Vecteur3D { // c'est un vecteur3D, avec z = 0
	
public:
	
	Vecteur2D (double X, double Y);
	
	Vecteur2D (Vecteur3D const& vect);
	
	Vecteur2D ();
	
	
};
#endif
