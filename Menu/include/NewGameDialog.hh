#pragma once
#include <wx/wx.h>

class NewGameDialog : public wxDialog {
public:
  NewGameDialog(wxWindow* parent, const wxString& title);
  void OnClick(wxCommandEvent & event);
};