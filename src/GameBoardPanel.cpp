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
  Bind(wxEVT_LEFT_DOWN, &GameBoardPanel::OnMouseEvent, this);
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
  wxSize size = this->GetSize();
  dc.SetPen(*wxBLACK_PEN);
  int nrows = 10;
  int ncolumns = 10;
  double widthSize = size.x / (ncolumns+1);
	double heightSize = size.y / (nrows+1);
  double rowStartPosition = 27.0;
  for (int i = 0; i < ncolumns + 1; i++) {
    double columStartPosition = 30.0;
    for (int j = 0; j < nrows + 1; j++) {
      dc.SetBrush(*wxBLACK_BRUSH);
      dc.DrawCircle(rowStartPosition, columStartPosition ,5);
      dc.SetBrush(*wxWHITE_BRUSH);
      if (!(j == nrows)) {
        dc.DrawRectangle(rowStartPosition-5, columStartPosition + 5, 10, (rowStartPosition+widthSize+2)-rowStartPosition);
      }
      if (!(i==ncolumns)) {
        dc.DrawRectangle(rowStartPosition+5, columStartPosition - 5, (columStartPosition+heightSize-2)-columStartPosition, 10);
      }
      columStartPosition += heightSize;
    }
    rowStartPosition += widthSize;
  }
}

void GameBoardPanel::OnMouseEvent(wxMouseEvent& evt) {
  // Para obtener la posici�n del mouse. 
	wxPoint position = evt.GetPosition();
	wxString message = wxString::Format("Left mouse click (x=%d, y=%d)", position.x, position.y);
 	wxLogStatus(message);
}

bool GameBoardPanel::ZoneClicked(wxEvent& evt) {
  return true;
}