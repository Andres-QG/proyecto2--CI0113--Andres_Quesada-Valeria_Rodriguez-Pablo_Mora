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

    wxPanel* panel = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxSize(300,550));
    wxSize size = panel->GetSize();
    auto button = new wxButton(panel, wxID_ANY, "Nueva Partida", wxPoint((size.x)/5 * 2, 50), wxSize(130,40));
    wxStaticText* staticText = new wxStaticText(panel, wxID_ANY, "Points", wxPoint(100,100));

    wxPanel* game_panel = new GameBoardPanel((wxFrame*)this);
    game_panel->SetBackgroundColour(*wxWHITE);
    CreateStatusBar();

    wxBoxSizer* sizer = new wxBoxSizer(wxHORIZONTAL);
    sizer->Add(panel, 1 , wxEXPAND | wxLEFT| wxTOP | wxRIGHT,10);
    sizer->Add(game_panel,2, wxEXPAND | wxALL,10);
    this->SetSizerAndFit(sizer);
    
}
