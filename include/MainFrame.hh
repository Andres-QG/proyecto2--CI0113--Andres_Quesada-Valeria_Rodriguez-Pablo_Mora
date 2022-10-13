#ifndef MAINFRAME_HH
#define MAINFRAME_HH

#include <wx/wx.h>

class MainFrame : public wxFrame
{
public:
  MainFrame(const wxString& title);
	void createHorizontalButtons(int nrows, int ncolumns, wxPanel* panel);
	void createVerticalButtons(int nrows, int ncolumns, wxPanel* panel);

private: 
	// Estos arreglos almacenan botones. 
	wxButton** horizontalButton;
	wxButton** verticalButton;
	// Variable que se usa para cambiar de turno. Entre cada turno se multiplica por -1. 
	int gameTurn = 1; 
	void OnMouseEvent(wxMouseEvent& evt);
	void OnButtonClicked(wxCommandEvent& evt);
};

#endif