#include "../includes/scheduler.hpp"

void scheduler::run(std::vector<Process>& ps, struct scheduler::InputData in) {
  switch (in.Algo) {
    case scheduler::FCFS:
      /* code */
      scheduler::FCFSAlgo(ps, in);
      break;
    case scheduler::SRTN:
      /* code */
      scheduler::SRTNAlgo(ps, in);
      break;
    case scheduler::RR:
      /* code */
      scheduler::RRAlgo(ps, in);
      break;
    case scheduler::HPF:
      /* code */
      scheduler::HPFAlgo(ps, in);
      break;
    default:
      std::cerr << "Something went wrong, how did you get here?" << std::endl;
      exit(-1);
      break;
  }
}

void scheduler::FCFSAlgo(std::vector<Process>& ps,
                         struct scheduler::InputData in) {
  float t = 0.0f;
  std::string state = "idle";  // can be idle, running, switching
  float start_switch = 0.0f;
  Process currentRunning;
  std::deque<Process> ps_copy(ps);

  std::sort(ps_copy.begin(), ps_copy.end());
  while (!ps_copy.empty()) {
    if (ps_copy.front().arrival_time < t && state == "idle") {
      state = "switching";
      start_switch = t;
    }

    if (ps_copy.front().arrival_time < t && state == "switching" &&
        t > start_switch + in.contextSwitching) {
      state = "running";
      currentRunning = ps_copy.pop_front();
    }

    t = t + 0.1;
  }
}