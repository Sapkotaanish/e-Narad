#include "Timer.cpp"
#include "include/Client.hpp"
#include "include/Download.hpp"
#include "include/Server.hpp"
#include <iostream>
#include <thread>
int main() {
<<<<<<< HEAD
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

=======
  std::cout << "Enter s for server and c for client." << std::endl;
  char ans;
  std::cin >> ans;
  Timer timer;
  if (ans == 's') {
    Server sender(51000);
    sender.send("/mnt/Data/Movies and Series/Aligarh 2015 WebRip Hindi 720p "
                "x264 AAC ESub - mkvCinemas [Telly]/Aligarh 2015 WebRip Hindi "
                "720p x264 AAC ESub - mkvCinemas [Telly].mkv");
  } else {

    Client client(51000);
    client.receive("check.mkv");
  }
>>>>>>> 610ce9198a885fff8c087757ff483b065c13e781
  return 0;
}
