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
        wxMenu *help;
        wxMenu *about;
        wxMenu *imp;
        wxMenu *ShareBro;
        wxMenuItem *quit;

        void OnQuit(wxCommandEvent& title);
        void OnClose(wxCloseEvent& event);

};

#endif