#include "Timer.cpp"
#include "include/Download.hpp"
#include "include/FileClient.hpp"
#include "include/FileServer.hpp"
#include <iostream>
#include <thread>

void send() {
  Server sender(51000);
  sender.send("/home/nabin/Documents/Advance mathematics.pdf");
}
void receive() {
  Client client(51000);
  client.receive("check.pdf");
}

int main() {
  // std::cout << "Enter s for server and c for client." << std::endl;
  // char ans;
  // std::cin >> ans;
  // Timer timer;
  // std::thread t;
  // if (ans == 's') {
  //   t = std::thread(send);
  // } else {
  //   t = std::thread(receive);
  // }

  // Download file("http://74.125.13.83", "/get_video?video_id=qg1ckCkm8YI",
  // "Check.txt", 80);
  // file.download();
  return 0;
}
