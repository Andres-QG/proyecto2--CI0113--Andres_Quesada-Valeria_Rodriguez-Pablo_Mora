#include <MainFrame.hh>
#include <iostream>
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

void MainFrame::OnPaint(wxPaintEvent& evt)
{
    wxPaintDC dc(this);

    dc.SetPen(*wxBLACK_PEN);
    dc.SetBrush(*wxBLACK_BRUSH);
    for (int i = 0; i < 8; i++) {
        dc.DrawCircle(330,35*i+1 ,5);
    }
}

wxBEGIN_EVENT_TABLE(MainFrame,wxFrame)
    EVT_PAINT(MainFrame::OnPaint)
wxEND_EVENT_TABLE()