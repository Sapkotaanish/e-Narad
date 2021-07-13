#include <wx/wx.h>
#include <thread>
#include "window.h"
#include "Client.hpp"
#include "Server.hpp"

enum
{
    create_button,
    join_button,
};

class WelcomePanel : public wxPanel
{
private:
    wxArrayString files;
    std::thread t;
    void Send();
    void Receive();

public:
    WelcomePanel(Window *window);

    Window *currentWindow;

    void onCreateClick(wxCommandEvent &event);
    void onJoinClick(wxCommandEvent &event);
    ~WelcomePanel();
};