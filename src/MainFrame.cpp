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

    wxPanel* panel = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxSize(300,550));
    wxSize size = panel->GetSize();
    auto button = new wxButton(panel, wxID_ANY, "Nueva Partida", wxPoint((size.x)/5 * 2, 50), wxSize(130,40));
    wxStaticText* staticText = new wxStaticText(panel, wxID_ANY, "Points", wxPoint(100,100));

    Board board = {4,6};
    Movement move11 = {1,1, SOUTH};
    move11.playAndAssignOwner(board, PLAYER1);
    Movement moveE = {1,1, EAST};
    moveE.playAndAssignOwner(board, PLAYER1);
    Movement moveS = {2,2, EAST};
    moveS.playAndAssignOwner(board, PLAYER2);
    Movement move3 = {0,0, WEST};
    move3.playAndAssignOwner(board, PLAYER1);
    Movement move4 = {1,0, WEST};
    move4.playAndAssignOwner(board, PLAYER2);
    Movement move5 = {1,0, NORTH};
    move5.playAndAssignOwner(board, PLAYER2);
    Movement move6 = {2,2, SOUTH};
    move6.playAndAssignOwner(board, PLAYER1);
    Movement move7 = {0,0, SOUTH}; 
    move7.playAndAssignOwner(board, PLAYER2); 
    Movement move8 = {0,0, NORTH};
    move8.playAndAssignOwner(board, PLAYER2);

    wxPanel* game_panel = new GameBoardPanel((wxFrame*)this, board);

    game_panel->SetBackgroundColour(*wxWHITE);
    CreateStatusBar();

    wxBoxSizer* sizer = new wxBoxSizer(wxHORIZONTAL);
    sizer->Add(panel, 1 , wxEXPAND | wxLEFT| wxTOP | wxRIGHT,10);
    sizer->Add(game_panel,2, wxEXPAND | wxALL,10);
    this->SetSizerAndFit(sizer);
    
}
