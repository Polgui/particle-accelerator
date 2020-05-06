

#ifndef CAMERA_H
#define CAMERA_H

#include "wx/wx.h"
#include "wx/glcanvas.h"
#include "wx/progdlg.h"

class Camera
{
	public:
	
	Camera();
	
	void setVue() const;
	void setVue(double,double,double) const; //permet de changer le point fixé par la camera

	
	void resetVue(); //reset les angles et le point fixé par la camera
	
	double getR() const;
	double getPhi() const;
	double getTheta() const;
	
	void setR(double r);
	void setPhi(double phi);
	void setTheta(double theta);
	
	void zoom0(); //zoom au max possible
	
	private:
	double r;
	double phi;
	double theta;
	
	void restreindre();
	
};

#endif
