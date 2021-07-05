#include <wx/wx.h>
#include "window.h"
#include "welcomePanel.h"

Window::Window(const wxString& title):wxFrame(NULL, wxID_ANY, title){
    WelcomePanel *welcomePanel = new WelcomePanel(this);

    menubar = new wxMenuBar;

    file = new wxMenu;
    file->Append(wxID_ANY, wxT("&New"));
    file->Append(wxID_ANY, wxT("&Open"));
    file->Append(wxID_ANY, wxT("&Save"));
    file->AppendSeparator();

    imp = new wxMenu;
    imp -> Append(wxID_ANY, wxT("Import newfeed list..."));
    imp->Append(wxID_ANY, wxT("Import bookmarks..."));
    imp->Append(wxID_ANY, wxT("Import mail..."));

    file->AppendSubMenu(imp, wxT("I&mport"));
    quit = new wxMenuItem(file, wxID_EXIT, wxT("&Quit\tCtrl+W"));
    file->Append(quit);
    menubar->Append(file, wxT("&File"));
    Connect(wxID_EXIT, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(Window::OnQuit));
    SetMenuBar(menubar);
    CreateStatusBar();
};

void Window::OnQuit(wxCommandEvent& WXUNUSED(event)){
    Close(true);
}
void Window::setStatus(wxString status){
    SetStatusText(status);
}