#ifndef GAMEBOARDPANEL_HH
#define GAMEBOARDPANEL_HH

#include <wx/wx.h>
#include "wx/sizer.h"
#include "MiniMax.hh"
#include "Board.hh"

class GameBoardPanel : public wxPanel 
{
  public:
    GameBoardPanel(wxFrame* parent);
    GameBoardPanel(wxFrame* parent, Board board); 
    void paintEvent(wxPaintEvent & evt);
    void paintNow();
    void render(wxDC& dc);
    void renderGame(wxDC& dc);
  private:
    void OnMouseEvent(wxMouseEvent& evt);
    bool ZoneClicked(wxEvent& evt);
    Movement getTemporalMovement(double xMousePosition, double yMousePosition);
    Directions getDirection(double xPosition, double yPosition, int columnIndex, int rowIndex);
    Board myBoard;
};

#endif