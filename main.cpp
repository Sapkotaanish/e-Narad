#include "main.h"
#include "window.h"


IMPLEMENT_APP(MyApp);

bool MyApp::OnInit() {
    Window* window = new Window(wxString("Share Project"));
    window->Show(true);

    //window->Maximize();

    return true;
};
