#ifndef MAINFRAME_HH
#define MAINFRAME_HH

#include <wx/wx.h>
#include <GameBoardPanel.hh>

class MainFrame : public wxFrame
{
public:
  MainFrame(const wxString& title);
  void OnTimerMF(wxTimerEvent& event);
private:
	wxTimer m_timer;
	wxTimer* timer;
	wxStaticText* staticText;
	Board board;
};



#endif