#include <wx/wx.h>
#include "window.h"
#include "Client.hpp"
#include "Server.hpp"


enum {
    create_button,
    join_button,
};

class WelcomePanel : public wxPanel {
public:
    WelcomePanel(Window* window);

    Window* currentWindow;


    void onCreateClick(wxCommandEvent& event);
    void onJoinClick(wxCommandEvent& event);
    void showDialog();
};