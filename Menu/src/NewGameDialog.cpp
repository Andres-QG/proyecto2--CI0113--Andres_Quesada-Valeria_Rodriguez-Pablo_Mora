#include <wx/wx.h>
#include <NewGameDialog.hh>

NewGameDialog::NewGameDialog(wxWindow* parent, const wxString& title):
wxDialog(parent,-1, title, wxPoint(500,300), wxSize(500,400)) 
{
  wxSize size = this->GetSize();
  int height = size.y;
  int width = size.x;
  wxBoxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);
  wxBoxSizer* playerSizer = new wxBoxSizer(wxHORIZONTAL);
  wxBoxSizer* columnsRows = new wxBoxSizer(wxVERTICAL);

  //Type of players
  wxStaticText *playerOneType = new wxStaticText(this,wxID_ANY,"Type of player A: ");
  wxStaticText *playerTwoType = new wxStaticText(this,wxID_ANY,"Type of player B: ");

  wxArrayString choicesA;
  choicesA.Add("Human");
  choicesA.Add("AI-Easy");
  choicesA.Add("AI-Medium");
  choicesA.Add("AI-Hard");
  wxRadioBox *choiceA = new wxRadioBox(this, wxID_ANY, "", wxPoint((width/6)*2,height/4),wxDefaultSize,choicesA);

  wxArrayString choicesB;
  choicesB.Add("Human");
  choicesB.Add("AI-Easy");
  choicesB.Add("AI-Medium");
  choicesB.Add("AI-Hard");
  wxRadioBox *choiceB = new wxRadioBox(this, wxID_ANY, "", wxPoint((width/6)*2,height/4),wxDefaultSize,choicesB);

  playerSizer -> Add(playerOneType);
  playerSizer -> Add(choiceA);
  playerSizer -> Add(playerTwoType);
  playerSizer -> Add(choiceB);

  //Set rows and cols
  wxStaticText *nRows = new wxStaticText(this,wxID_ANY,"Rows: ");
  wxStaticText *nColumns = new wxStaticText(this,wxID_ANY,"Columns: ");
  wxSlider * rows = new wxSlider(this,wxID_ANY, 10, 2, 20, wxPoint((width/5), (height/5)*3),wxSize(200,50));
  wxSlider * columns = new wxSlider(this,wxID_ANY, 10, 2, 20, wxPoint((width/5), (height/6)*5),wxSize(200,50));

  columnsRows->Add(nRows);
  columnsRows->Add(rows);
  columnsRows->Add(nColumns);
  columnsRows->Add(columns);

  wxSizer* buttonSizer = CreateButtonSizer(wxOK);
  mainSizer->Add(playerSizer,0, wxLEFT | wxBOTTOM,5);
  mainSizer->Add(columnsRows, 0, wxEXPAND | wxBOTTOM, 5);
  mainSizer->Add(buttonSizer,0,wxALIGN_RIGHT|wxBOTTOM,5);
  SetSizer(mainSizer);
  SetMinSize(wxSize(400,200));
  Fit();
}

