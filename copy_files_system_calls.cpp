#include <iostream>
#include <fstream>
#include <string>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>

#define BUFFER_SIZE 1024

using namespace std;

void copy(const string& src, const string& dst) {
  int sfd, dfd, count;
  char buffer[BUFFER_SIZE];
  mode_t fileMode = S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH;

  sfd = open(src.c_str(), O_RDONLY);
  if (sfd < 0) {
    cerr << "ERROR: " << src << " doesn't exist" << endl;
    exit(1);
  }

  dfd = open(dst.c_str(), O_CREAT | O_WRONLY | O_TRUNC, fileMode);
  if (dfd < 0) {
    close(sfd);
    cerr << "ERROR: Failed to create or open destination file " << dst << endl;
    exit(1);
  }

  while ((count = read(sfd, buffer, BUFFER_SIZE)) > 0) {
    if (write(dfd, buffer, count) < 0) {
      close(sfd);
      close(dfd);
      cerr << "ERROR: Failed to write to destination file " << dst << endl;
      exit(1);
    }
  }

  close(sfd);
  close(dfd);
}

int main(int argc, char* argv[]) {
  if (argc != 3) {
    cerr << "ERROR: Usage: " << argv[0] << " <source_file> <destination_file>" << endl;
    return 1;
  }

  cout << "Copying " << argv[1] << " to " << argv[2] << endl;
  copy(argv[1], argv[2]);

  return 0;
}

