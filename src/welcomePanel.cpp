#include "welcomePanel.h"
<<<<<<< HEAD
#include <thread>

=======
#include <iostream>
#include <wx/wx.h>
>>>>>>> integration

WelcomePanel::WelcomePanel(Window* window)
  : wxPanel(window, wxID_ANY, wxDefaultPosition, wxSize(200, 800)),
  initialized(false) {
  window->SetBackgroundColour(wxColor("#fff"));
  wxBoxSizer* pSizer = new wxBoxSizer(wxVERTICAL);


  currentWindow = window;

  wxButton* createButton = new wxButton(this, create_button, "Send",
    wxDefaultPosition, wxSize(150, 40));
  pSizer->AddStretchSpacer(1);

  wxButton* joinButton = new wxButton(this, join_button, "Receive",
    wxDefaultPosition, wxSize(150, 40));

  createButton->SetBackgroundColour(wxColor("#3D50C6"));
  joinButton->SetBackgroundColour(wxColor("#3D50C6"));


  sending = false;
  pSizer->AddStretchSpacer(1);
  pSizer->Add(createButton, 0, wxALIGN_CENTER);
  // pSizer->AddSpacer((10, 10));
  pSizer->Add(joinButton, 0, wxALIGN_CENTER);
  pSizer->AddStretchSpacer(1);

  this->SetSizer(pSizer);
  this->Layout();

  // opens file dialog on click
  Connect(create_button, wxEVT_COMMAND_BUTTON_CLICKED,
    wxCommandEventHandler(WelcomePanel::onCreateClick));
  joinButton->Bind(wxEVT_BUTTON, &WelcomePanel::onJoinClick, this);
};

<<<<<<< HEAD


void WelcomePanel::onCreateClick(wxCommandEvent& event)
{
=======
void WelcomePanel::onCreateClick(wxCommandEvent& event) {

  if (!initialized) {
    std::mutex m;
    m.lock();
    sender_port = 50000;
    receiver_port = 48000;
    initialized = true;
    m.unlock();
  }
>>>>>>> integration

  if (!sending) {
    wxFileDialog* openFileDialog =
      new wxFileDialog(this, "", "", "", "", wxFD_MULTIPLE | wxFD_PREVIEW);
    if (openFileDialog->ShowModal() == wxID_OK) {
      openFileDialog->GetPaths(files);
      Server::count = files.size();
      std::thread thr(&WelcomePanel::Send, this);
      thr.detach();
    }
<<<<<<< HEAD

};

void WelcomePanel::onJoinClick(wxCommandEvent& event)
{
    t = std::thread(&WelcomePanel::Receive, this);
=======
  }
  else {
    std::cout << "sending already" << std::endl;
  }
};

void WelcomePanel::onJoinClick(wxCommandEvent& event) {
  currentWindow->setStatus(wxString("Receive"));
  if (!initialized) {
    std::mutex m;
    sender_port = 48000;
    receiver_port = 50000;
    initialized = true;
  }
  if (!receiving) {
    std::thread thr(&WelcomePanel::Receive, this);
    thr.detach();
  }
  else {
    std::cout << "Receiving already" << std::endl;
  }
>>>>>>> integration
};

void WelcomePanel::Send() {
  std::mutex m;
  m.lock();
  sending = true;
  m.unlock();
  Server server(sender_port, files);
  m.lock();
  sending = false;
  m.unlock();
  sender_port++;
}

<<<<<<< HEAD
void WelcomePanel::Receive()
{
    Client client(51000);
};

// void WelcomePanel::showDialog(){
//     wxMessageDialog *dial = new wxMessageDialog(NULL,
//     wxT("Ask your friend to join..."), wxT("Listening"),
//     wxOK);
//     dial->SetOKLabel(_("&Cancel"));
//     int ret = dial->ShowModal();
// 
//     std::cout << ret;
//     if (ret == wxID_OK) {
//         Destroy();
//     };
// 
// }
=======
void WelcomePanel::Receive() {
  std::mutex m;
  m.lock();
  receiving = true;
  m.unlock();
  Client client(receiver_port);
  m.lock();
  receiving = false;
  m.unlock();
  receiver_port++;
}
>>>>>>> integration

WelcomePanel::~WelcomePanel() {
  std::cout << "its working dick heads." << std::endl;
}
