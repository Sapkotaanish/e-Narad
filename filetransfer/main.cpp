#include "Timer.cpp"
#include "include/Client.hpp"
#include "include/Download.hpp"
#include "include/Server.hpp"
#include <iostream>
int main() {
  std::cout << "Enter s for server and c for client." << std::endl;
  char ans;
  std::cin >> ans;
  Timer timer;
  if (ans == 's') {
    Server sender(51000);
    sender.send("/home/nabin/try.cpp");
  } else {

    Client client(51000);
    client.receive("check.cpp");
  }

  Download file("http://pixelcaster.com", "/yosemite/webcams/ahwahnee2.jpg",
                "check.jpg", 80);
  file.download();

  return 0;
}
