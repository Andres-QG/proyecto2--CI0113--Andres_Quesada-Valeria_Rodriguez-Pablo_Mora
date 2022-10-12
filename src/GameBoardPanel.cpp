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
  for (int i = 1; i < 9; i++) {
    for (int j = 1; j < 9; j++) {
      dc.DrawCircle(50 + i * 50 ,65 *j ,5);
    }
  }
}