#include <wx/wx.h>
#include "window.h"
#include "welcomePanel.h"

Window::Window(const wxString& title) :wxFrame(NULL, wxID_ANY, title) {
    WelcomePanel* welcomePanel = new WelcomePanel(this);
    SetBackgroundColour(wxColor("#D0BFBF"));
    menubar = new wxMenuBar;
    menubar->SetBackgroundColour(wxColor("#3D50C6"));
    // about = new wxMenu;
    help = new wxMenu;
    ShareBro = new wxMenu;
    help->Append(wxID_ABOUT, wxT("&About"));
    help->Append(id_help, wxT("Learn to use"));
    file = new wxMenu;
    file->Append(wxID_ANY, wxT("&New"));
    file->Append(wxID_ANY, wxT("&Open"));
    file->Append(wxID_ANY, wxT("&Save"));
    file->AppendSeparator();

    imp = new wxMenu;
    imp->Append(wxID_ANY, wxT("1"));
    imp->Append(wxID_ANY, wxT("2"));
    imp->Append(wxID_ANY, wxT("3"));

    file->AppendSubMenu(imp, wxT("Submenu"));
    quit = new wxMenuItem(file, wxID_EXIT, wxT("&Quit\tCtrl+W"));
    ShareBro->Append(quit);
    menubar->Append(ShareBro, wxT("&ShareBro"));
    menubar->Append(file, wxT("&File"));
    menubar->Append(help, wxT("&Help"));
    // menubar->Append(about, wxT("&About"));

    Connect(wxID_EXIT, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(Window::OnQuit));
    Connect(wxEVT_CLOSE_WINDOW, wxCloseEventHandler(Window::OnClose));
    Connect(wxID_ABOUT, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(Window::OnAbout));
    Connect(id_help, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(Window::OnLearnToUse));

    SetMenuBar(menubar);
    CreateStatusBar();
};

void Window::OnQuit(wxCommandEvent& WXUNUSED(event)) {
    Close(true);
}

void Window::OnAbout(wxCommandEvent& WXUNUSED(event)) {
    wxString msg;
    wxString about = "A simple file transfer app with fast and reliable service made using core concepts of OOP in C++ aided by some popular libraries.\n\nDeveloped by: \n1. Anish Sapkota \n2. Nabin Khanal \n3. Kushal Subedi \n\n Libraries used: \n1. wxWidgets(UI) \n2. SFM(Networking)";
    msg.Printf(about);

    wxMessageBox(msg, "About", wxOK | wxICON_INFORMATION);
}

void Window::OnLearnToUse(wxCommandEvent& WXUNUSED(event)) {
    wxString msg;
    msg.Printf("Use send button for sending file.\nUse receive button for receiving file. \nMakesure both devices are connected in the same network.\nYou can even play games during sending/receiving.");

    wxMessageBox(msg, "Learn to use", wxOK | wxICON_INFORMATION);
}

void Window::OnClose(wxCloseEvent& event)
{
    wxMessageDialog* dial = new wxMessageDialog(NULL,
        wxT("Are you sure to quit?"), wxT("Question"),
        wxYES_NO | wxNO_DEFAULT | wxICON_QUESTION);

    int ret = dial->ShowModal();
    dial->Destroy();

    if (ret == wxID_YES) {
        Destroy();
    }
    else {
        event.Veto();
    }
}


void Window::setStatus(wxString status) {
    SetStatusText(status);
}