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
  int nrows = 10;
  int ncolumns = 10;
  double widthSize = 700.0 / (ncolumns-1);
	double heightSize = 520.0 / (nrows-1);
  double rowStartPosition = 27.0;
  for (int i = 0; i < ncolumns + 1; i++) {
    double columStartPosition = 30.0;
    for (int j = 0; j < nrows + 1; j++) {
      dc.DrawCircle(rowStartPosition, columStartPosition ,5);
      columStartPosition += heightSize;
    }
    rowStartPosition += widthSize;
  }
}