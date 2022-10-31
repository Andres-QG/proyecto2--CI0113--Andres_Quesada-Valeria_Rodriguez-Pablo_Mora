#pragma once
#include <wx/wx.h>
class MainFrame : public wxFrame
{
public:
	MainFrame();
	// Destructor. 
	~MainFrame();
	void createSquareButtons(int nrows, int ncolumns, wxPanel* panel);
	void createHorizontalButtons(int nrows, int ncolumns, wxPanel* panel);
	void createVerticalButtons(int nrows, int ncolumns, wxPanel* panel);

private: 
	// Estos arreglos almacenan botones. 
	wxButton** squareButton;
	wxButton** horizontalButton;
	wxButton** verticalButton;
	// Variable que se usa para cambiar de turno. Entre cada turno se multiplica por -1. 
	int gameTurn = 1; 


	void OnMouseEvent(wxMouseEvent& evt);
	void OnButtonClicked(wxCommandEvent& evt);
	//TODO: Manejar eventos de forma dinámica. 
	// TODO: NO manejar eventos de forma estática. 
	// Macro para Declar una tabla de eventos estática. 
	//wxDECLARE_EVENT_TABLE();


};

