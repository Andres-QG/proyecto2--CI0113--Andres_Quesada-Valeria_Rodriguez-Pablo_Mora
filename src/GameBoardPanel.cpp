#include <App.hh>
#include <MainFrame.hh>
#include <GameBoardPanel.hh>

#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif

GameBoardPanel::GameBoardPanel(wxFrame* parent) :
wxPanel(parent) 
{
  Bind(wxEVT_PAINT, &GameBoardPanel::paintEvent, this);
}

void GameBoardPanel::paintEvent(wxPaintEvent & evt){
  wxPaintDC dc(this);
  render(dc);
}

void GameBoardPanel::paintNow() {
  wxClientDC dc(this);
  render(dc);
}

void GameBoardPanel::render(wxDC& dc) {
  dc.SetPen(*wxBLACK_PEN);
  dc.SetBrush(*wxBLACK_BRUSH);
  for (int i = 0; i < 8; i++) {
    dc.DrawCircle(330,35*i+1 ,5);
  }
}