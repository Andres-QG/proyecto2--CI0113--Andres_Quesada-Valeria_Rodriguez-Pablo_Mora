#include <MainFrame.hh>
#include <iostream>
#include <GameBoardPanel.hh>
#include <wx/dcclient.h>
#include <Movement.hh>


// For compilers that support precompilation, includes "wx/wx.h".
#include <wx/wxprec.h>

#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif

using namespace std;

MainFrame :: MainFrame (const wxString& title): wxFrame(nullptr, wxID_ANY, title) {

    wxPanel* panel = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxSize(200,300));
    wxSize size = panel->GetSize();
    auto button = new wxButton(panel, wxID_ANY, "Nueva Partida", wxPoint(3, 20), wxSize(100,40));
    wxStaticText* staticText = new wxStaticText(panel, wxID_ANY, "Points", wxPoint(10, 100));


    Board board = {4,6};
    //Board board = {11,11};
    wxPanel* game_panel = new GameBoardPanel((wxFrame*)this, board, HUMAN, ALFABETA_PRUNING);
    game_panel->SetDoubleBuffered(true);
    game_panel->SetBackgroundColour(*wxWHITE);
    CreateStatusBar();
    wxString message = wxString::Format("Player                   Points\n\nPlayer 1:                    %d\nPlayer 2:                    %d", board.getScoreP1(), board.getScoreP2());

    staticText->SetLabel(message);
    wxBoxSizer* sizer = new wxBoxSizer(wxHORIZONTAL);
    sizer->Add(panel, 1 , wxEXPAND | wxLEFT| wxTOP | wxRIGHT, 1);
    sizer->Add(game_panel, 2, wxEXPAND | wxLEFT | wxTOP | wxRIGHT, 1);
    this->SetSizerAndFit(sizer);
    
    
}
