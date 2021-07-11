#include <wx/wx.h>
#include "window.h"
#include "welcomePanel.h"

Window::Window(const wxString& title):wxFrame(NULL, wxID_ANY, title){
    WelcomePanel *welcomePanel = new WelcomePanel(this);

    menubar = new wxMenuBar;
    about = new wxMenu;
    help = new wxMenu;
    ShareBro = new wxMenu;

    file = new wxMenu;
    file->Append(wxID_ANY, wxT("&New"));
    file->Append(wxID_ANY, wxT("&Open"));
    file->Append(wxID_ANY, wxT("&Save"));
    file->AppendSeparator();

    imp = new wxMenu;
    imp -> Append(wxID_ANY, wxT("1"));
    imp->Append(wxID_ANY, wxT("2"));
    imp->Append(wxID_ANY, wxT("3"));

    file->AppendSubMenu(imp, wxT("Submenu"));
    quit = new wxMenuItem(file, wxID_EXIT, wxT("&Quit\tCtrl+W"));
    ShareBro->Append(quit);
    menubar->Append(ShareBro, wxT("&ShareBro"));
    menubar->Append(file, wxT("&File"));
    menubar->Append(help, wxT("&Help"));
    menubar->Append(about, wxT("&About"));

    Connect(wxID_EXIT, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(Window::OnQuit));
    Connect(wxEVT_CLOSE_WINDOW, wxCloseEventHandler(Window::OnClose));
    SetMenuBar(menubar);
    CreateStatusBar();
};

void Window::OnQuit(wxCommandEvent& WXUNUSED(event)){
    Close(true);
}

void Window::OnClose(wxCloseEvent& event) 
{
  wxMessageDialog *dial = new wxMessageDialog(NULL,
    wxT("Are you sure to quit?"), wxT("Question"),
    wxYES_NO | wxNO_DEFAULT | wxICON_QUESTION);

    int ret = dial->ShowModal();
    dial->Destroy();

    if (ret == wxID_YES) {
        Destroy();
    } else {
        event.Veto();
    }
}


void Window::setStatus(wxString status){
    SetStatusText(status);
}