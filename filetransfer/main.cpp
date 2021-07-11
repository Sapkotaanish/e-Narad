#include "Timer.cpp"
#include "include/Client.hpp"
#include "include/Download.hpp"
#include "include/Server.hpp"
#include <iostream>
int main() {
  // std::cout << "Enter s for server and c for client." << std::endl;
  // char ans;
  // std::cin >> ans;
  // Timer timer;
  // if (ans == 's') {
  //   Server sender(51000);
  //   sender.send("/home/nabin/try.cpp");
  // } else {
  //
  //   Client client(51000);
  //   client.receive("check.cpp");
  // }
  Download file(
      "https://",
      "www.google.com/"
      "url?sa=i&url=https%3A%2F%2Fwww.shutterstock.com%2Fsearch%2Fnepal&psig="
      "AOvVaw0QN0FCSXfCMGj33ZrQMTJ2&ust=1626090047410000&source=images&cd=vfe&"
      "ved=0CAoQjRxqFwoTCPiu_NP32vECFQAAAAAdAAAAABAD",
      "check.jpeg");
  file.download();

  return 0;
}
