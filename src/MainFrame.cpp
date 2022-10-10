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
    
    wxPanel* panel_game = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxSize(500,550));
    panel_game->SetBackgroundColour(*wxWHITE);

    wxPanel* panel = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxSize(300,550));
    auto button = new wxButton(panel, wxID_ANY, "Nueva Partida", wxPoint(100, 55), wxSize(130,40));
    wxStaticText* staticText = new wxStaticText(panel, wxID_ANY, "Points", wxPoint(100,100));

    wxBoxSizer* sizer = new wxBoxSizer(wxHORIZONTAL);
    sizer->Add(panel, 1 , wxEXPAND | wxLEFT| wxTOP | wxRIGHT,10);
    sizer->Add(panel_game,2, wxEXPAND | wxALL,10);
    this->SetSizerAndFit(sizer);
    
}