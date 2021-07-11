#include "Timer.cpp"
#include "include/Client.hpp"
#include "include/Server.hpp"
#include <iostream>
#include <thread>
int main() {
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
  return 0;
}
