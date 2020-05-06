#include "FenetreGL.h"
#include "Application.h"


FenetreGL::FenetreGL(wxString const& titre, wxSize const& taille)
:wxFrame(0, wxID_ANY, titre, wxDefaultPosition, taille, wxDEFAULT_FRAME_STYLE & ~ (wxRESIZE_BORDER  | wxMAXIMIZE_BOX))
,
vueOpenGL(new VueOpenGL(this))
{
	
	Center();
	
	Show();
	
	vueOpenGL->InitOpenGL(); //Attention à l'ordre !
	
}

void FenetreGL::rafraichir()
{	
	vueOpenGL->Refresh(false);
}
