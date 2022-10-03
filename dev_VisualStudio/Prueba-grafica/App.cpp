#include "App.h"
#include "MainFrame.h"
#include <wx/wx.h>

// Macro para indicar la clase "principal". 
wxIMPLEMENT_APP(App);

bool App :: OnInit() {
	// MainFrame es el panel o ventana principal de la app, el resto de los objetos van a ser sus hijos. 
	MainFrame* mainFrame = new MainFrame();
	mainFrame->SetClientSize(800, 600);
	mainFrame->Center();
	mainFrame->Show();
	return true; 

}