#include <MainFrame.hh>

// For compilers that support precompilation, includes "wx/wx.h".
#include <wx/wxprec.h>
 
#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif

MainFrame :: MainFrame (const wxString& title): wxFrame(nullptr, wxID_ANY, title) {

}