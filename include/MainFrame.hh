#ifndef MAINFRAME_HH
#define MAINFRAME_HH

#include <wx/wx.h>

class MainFrame : public wxFrame
{
public:
  MainFrame(const wxString& title);

private:
  void OnPaint(wxPaintEvent& evt);
  
};

#endif