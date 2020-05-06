#include "Camera.h"
#include <math.h>
#include <OpenGL/glu.h>


#define DEFAULT_R 5
#define DEFAULT_THETA 11*M_PI/24
#define DEFAULT_PHI 7*M_PI/12 

Camera::Camera()
:r(DEFAULT_R), phi(DEFAULT_PHI) , theta(DEFAULT_THETA)
{
}
double Camera::getR() const
{
	return r;
}
double Camera::getPhi() const
{
	return phi;
}
double Camera::getTheta() const
{
	return theta;
}
	
void Camera::setR(double r)
{
	this->r=r;
	restreindre();
}
void Camera::setPhi(double phi)
{
	this->phi=phi;
	restreindre();
}
void Camera::setTheta(double theta)
{
	this->theta=theta;
	restreindre();
}

void Camera::setVue() const
{
	gluLookAt(r*sin(theta)*sin(phi), r*sin(theta)*cos(phi), r*cos(theta), 0.0, 0.0, 0.0, 0.0, 0.0, 1.0);
	
}

void Camera::setVue(double x,double y,double z) const
{
	gluLookAt(x+r*sin(theta)*sin(phi), y+r*sin(theta)*cos(phi),z+ r*cos(theta),x+0.0, y+0.0, z+0.0, 0.0, 0.0, 1.0);

}

void Camera::resetVue()
{

	r=DEFAULT_R;
	theta=DEFAULT_THETA;
	phi=DEFAULT_PHI;
}

void Camera::zoom0()
{
r=0.1;
theta=M_PI/2;
phi=0;
}

void Camera::restreindre()
{
	if(r<=0.1) r=0.1;
	if (theta<0.1) theta=0.1;
	if (theta>3) theta=3;
	}
