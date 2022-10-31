#include <wx/wx.h>
#include <NewGameDialog.hh>

NewGameDialog::NewGameDialog(wxWindow* parent, const wxString& title):
wxDialog(parent,-1, title, wxPoint(500,300), wxSize(500,400)) 
{
  //Sizers
  wxBoxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);
  wxBoxSizer* playerSizer = new wxBoxSizer(wxHORIZONTAL);
  wxBoxSizer* columnsRows = new wxBoxSizer(wxVERTICAL);
  wxBoxSizer* colors = new wxBoxSizer(wxHORIZONTAL);

  //Type of players
  wxStaticText *playerOneType = new wxStaticText(this,wxID_ANY,"Type of player A: ");
  wxStaticText *playerTwoType = new wxStaticText(this,wxID_ANY,"Type of player B: ");

  wxArrayString choicesA;
  choicesA.Add("Human");
  choicesA.Add("AI-Easy");
  choicesA.Add("AI-Medium");
  choicesA.Add("AI-Hard");
  wxRadioBox *choiceA = new wxRadioBox(this, wxID_ANY, "", wxDefaultPosition,wxDefaultSize,choicesA);

  wxArrayString choicesB;
  choicesB.Add("Human");
  choicesB.Add("AI-Easy");
  choicesB.Add("AI-Medium");
  choicesB.Add("AI-Hard");
  wxRadioBox *choiceB = new wxRadioBox(this, wxID_ANY, "", wxDefaultPosition,wxDefaultSize,choicesB);

  playerSizer -> Add(playerOneType);
  playerSizer -> Add(choiceA);
  playerSizer -> Add(playerTwoType);
  playerSizer -> Add(choiceB);

  //Set rows and cols
  wxStaticText *nRows = new wxStaticText(this,wxID_ANY,"Rows: ");
  wxStaticText *nColumns = new wxStaticText(this,wxID_ANY,"Columns: ");
  wxSlider * rows = new wxSlider(this,wxID_ANY, 10, 2, 20, wxDefaultPosition,wxSize(200,50),wxSL_LABELS|wxSL_AUTOTICKS);
  wxSlider * columns = new wxSlider(this,wxID_ANY, 10, 2, 20, wxDefaultPosition,wxSize(200,50),wxSL_LABELS|wxSL_AUTOTICKS);

  columnsRows->Add(nRows);
  columnsRows->Add(rows);
  columnsRows->Add(nColumns);
  columnsRows->Add(columns);

  //Set Color for players
  wxStaticText *colorA = new wxStaticText(this,wxID_ANY,"Choose a color to identify your turn Player A: ");
  wxStaticText *colorB = new wxStaticText(this,wxID_ANY,"Choose a color to identify your turn Player B: ");

  wxArrayString choicesColorA;
  choicesColorA.Add("Red");
  choicesColorA.Add("Green");
  choicesColorA.Add("Blue");
  choicesColorA.Add("Purple");
  wxRadioBox *choiceColorA = new wxRadioBox(this, wxID_ANY, "", wxDefaultPosition,wxDefaultSize,choicesColorA);

  wxArrayString choicesColorB;
  choicesColorB.Add("Orange");
  choicesColorB.Add("Yellow");
  choicesColorB.Add("Cyan");
  choicesColorB.Add("Pink");
  wxRadioBox *choiceColorB = new wxRadioBox(this, wxID_ANY, "", wxDefaultPosition,wxDefaultSize,choicesColorB);

  colors->Add(colorA);
  colors->Add(choiceColorA);
  colors->Add(colorB);
  colors->Add(choiceColorB);

  //Button
  wxSize size = this->GetSize();
  int height = size.y;
  int width = size.x;
  wxButton *buttonGame = new wxButton(this,wxID_ANY, wxT("Apply"), wxPoint((width/3)*2, (height/5)*3));
  Connect(wxID_ANY, wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(NewGameDialog::OnClick));

  //Puts everything together
  wxSizer* buttonSizer = CreateButtonSizer(wxOK);
  mainSizer->Add(playerSizer,0, wxLEFT | wxBOTTOM,5);
  mainSizer->Add(columnsRows, 1, wxEXPAND | wxBOTTOM, 5);
  mainSizer->Add(colors,1, wxEXPAND | wxBOTTOM, 5);
  mainSizer->Add(buttonSizer,0,wxALIGN_RIGHT|wxBOTTOM,5);
  SetSizer(mainSizer);
  SetMinSize(wxSize(400,200));
  Fit();
}

void NewGameDialog::OnClick(wxCommandEvent & event) {
  this->EndModal(wxID_APPLY);

}
