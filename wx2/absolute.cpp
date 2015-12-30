#include "absolute.h"
Absolute::Absolute(const wxString &title)
 : wxFrame(NULL, -1, title, wxPoint(-1, -1), wxSize(600, 600))
{
   wxPanel *panel=new wxPanel(this,-1); //-1Ϊpanel��ID
   menubar=new wxMenuBar;
   file=new wxMenu;
   edit=new wxMenu;
   help=new wxMenu;
   menubar->Append(file,wxT("&File"));
   menubar->Append(edit,wxT("&Edit"));
   menubar->Append(help,wxT("&Help"));
   SetMenuBar(menubar);
   textctrl=new wxTextCtrl(panel,-1,wxT(""),wxPoint(-1,-1),wxSize(600, 600));
   Centre();
}
