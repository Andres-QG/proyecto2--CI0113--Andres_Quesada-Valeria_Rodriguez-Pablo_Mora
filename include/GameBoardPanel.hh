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
    void playGame();
    short scorePlayer1;
    short scorePlayer2;
  private:
    void OnMouseLeftClick(wxMouseEvent& evt);
    void OnMouseLeftClick2(wxMouseEvent& evt);
    void OnMouseLeftClick3(wxMouseEvent& evt);
    void OnMouseMove(wxMouseEvent& evt);
    void drawTemporalLine(wxDC& dc, int rowIndex, int columIndex, Directions direction, double cellWidth, double cellHeight); 
    bool ZoneClicked(wxEvent& evt);
    Movement getTemporalMovement(double xMousePosition, double yMousePosition);
    Directions getDirection(double xPosition, double yPosition, int columnIndex, int rowIndex);
    Board myBoard;
    short gameTurn = 1; 
};

#endif