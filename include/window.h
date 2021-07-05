#ifndef MAINWINDOW
#define MAINWINDOW

#include <wx/wx.h>
#include <cstring>

class Window : public wxFrame{

    public:
        Window(const wxString &title);

        void setStatus(wxString status);

};

#endif