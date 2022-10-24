#include <wx/wx.h>

class MainFrame : public wxFrame {
public:
  MainFrame(const wxString& title);
private:
  void OnQuit(wxCommandEvent & event);
  void OnInstructions(wxCommandEvent & event);
  void OnGame(wxCommandEvent & event);
};