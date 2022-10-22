#ifndef APP_HH
#define APP_HH

#include <GameBoardPanel.hh>
#include <wx/wxprec.h>
 
#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif

class App : public wxApp
{
public:
  bool OnInit();
  GameBoardPanel * drawPane;

};

#endif