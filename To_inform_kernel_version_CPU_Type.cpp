#include <iostream>
#include <fstream>
#include <sstream>

int main() {
  std::cout << "### Kernel Information ###\n\n";

  std::ifstream versionFile("/proc/version_signature");
  if (versionFile.is_open()) {
    std::string line;
    while (std::getline(versionFile, line)) {
      std::istringstream iss(line);
      std::string kernelVersion;
      iss >> kernelVersion;
      std::cout << "Kernel Version: " << kernelVersion << std::endl;
      break;
    }
    versionFile.close();
  } else {
    std::cerr << "Error opening /proc/version_signature" << std::endl;
  }

  std::cout << "\n### CPU Information ###\n\n";

  std::ifstream cpuInfoFile("/proc/cpuinfo");
  if (cpuInfoFile.is_open()) {
    std::string line;
    while (std::getline(cpuInfoFile, line)) {
      if (line.find("processor") != std::string::npos ||
          line.find("model") != std::string::npos) {
        std::cout << line << std::endl;
      }
    }
    cpuInfoFile.close();
  } else {
    std::cerr << "Error opening /proc/cpuinfo" << std::endl;
  }

  return 0;
}

