#ifndef MAINWINDOW
#define MAINWINDOW

#include <cstring>
#include <wx/wx.h>


class Window : public wxFrame {
private:
    bool playing_game;
    enum { id_help = 1 };

public:
    Window(const wxString& title);
    void setStatus(wxString status);
    wxMenuBar* menubar;
    wxMenu* help;
    wxMenu* eNarad;
    wxMenuItem* quit;

    void OnQuit(wxCommandEvent& title);
    void OnClose(wxCloseEvent& event);
    void OnAbout(wxCommandEvent& event);
    void OnLearnToUse(wxCommandEvent& event);

    void onPlayTicTacToeClick(wxCommandEvent& event);
    void PlayGame();
};

#endif
