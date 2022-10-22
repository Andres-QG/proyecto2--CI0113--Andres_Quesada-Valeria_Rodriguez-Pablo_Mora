#pragma once

#include <wx/wx.h>
#include "wx/sizer.h"

class GameBoardPanel : public wxPanel 
{
  public:
    GameBoardPanel(wxFrame* parent);
    void paintEvent(wxPaintEvent & evt);
    void paintNow();
    void render(wxDC& dc);
  private:
    void OnMouseEvent(wxMouseEvent& evt);
    bool ZoneClicked(wxEvent& evt);
};