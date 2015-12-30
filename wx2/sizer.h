#ifndef SIZER_H_INCLUDED
#define SIZER_H_INCLUDED
#include<wx/wx.h>
class Sizer:public wxFrame
{
public:
    Sizer(const wxString &title); wxMenuBar *menubar;
    wxMenu *file;
    wxMenu *edit;
    wxMenu *help;
    wxTextCtrl *textctrl;
};


#endif // SIZER_H_INCLUDED
