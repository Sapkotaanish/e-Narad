#include <wx/wx.h>
#include <iostream>
#include "welcomePanel.h"
<<<<<<< HEAD
#include <thread>

WelcomePanel::WelcomePanel(Window* window) : wxPanel(window, wxID_ANY, wxDefaultPosition, wxSize(200, 800)) {
=======

WelcomePanel::WelcomePanel(Window *window) : wxPanel(window, wxID_ANY, wxDefaultPosition, wxSize(200, 800))
{
>>>>>>> 9b5ac9b0ba51a33dcacfbbe2495082f2f8007314

    currentWindow = window;

    wxButton *createButton = new wxButton(this, create_button, "Send", wxDefaultPosition, wxSize(150, 40));
    wxButton *joinButton = new wxButton(this, join_button, "Receive", wxDefaultPosition, wxSize(150, 40));

    wxBoxSizer *pSizer = new wxBoxSizer(wxVERTICAL);

    pSizer->AddStretchSpacer(1);
    pSizer->Add(createButton, 0, wxALIGN_CENTER);
    pSizer->AddSpacer((10, 10));
    pSizer->Add(joinButton, 0, wxALIGN_CENTER);
    pSizer->AddStretchSpacer(1);

    this->SetSizer(pSizer);
    this->Layout();

    //opens file dialog on click
    Connect(create_button, wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(WelcomePanel::onCreateClick));
    joinButton->Bind(wxEVT_BUTTON, &WelcomePanel::onJoinClick, this);
};

<<<<<<< HEAD

void WelcomePanel::onCreateClick(wxCommandEvent& event) {
    Server sender(51000);
    std::thread t1(&Server::start, &sender);

    wxMessageDialog *dial = new wxMessageDialog(NULL,
    wxT("Ask your friend to join..."), wxT("Listening"),
    wxYES_NO);
    dial->SetYesNoLabels(_("&Done"), _("&Cancel"));
    int ret = dial->ShowModal();

    if(ret == wxID_NO){
        t1.detach();
    }else{
        currentWindow->setStatus(wxString("Creating Hotspot"));
        wxFileDialog* openFileDialog = new wxFileDialog(this, "", "", "", "", wxFD_MULTIPLE | wxFD_PREVIEW);
        if (openFileDialog->ShowModal() == wxID_OK) {
            wxArrayString filename;
            openFileDialog->GetPaths(filename);
            for (auto file : filename) {
                std::cout << "Selected files: " << file << std::endl;
                sender.send((std::string)file);
            }

        };

        t1.detach();
=======
void WelcomePanel::onCreateClick(wxCommandEvent &event)
{

    wxFileDialog *openFileDialog = new wxFileDialog(this, "", "", "", "", wxFD_MULTIPLE | wxFD_PREVIEW);
    if (openFileDialog->ShowModal() == wxID_OK)
    {
        openFileDialog->GetPaths(files);
        t = std::thread(&WelcomePanel::Send, this);
>>>>>>> 9b5ac9b0ba51a33dcacfbbe2495082f2f8007314
    }

};

void WelcomePanel::onJoinClick(wxCommandEvent &event)
{
    t = std::thread(&WelcomePanel::Receive, this);
    currentWindow->setStatus(wxString("Receive"));
};

void WelcomePanel::Send()
{
    Server server(51000, files);
}

void WelcomePanel::Receive()
{
    Client client(51000);
<<<<<<< HEAD
    client.receive("receivedfile.cpp");
    currentWindow->setStatus(wxString("Joining Hotspot"));
};

void WelcomePanel::showDialog(){
    wxMessageDialog *dial = new wxMessageDialog(NULL,
    wxT("Ask your friend to join..."), wxT("Listening"),
    wxOK);
    dial->SetOKLabel(_("&Cancel"));
    int ret = dial->ShowModal();

    std::cout << ret;
    if (ret == wxID_OK) {
        Destroy();
    };

}
=======
}

WelcomePanel::~WelcomePanel()
{
    t.join();
}
>>>>>>> 9b5ac9b0ba51a33dcacfbbe2495082f2f8007314
