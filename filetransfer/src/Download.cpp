#include "../include/Download.hpp"

Download::Download(const std::string Host, const std::string RemoteFile,
                   const std::string LocalFile, unsigned short Port)
    : Host(Host), LocalFile(LocalFile), RemoteFile(RemoteFile),
      outfile(LocalFile.c_str(), std::ios::out | std::ios::binary) {
  Filesize = 0;
  Http.setHost(Host, Port);
  Request.setMethod(sf::Http::Request::Get);
  Request.setUri(RemoteFile);
}
void Download::download() {
  if (!outfile.is_open()) {
    std::cout << "Error opening file" << std::endl;
    exit(1);
  }
  Page = Http.sendRequest(Request);
  Filesize = Page.getBody().size();
  std::cout << Filesize << std::endl;
  std::string FileContainer = Page.getBody();
  outfile.write(FileContainer.c_str(), Filesize); // Write the file
  outfile.close();
}
