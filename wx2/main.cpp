#include <wx/wx.h>
#include "wx/textctrl.h"
#include "wx/menu.h"
#include "wx/file.h"
#include<iostream>
#include "wx/msgdlg.h"
#include "wx/filedlg.h"
#include "wx/datetime.h"
#include "wx/colordlg.h"
#include "wx/fontdlg.h"
using namespace std;



class window:public wxFrame
{
public:
    window(const wxString &title);
    wxBoxSizer *box;
    wxTextCtrl *text;
    wxPanel *panel;
    wxMenuBar *menubar;
    wxMenu *file;
    wxMenu *edit;
    wxMenu *help;
    wxMenu *settings;
    void Exit(wxCommandEvent &event);
    void Open(wxCommandEvent &event);
    void Save(wxCommandEvent &event);
    void Seach(wxCommandEvent &event);
    void About(wxCommandEvent &event);
    void Count(wxCommandEvent &event);
    void Save_as(wxCommandEvent &event);
    void Editor(wxCommandEvent &event);
    void New(wxCommandEvent &event);
    void Undo(wxCommandEvent &event);
    void Date(wxCommandEvent &event);
    void Colour(wxCommandEvent &event);
    void Cut(wxCommandEvent &event){text->Cut();}
    void Copy(wxCommandEvent &event){text->Copy();}
    void Paste(wxCommandEvent &event){text->Paste();}
    void Test(wxCommandEvent &event);
private:
    DECLARE_EVENT_TABLE()
    wxString path="";
    wxString path1;
};
BEGIN_EVENT_TABLE(window,wxFrame)
EVT_MENU(wxID_EXIT,window::Exit)
EVT_MENU(wxID_OPEN,window::Open)
EVT_MENU(wxID_SAVE,window::Save)
EVT_MENU(2,window::About)
EVT_MENU(3,window::Count)
EVT_MENU(4,window::Save_as)
EVT_MENU(5,window::Editor)
EVT_MENU(wxID_NEW,window::New)
EVT_MENU(6,window::Undo)
EVT_MENU(7,window::Date)
EVT_MENU(8,window::Colour)
EVT_MENU(9,window::Cut)
EVT_MENU(10,window::Copy)
EVT_MENU(11,window::Paste)
EVT_MENU(88,window::Test)
END_EVENT_TABLE()
window::window(const wxString &title)
:wxFrame(NULL,wxID_ANY,title,wxDefaultPosition,wxSize(500,500))
{
    menubar=new wxMenuBar;
    file=new wxMenu;
    edit=new wxMenu;
    help=new wxMenu;
    settings=new wxMenu;
    file->Append(wxID_NEW,wxT("New"));
    file->AppendSeparator();
    file->Append(wxID_OPEN,wxT("Open"));
    file->AppendSeparator();
    file->Append(wxID_SAVE,wxT("Save file"));
    file->Append(4,wxT("Save file as"));
    file->Append(wxID_EXIT,wxT("Quit"));
    file->Append(88,wxT("Test"));
    edit->Append(6,wxT("Undo"));
    edit->AppendSeparator();
    edit->Append(9,wxT("Cut"));
    edit->Append(10,wxT("Copy"));
    edit->Append(11,wxT("Paste"));
    edit->AppendSeparator();
    edit->Append(1,wxT("Search"));
    edit->Append(3,wxT("Count"));
    edit->AppendSeparator();
    edit->Append(7,wxT("Date"));
    help->Append(2,wxT("About"));
    settings->Append(5,wxT("Editor.."));
    settings->Append(8,wxT("Colour"));
    menubar->Append(file,wxT("File"));
    menubar->Append(edit,wxT("Edit"));
    menubar->Append(settings,wxT("Settings"));
    menubar->Append(help,wxT("Help"));
    panel=new wxPanel(this,wxID_ANY,wxDefaultPosition,wxSize(500,500));
    box=new wxBoxSizer(wxVERTICAL);
    text = new wxTextCtrl(panel, wxID_STATIC,
wxEmptyString,
wxPoint(0,20), wxSize(500,480), wxTE_MULTILINE|wxTE_RICH); //this wxTE_RICH is necessary
Centre();
box->Add(text,1,wxEXPAND, 5);
panel->SetSizer(box);
SetMenuBar(menubar);
}
class dialog: public wxDialog
{
public:
    dialog(const wxString &title);
    wxPanel *panel;
    bool TransferDataFromWindow();
    wxString GetValue();
private:
    wxString data;
    DECLARE_EVENT_TABLE()
    };
    BEGIN_EVENT_TABLE(dialog,wxDialog)
    END_EVENT_TABLE()
dialog::dialog(const wxString &title)
:wxDialog(NULL,wxID_ANY,title,wxDefaultPosition,wxSize(300,150))
{
wxBoxSizer *box=new wxBoxSizer(wxHORIZONTAL);
box->Add(new wxTextCtrl(this, wxID_STATIC,wxEmptyString,wxDefaultPosition, wxDefaultSize),1,wxALIGN_CENTER_VERTICAL);
box->AddSpacer(10);
box->Add(new wxButton(this,wxID_OK,wxT("Search")),0,wxEXPAND|wxALIGN_CENTER_VERTICAL|wxTOP|wxBOTTOM,10);
SetSizer(box);
box->SetSizeHints( this );
}
 bool dialog::TransferDataFromWindow()
    {
        wxTextCtrl *text=(wxTextCtrl *)FindWindow(wxID_STATIC);
        data=text->GetValue();
        return true;
    }
    wxString dialog::GetValue()
    {
        return data;
    }
void window::Test(wxCommandEvent &event)
{

}
void window::Seach(wxCommandEvent &event)
{
    dialog *d=new dialog("Search");
if (d->ShowModal()==wxID_OK)
{
  wxString str=d->GetValue();
  if (!str)return;
  int length=text->GetNumberOfLines();
  wxString buf;
  int strL=str.length();
  unsigned int i,j;
  bool flag=false;
  for (int k=0;k<length;++k)
  {
      buf=text->GetLineText(k);
      i=0;
      j=0;
      while(i<buf.length()-str.length()+2)
      {
          for (j=0;j<str.length();++j,++i)
          {
              if (buf[i]!=str[j])
              {
                  i=i-(j-1);
                  j=0;
                  break;
              }
          }
          if (j==str.length())
          {
              printf("lines:%d position:%d\n",k+1,i);
              int sum=0;
              for (int p=0;p<k;++p)
              sum+=text->GetLineLength(p);
              sum+=(i-str.length());
              wxTextAttr attr;
              attr.SetTextColour(*wxRED);
              text->SetStyle(sum,sum+str.length(),attr);
              flag=true;
          }
      }

  }
  if (!flag)
      {
          printf("Can't find\n");
      }
}
}
void window::Editor(wxCommandEvent &event)
{
    wxFontDialog dialog(this);
    if (dialog.ShowModal()==wxID_OK)
        {
            wxFontData retData=dialog.GetFontData();
            wxTextAttr attr;
            wxFont m_font=retData.GetChosenFont();
            attr.SetFont(m_font);
             long start,end;
        text->GetSelection(&start,&end);
        text->SetStyle(start,end,attr);
            text->Refresh();
        }
}
void window::Date(wxCommandEvent &event)
{
    wxDateTime time=wxDateTime::Now();
    wxString DT;
    text->WriteText(time.FormatDate() + "  " + time.FormatTime());
}
void window::Undo(wxCommandEvent &event)
{
    if (text->CanUndo()==true)
    text->Undo();
}
void window::New(wxCommandEvent &event)
{
    text->Clear();
}
void window::Colour(wxCommandEvent &event)
{
    wxColourData data;
    data.SetChooseFull(true);
    for (int i=0;i<16;++i)
    {
        wxColour color(i*16,i*16,i*16);
        data.SetCustomColour(i,color);
    }
    wxColourDialog dialog(this,&data);
    if (dialog.ShowModal()==wxID_OK)
    {

        wxColourData retData=dialog.GetColourData();
        wxColour col=retData.GetColour();
        wxTextAttr attr;
        attr.SetTextColour(col);
        long start,end;
        text->GetSelection(&start,&end);
        text->SetStyle(start,end,attr);


    }

}
void window::Save_as(wxCommandEvent &event)
{
    wxString wildcard =wxT("Text File (*.txt)|*.txt");
    wxString defaultFileName=wxT("text");
    wxString defaultDir=wxT("c:\\");
    wxString Caption=wxT("Choose a file");
    wxFileDialog *openFileDialog=new wxFileDialog(this,Caption,defaultDir,defaultFileName,wildcard,2);
    wxString path2;
    if (openFileDialog->ShowModal()==wxID_OK)
    {
        path2=openFileDialog->GetPath();
        text->SaveFile(path2);
        cout<<"file has saved as: "<<path2<<endl;
    }

}
void window::Count(wxCommandEvent &event)
{
    int lines,words=0;
    lines=text->GetNumberOfLines();
    if (lines==1)
       {
           words=text->GetLineLength(lines);
           if (words==0)
            lines--;
       }
    else
    {
        for (int i=0;i<lines;++i)
    words+=text->GetLineLength(i);
    }
    path.Printf(wxT("lines:%d\nwords:%d"),lines,words);
    wxMessageDialog dialog(NULL,path,wxT("Count"));
    dialog.ShowModal();
}
void window::About(wxCommandEvent &event)
{
    wxMessageDialog dialog(NULL,wxT("A little notepad made by ck.\n :-)"),wxT("About"));
    dialog.ShowModal();
}
void window::Exit(wxCommandEvent &event)
{
    Close(true);
}
void window::Open(wxCommandEvent &event)
{
    wxString wildcard =wxT("Text File (*.txt)|*.txt");
    wxString defaultFileName=wxT("text");
    wxString defaultDir=wxT("c:\\");
    wxString Caption=wxT("Choose a file");
    wxFileDialog *openFileDialog=new wxFileDialog(this,Caption,defaultDir,defaultFileName,wildcard,1);
    wxString path;
    if (openFileDialog->ShowModal()==wxID_OK)
    {
        path=openFileDialog->GetPath();
    }
    else
        {
            cout<<"open failed"<<endl;return;}
           path1=path;
    text->LoadFile(path);
    cout<<"The file: "<<path<<"  has opened\n";
}
void window::Save(wxCommandEvent &event)
{

    if (path1=="")
    {
        cout<<"no file opened"<<endl;
    }
    else
    {
    if (text->SaveFile(path1)==true);
    {
        cout<<"save successfully!"<<endl;
    }
    }
}
class app:public wxApp
{
    virtual bool OnInit();
};
IMPLEMENT_APP(app)
bool app::OnInit()
{
    window *win=new window("wxNotepad---by ck");
    win->Show(true);
    return true;
}




