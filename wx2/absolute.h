#ifndef absolute_H_INCLUDED
#define absolute_H_INCLUDED
#include<wx/wx.h>
class Absolute:public wxFrame
{
public:
    Absolute(const wxString &title);
    wxMenuBar *menubar;
    wxMenu *file;
    wxMenu *edit;
    wxMenu *help;
    wxTextCtrl *textctrl;
};
#endif
