#include <MainFrame.hh>
#include <iostream>
#include <GameBoardPanel.hh>
#include <wx/dcclient.h>

// For compilers that support precompilation, includes "wx/wx.h".
#include <wx/wxprec.h>

#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif

using namespace std;

MainFrame :: MainFrame (const wxString& title): wxFrame(nullptr, wxID_ANY, title) {

    verticalButton = nullptr;
	horizontalButton = nullptr;

    wxPanel* panel = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxSize(300,550));
    auto button = new wxButton(panel, wxID_ANY, "Nueva Partida", wxPoint(100, 55), wxSize(130,40));
    wxStaticText* staticText = new wxStaticText(panel, wxID_ANY, "Points", wxPoint(100,100));

    wxPanel* game_panel = new GameBoardPanel((wxFrame*)this);
    game_panel->SetBackgroundColour(*wxWHITE);
    createHorizontalButtons(10, 10, game_panel);
	createVerticalButtons(10, 10, game_panel);
    CreateStatusBar();

	// Manejamos el evento de click izquierdo de forma din�mica. 
	game_panel->Bind(wxEVT_LEFT_DOWN, &MainFrame::OnMouseEvent, this);

    wxBoxSizer* sizer = new wxBoxSizer(wxHORIZONTAL);
    sizer->Add(panel, 1 , wxEXPAND | wxLEFT| wxTOP | wxRIGHT,10);
    sizer->Add(game_panel,2, wxEXPAND | wxALL,10);
    this->SetSizerAndFit(sizer);
    
}

// Tanto las lineas horizontales como las verticales son botones alargados. 
void MainFrame::createHorizontalButtons(int nrows, int ncolumns, wxPanel* panel) {
	double widthSize = 700.0 / (ncolumns - 1);
	double heightSize = 520.0 / (nrows - 1);
	horizontalButton = new wxButton * [(nrows) * (ncolumns - 1)];
	double rowStartPosition = 27.0;
	for (int j = 0; j < ncolumns-1; j++) {
		double columStartPosition = 30;
		for (int i = 0; i < nrows; i++) {
			horizontalButton[i * (ncolumns - 1) + j] = new wxButton(panel, 11000 + (i * (ncolumns - 1) + j), "", wxPoint(rowStartPosition, columStartPosition + 5.5), wxSize(widthSize + 4, 4));// wxBORDER_NONE);
			horizontalButton[i * (ncolumns - 1) + j]->SetBackgroundColour(wxColour(*wxWHITE)); 
			columStartPosition += heightSize;
			//Manejamos de forma din�mica el evento de click en un bot�n. 
			horizontalButton[i * (ncolumns - 1) + j]->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &MainFrame::OnButtonClicked, this); 
		}
		rowStartPosition += widthSize;
	}
}

void MainFrame::createVerticalButtons(int nrows, int ncolumns, wxPanel* panel){
	double widthSize = 700.0 / (ncolumns - 1);
	double heightSize = 500.0 / (nrows - 1);
	verticalButton = new wxButton * [(nrows-1) * ncolumns];
	double rowStartPosition = 27.0;
	for (int j = 0; j < ncolumns; j++) {
		double columStartPosition = 30;
		for (int i = 0; i < nrows-1; i++) {
			verticalButton[i * (ncolumns) + j] = new wxButton(panel, 12000 + (i * (ncolumns ) + j), "", wxPoint(rowStartPosition+6, columStartPosition), wxSize (4, heightSize+4));// wxBORDER_NONE);
			verticalButton[i * (ncolumns) + j]->SetBackgroundColour(wxColour(*wxWHITE));
			columStartPosition += heightSize;

			verticalButton[i * (ncolumns)+j]->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &MainFrame::OnButtonClicked, this);
		}
		rowStartPosition += widthSize;
	}
}

// Est� funci�n de llama cuando se da click sobre un bot�n. 
void MainFrame::OnButtonClicked(wxCommandEvent& evt) {
	// Para obtener la Id del bot�n. 
	int id = evt.GetId();
	int buttonID; 
	// Est� l�gica se usa para transformar la ID del bot�n a la posici�n del objeto en el arreglo.  
	// Para botones verticales 
	if (id >= 11000 && id < 12000) {
		buttonID = id - 11000;
		horizontalButton[buttonID]->Enable(false);
		if (gameTurn == 1) {
			horizontalButton[buttonID] ->SetBackgroundColour(wxColour(*wxBLUE));
		}
		else {
			horizontalButton[buttonID]->SetBackgroundColour(wxColour(*wxRED));
		}
	}
	// Para botones verticales. 
	else if(id >= 12000 && id < 13000) {
		buttonID = id - 12000;
		verticalButton[buttonID]->Enable(false);
		if (gameTurn == 1) {
			verticalButton[buttonID]->SetBackgroundColour(wxColour(*wxBLUE));
		}
		else {
			verticalButton[buttonID]->SetBackgroundColour(wxColour(*wxRED));
		}
	}
	// Para cambiar de turnos. 
	gameTurn *= -1; 

}

void MainFrame::OnMouseEvent(wxMouseEvent& evt) {
	// Para obtener la posici�n del mouse. 
	wxPoint position = evt.GetPosition();
	wxString message = wxString::Format("Left mouse click (x=%d, y=%d)", position.x, position.y);
 	wxLogStatus(message);
}