#include <App.hh>
#include <MainFrame.hh>

#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif

wxIMPLEMENT_APP(App);

bool App::OnInit() {
  MainFrame* mainFrame = new MainFrame ("Dots & Boxes");
  mainFrame->SetClientSize(800,600);
  mainFrame->Center();
  mainFrame->Show();
  return true;
}