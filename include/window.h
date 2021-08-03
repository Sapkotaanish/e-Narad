#ifndef MAINWINDOW
#define MAINWINDOW

#include <cstring>
#include <wx/wx.h>

class Window : public wxFrame {
private:
    enum { id_help = 1 };

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

    void OnQuit(wxCommandEvent &title);
    void OnClose(wxCloseEvent &event);
    void OnAbout(wxCommandEvent &event);
    void OnLearnToUse(wxCommandEvent &event);
};

#endif
