#include <wx/wx.h>
#include "window.h"
#include "welcomePanel.h"

Window::Window(const wxString& title):wxFrame(NULL, wxID_ANY, title){
    WelcomePanel *welcomePanel = new WelcomePanel(this);
    CreateStatusBar();
};

void Window::setStatus(wxString status){
    SetStatusText(status);
}