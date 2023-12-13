#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

int main() {
  cout << "### Memory Information ###\n\n";

  // Get total memory
  long totalMem = 0;
  ifstream fTotalMem("/proc/meminfo");
  if (fTotalMem.is_open()) {
    string line;
    while (getline(fTotalMem, line)) {
      if (line.find("MemTotal:") != string::npos) {
        istringstream iss(line);
        string label, memoryValue;
        iss >> label >> memoryValue;
        totalMem = stol(memoryValue);
        break;
      }
    }
    fTotalMem.close();
  } else {
    cerr << "Error opening /proc/meminfo" << endl;
  }

  // Get free memory
  long freeMem = 0;
  ifstream fFreeMem("/proc/meminfo");
  if (fFreeMem.is_open()) {
    string line;
    while (getline(fFreeMem, line)) {
      if (line.find("MemFree:") != string::npos) {
        istringstream iss(line);
        string label, memoryValue;
        iss >> label >> memoryValue;
        freeMem = stol(memoryValue);
        break;
      }
    }
    fFreeMem.close();
  } else {
    cerr << "Error opening /proc/meminfo" << endl;
  }

  // Calculate used memory
  long usedMem = totalMem - freeMem;

  cout << "Total Memory: " << totalMem / 1024 << " MB" << endl;
  cout << "Free Memory: " << freeMem / 1024 << " MB" << endl;
  cout << "Used Memory: " << usedMem / 1024 << " MB" << endl;

  return 0;
}
