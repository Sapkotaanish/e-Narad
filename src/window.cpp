#include "window.h"
#include "welcomePanel.h"

Window::Window(const wxString& title)
    : wxFrame(NULL, wxID_ANY, title, wxDefaultPosition, wxSize(600, 600),
        wxDEFAULT_FRAME_STYLE^ wxRESIZE_BORDER), playing_game(false) {
    WelcomePanel* welcomePanel = new WelcomePanel(this);
    SetBackgroundColour(wxColor("#D0BFBF"));

    //creating menubar
    menubar = new wxMenuBar;
    menubar->SetBackgroundColour(wxColor("#3D50C6"));

    //creating menu in menubar
    help = new wxMenu;
    help->Append(wxID_ABOUT, wxT("&About"));
    help->Append(id_help, wxT("Learn to use"));

    //game menu
    wxMenu* games = new wxMenu;
    games->Append(play_tictactoe, wxT("&TicTacToe\tCtrl+G"));

    //menu items
    quit = new wxMenuItem(eNarad, wxID_EXIT, wxT("&Quit\tCtrl+W"));

    //menu
    eNarad = new wxMenu;
    eNarad->Append(quit);

    //appending menus to menubar
    menubar->Append(eNarad, wxT("&e-Narad"));
    menubar->Append(help, wxT("&Help"));
    menubar->Append(games, wxT("&Games"));

    //connecting menu items to event handlers
    //quit 
    Connect(wxID_EXIT, wxEVT_COMMAND_MENU_SELECTED,
        wxCommandEventHandler(Window::OnQuit));
    //window close
    Connect(wxEVT_CLOSE_WINDOW,
        wxCloseEventHandler(Window::OnClose));
    //help::about
    Connect(wxID_ABOUT, wxEVT_COMMAND_MENU_SELECTED,
        wxCommandEventHandler(Window::OnAbout));
    //help::learn to use
    Connect(id_help, wxEVT_COMMAND_MENU_SELECTED,
        wxCommandEventHandler(Window::OnLearnToUse));

    Connect(play_tictactoe, wxEVT_COMMAND_MENU_SELECTED,
        wxCommandEventHandler(Window::onPlayTicTacToeClick));
    //finally displaying menubar
    SetMenuBar(menubar);
    CreateStatusBar();
};

//quit button handler
void Window::OnQuit(wxCommandEvent& WXUNUSED(event)) {
    Close(true);
}

//about button handler
void Window::OnAbout(wxCommandEvent& WXUNUSED(event)) {
    wxString msg;
    wxString about =
        "A simple file transfer app with fast and reliable "
        "service made using core concepts of OOP in C++ aided by "
        "some popular libraries.\n\nDeveloped by: \n1. Anish "
        "Sapkota \n2. Nabin Khanal \n3. Kushal Subedi \n\n "
        "Libraries used: \n1. wxWidgets(UI) \n2. SFML(Networking & Game)";
    msg.Printf(about);

    wxMessageBox(msg, "About", wxOK | wxICON_INFORMATION);
}

//learn to use 
void Window::OnLearnToUse(wxCommandEvent& WXUNUSED(event)) {
    wxString msg;
    msg.Printf(
        "Use send button for sending file.\nUse receive button for receiving "
        "file. \nMakesure both devices are connected in the same network.\nYou "
        "can even play games during sending/receiving.");

    wxMessageBox(msg, "Learn to use", wxOK | wxICON_INFORMATION);
}

//window close :: we raised veto  to makesure user does not close the app mistakenly
void Window::OnClose(wxCloseEvent& event) {
    wxMessageDialog* dial =
        new wxMessageDialog(NULL, wxT("Are you sure to quit?"), wxT("Question"),
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
void Window::onPlayTicTacToeClick(wxCommandEvent& event) {
    wxLogStatus("Tictactoe started");
    if (!playing_game) {
        playing_game = true;
        std::thread game_thread(&Window::PlayGame, this);
        game_thread.detach();
    }
    else {
        wxLogStatus("Already one instance is running.");
    }
}

void Window::PlayGame() {
    Board b;
    b.run();
    wxLogStatus("Tic tac toe quitted.");
    playing_game = false;
}
void Window::setStatus(wxString status) {
    SetStatusText(status);
}
