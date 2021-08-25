#include "main.h"
#include "window.h"

IMPLEMENT_APP(MyApp);

bool MyApp::OnInit() {
    Window* window = new Window(wxString("e-Narad"));
    window->SetIcon(wxIcon("./assets/images/icon.png"));
    window->Show(true);

    // window->Maximize();

    return true;
};
