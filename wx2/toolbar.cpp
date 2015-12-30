#include "toolbar.h"
Toolbar::Toolbar(const wxString &title)
 : wxFrame(NULL, wxID_ANY, title, wxDefaultPosition, wxSize(280, 180))
{
    wxImage::AddHandler(new wxPNGHandler);
    wxBitmap exit(wxT("exit.png"),wxBITMAP_TYPE_PNG);
    wxToolBar *toolbar=CreateToolBar(); //创建一个工具栏
    toolbar->AddTool(wxID_EXIT,exit,wxT("Exit application"));
    toolbar->Realize();
    Connect(wxID_EXIT, wxEVT_COMMAND_TOOL_CLICKED,
      wxCommandEventHandler(Toolbar::OnQuit));
      Centre();

}
void Toolbar::OnQuit(wxCommandEvent& WXUNUSED(eve8nt))
{
    Close(true);
}
