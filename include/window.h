#ifndef MAINWINDOW
#define MAINWINDOW

#include <wx/wx.h>
#include <cstring>

class Window : public wxFrame{

    public:
        Window(const wxString &title);
        void setStatus(wxString status);

        wxMenuBar *menubar;
        wxMenu *file;
        wxMenu *imp;
        wxMenuItem *quit;

        void OnQuit(wxCommandEvent& title);
};

#endif