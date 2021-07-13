#include <wx/wx.h>
#include "window.h"

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
};