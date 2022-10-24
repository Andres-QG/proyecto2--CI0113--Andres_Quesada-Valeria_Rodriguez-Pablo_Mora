#include <wx/wxprec.h>
#include <wx/wx.h>
#include <iostream>
#include <MyApp.hh>
#include <MainFrame.hh>

wxIMPLEMENT_APP(MyApp);

bool MyApp::OnInit()
{
  MainFrame* mainFrame = new MainFrame("Prueba");
  mainFrame->SetClientSize(600,400);
  mainFrame->Center();
  mainFrame->Show(true);
  return true;
}