#include "MainFrame.h"
#include <wx/wx.h>
#include <wx/spinctrl.h>


// TODO: Manejar los eventos siempre de forma din�mica, es m�s sencillo de programar. 
// Macros para la table de eventos est�tica // NO USAR. 
//wxBEGIN_EVENT_TABLE(MainFrame, wxFrame)
	//EVT_BUTTON(wxID_ANY, OnButtonClicked)
//END_EVENT_TABLE()

MainFrame::MainFrame(): wxFrame(nullptr, wxID_ANY, "Dots and Boxes") {
	squareButton = nullptr; 
	verticalButton = nullptr;
	horizontalButton = nullptr;

	//Dentro del `MainFrame` tenemos al panel `gamePanel` que va a ser el encartado de contener el "dibujo" del juego. 
	wxPanel* gamePanel = new wxPanel(this);
	createSquareButtons(10, 10, gamePanel);
	createHorizontalButtons(10, 10, gamePanel);
	createVerticalButtons(10, 10, gamePanel);


	// La idea es usar esta barra para irnos ayudando con las cordinadas en el panel principal.
	// TODO: Borrar antes de entregar el proyecto. 
	CreateStatusBar();

	// Manejamos el evento de click izquierdo de forma din�mica. 
	gamePanel->Bind(wxEVT_LEFT_DOWN, &MainFrame::OnMouseEvent, this);



	//TODO: esto lo mantengo porque algunos objetos nos pueden funcionar luego. Borrar antes de entegrar. 
	/* 
	wxButton* button = new wxButton(panel, wxID_ANY, "Button", wxPoint(150, 50), wxSize(100, 35), wxBU_LEFT);

	wxCheckBox* checkBox = new wxCheckBox(panel, wxID_ANY, "CheckBox", wxPoint(550, 55));

	wxStaticText* staticText = new wxStaticText(panel, wxID_ANY, "StaticText - NOT editable", wxPoint(120, 150));
	
	wxTextCtrl* textCtrl = new wxTextCtrl(panel, wxID_ANY, "TextCTol -editable", wxPoint(500, 145), wxSize(200, -1));

	wxSlider* slider = new wxSlider(panel, wxID_ANY, 25, 0, 100, wxPoint(100, 250), wxSize(200, -1));

	wxGauge* gauge = new wxGauge(panel, wxID_ANY, 100, wxPoint(500, 255), wxSize(200, -1)); 
	gauge->SetValue(50);

	wxArrayString choices;
	choices.Add("Item A");
	choices.Add("Item B");
	choices.Add("Item C");

	wxChoice* choice = new wxChoice(panel, wxID_ANY, wxPoint(150, 375), wxSize(100, -1), choices);
	choice->Select(0); 

	wxSpinCtrl* spinCtrl = new wxSpinCtrl(panel, wxID_ANY, "", wxPoint(550, 375), wxSize(100, -1));

	wxListBox* listBox = new wxListBox(panel, wxID_ANY, wxPoint(150, 475), wxSize(100, -1), choices);

	wxRadioBox* radioBox = new wxRadioBox(panel, wxID_ANY, "RadioBox", wxPoint(555, 450), wxDefaultSize, choices, 1);
	
	*/
}

// Este m�todo se encarga de inicializar y dibujar los cuadros. Notar que el dibujo se realiza sobre `gamePanel`.
// Por el momento, los cuadros son botones pintados de negro y desactivados. En buena teoria, deberia ser sencillo
// cambiar esos botones por otro tipo de objetos (en plan circulos). Aunque puede que hacer que hacer alg�n ajuste minimo
// en la posici�n de las l�neas verticales y horizontales. 
void MainFrame::createSquareButtons(int nrows, int ncolumns, wxPanel* panel) {
	//Todos estos calculos est�n para una ventana de 800x600 px. 
	//TODO: Por el momento el tama�o de los objetos no cambia. Hay que investigar un poco sobre sizer a ver que se puede hacer. 
	// NO estoy seguro si al momento de usar sizer vamos a tener problemas con los calculos que se hicieron para una ventana de 800x600px. 
	// Eleg� ese tama�o porque se ve�a bien en mi laptop de 14 pulgadas, no hay otra raz�n. 

	//La idea es dejar aproximadamente 30 px en los bordes. 
	double widthSize = 720.0 / (ncolumns-1);
	double heightSize = 540.0 / (nrows-1);
	squareButton = new wxButton * [ncolumns * nrows];
	double rowStartPosition = 27.0;
	for (int i = 0; i < ncolumns; i++) {
		double columStartPosition = 30.0;
		for (int j = 0; j < nrows; j++) {
			// Notar que `i*ncolumns + j` es una forma de transformar los datos de i y j en una sola dimenci�n que va de 0 a `ncolumns * nrows`.
			// Notar que `10000 + (i * ncolumns + j)` se usa para asignar la ID a los botones, si hay IDs repetidas, la llamada de un m�todo suele afectar ambos objetos. 
			squareButton[i*ncolumns + j] = new wxButton(panel, 10000 + (i * ncolumns + j), "", wxPoint(rowStartPosition, columStartPosition), wxSize(15, 15), wxBORDER_NONE);
			// Cambiamos el color del boton a negro. 
			squareButton[i * ncolumns + j] ->SetBackgroundColour(wxColour(*wxBLACK));
			// Desactivamos el bot�n. 
			squareButton[i * ncolumns + j]-> Disable();
			columStartPosition += heightSize;
		}
		rowStartPosition += widthSize;
	}
	

}

// Tanto las lineas horizontales como las verticales son botones alargados. 
void MainFrame::createHorizontalButtons(int nrows, int ncolumns, wxPanel* panel) {
	double widthSize = 720.0 / (ncolumns - 1);
	double heightSize = 540.0 / (nrows - 1);
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
	double widthSize = 720.0 / (ncolumns - 1);
	double heightSize = 540.0 / (nrows - 1);
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

MainFrame:: ~MainFrame() {
	delete[] squareButton ;
	delete[] verticalButton;
	delete[] horizontalButton;
	// TODO: Verificar si este destructor es necesario y si est� bien construido. 
}