#include "Client.hpp"
#include "Server.hpp"
#include "window.h"
#include <mutex>
#include <thread>
#include <wx/wx.h>

enum {
  create_button,
  join_button,
};

class WelcomePanel : public wxPanel {
private:
  wxArrayString files;
  std::thread t;
  void Send();
  void Receive();
  bool initialized;
  bool sending, receiving;
  unsigned int sender_port, receiver_port;

public:
  WelcomePanel(Window* window);
  Window* currentWindow;
  void onCreateClick(wxCommandEvent& event);
  void onJoinClick(wxCommandEvent& event);
  ~WelcomePanel();
};
