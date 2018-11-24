#include <bits/stdc++.h>
#include "common.hpp"

namespace scheduler {
struct InputData {
  float quantumTime;
  float contextSwitching;
  int Algo;
};
void run(std::vector<Process> &ps, struct scheduler::InputData in);
void FCFSAlgo(std::vector<Process> &, struct scheduler::InputData in);
void HPFAlgo(std::vector<Process> &, struct scheduler::InputData in);
void RRAlgo(std::vector<Process> &, struct scheduler::InputData in);
void SRTNAlgo(std::vector<Process> &, struct scheduler::InputData in);
enum { HPF, FCFS, RR, SRTN };
}  // namespace scheduler
