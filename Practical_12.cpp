#include <iostream>
#include <vector>
#include <climits>

using namespace std;

struct Block {
  int size;
  bool isFree;
};

struct Process {
  int processId;
  int size;
};

void firstFit(vector<Block>& blocks, vector<Process>& processes) {
  for (Process& process : processes) {
    bool allocated = false;
    for (int i = 0; i < blocks.size(); i++) {
      if (blocks[i].isFree && blocks[i].size >= process.size) {
        blocks[i].isFree = false;
        process.processId = i;
        allocated = true;
        break;
      }
    }

    if (!allocated) {
      cout << "Process " << process.processId << " cannot be allocated using first-fit" << endl;
    }
  }
}

void bestFit(vector<Block>& blocks, vector<Process>& processes) {
  for (Process& process : processes) {
    int bestFitIndex = -1;
    int bestFitSize = INT_MAX;

    for (int i = 0; i < blocks.size(); i++) {
      if (blocks[i].isFree && blocks[i].size >= process.size) {
        if (blocks[i].size < bestFitSize) {
          bestFitIndex = i;
          bestFitSize = blocks[i].size;
        }
      }
    }

    if (bestFitIndex != -1) {
      blocks[bestFitIndex].isFree = false;
      process.processId = bestFitIndex;
    } else {
      cout << "Process " << process.processId << " cannot be allocated using best-fit" << endl;
    }
  }
}

void worstFit(vector<Block>& blocks, vector<Process>& processes) {
  for (Process& process : processes) {
    int worstFitIndex = -1;
    int worstFitSize = 0;

    for (int i = 0; i < blocks.size(); i++) {
      if (blocks[i].isFree && blocks[i].size >= process.size) {
        if (blocks[i].size > worstFitSize) {
          worstFitIndex = i;
          worstFitSize = blocks[i].size;
        }
      }
    }

    if (worstFitIndex != -1) {
      blocks[worstFitIndex].isFree = false;
      process.processId = worstFitIndex;
    } else {
      cout << "Process " << process.processId << " cannot be allocated using worst-fit" << endl;
    }
  }
}

int main() {
  int numberOfBlocks;
  cout << "Enter the number of memory blocks: ";
  cin >> numberOfBlocks;

  vector<Block> blocks(numberOfBlocks);
  for (int i = 0; i < numberOfBlocks; i++) {
    cout << "Enter block " << i + 1 << " size: ";
    cin >> blocks[i].size;
    blocks[i].isFree = true;
  }

  int numberOfProcesses;
  cout << "\nEnter the number of processes: ";
  cin >> numberOfProcesses;

  vector<Process> processes(numberOfProcesses);
  for (int i = 0; i < numberOfProcesses; i++) {
    cout << "Enter process " << i + 1 << " size: ";
    cin >> processes[i].size;
  }

  cout << "\nFirst-Fit Allocation:" << endl;
  firstFit(blocks, processes);

  cout << "\nBest-Fit Allocation:" << endl;
  bestFit(blocks, processes);

  cout << "\nWorst-Fit Allocation:" << endl;
  worstFit(blocks, processes);
}
