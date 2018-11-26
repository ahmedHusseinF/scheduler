#include "../includes/scheduler.hpp"

std::vector<Process> scheduler::getProcessesFromFile(std::string filename) {
  std::fstream file;
  file.open(filename);

  int size;
  file >> size;
  std::vector<Process> ps;
  for (int i = 0; i < size; i++) {
    struct Process p;
    file >> p.pid >> p.arrival_time >> p.working_time >> p.priority;
    p.remaining_time = p.working_time;
    p.done = false;
    ps.push_back(p);
  }
  return ps;
}

void scheduler::saveProcessesStats(std::string filename,
                                   std::vector<Process>& ps) {
  std::ofstream file;
  file.open(filename);

  file << ps.size() << std::endl;

  float sumTA = 0;
  float sumWTa = 0;

  for (int i = 0; i < ps.size(); i++) {
    float ta = max(ps[i].finish_time) - ps[i].arrival_time;
    float wta = ta / ps[i].working_time;

    file << std::fixed << std::setprecision(1) << ps[i].pid << " "
         << min(ps[i].start_time) - ps[i].arrival_time << " " << ta << " "
         << wta << std::endl;

    sumTA += ta;
    sumWTa += wta;
  }

  file << std::fixed << std::setprecision(1) << sumTA << std::endl
       << sumWTa << std::endl;

  file.close();
}

void scheduler::run(std::vector<Process>& ps, struct scheduler::InputData in) {
  switch (in.Algo) {
    case scheduler::FCFS:
      scheduler::FCFSAlgo(ps, in);
      break;
    case scheduler::SRTN:
      scheduler::SRTNAlgo(ps, in);
      break;
    case scheduler::RR:
      scheduler::RRAlgo(ps, in);
      break;
    case scheduler::HPF:
      scheduler::HPFAlgo(ps, in);
      break;
    default:
      std::cerr << "Something went wrong, how did you get here?" << std::endl;
      exit(-1);
      break;
  }
}

bool arrivalComparator(Process p1, Process p2) {
  // break the tie in arrival by smaller pid
  // the comp. uses the < operator
  if (p1.arrival_time == p2.arrival_time) return p1.pid > p2.pid;
  return (p1.arrival_time < p2.arrival_time);
}

void addStartTime(int pid, std::vector<Process>& ps, float st) {
  for (int i = 0; i < ps.size(); i++) {
    if (ps[i].pid == pid) {
      ps[i].start_time.push_back(st);
    }
  }
}

void addFinishTime(int pid, std::vector<Process>& ps, float ft) {
  for (int i = 0; i < ps.size(); i++) {
    if (ps[i].pid == pid) {
      ps[i].finish_time.push_back(ft);
    }
  }
}

void scheduler::FCFSAlgo(std::vector<Process>& ps,
                         struct scheduler::InputData in) {
  float t = 0.0f;
  std::string state = "idle";  // can be idle, running, switching
  float start_switch = 0.0f;
  float start_running = 0.0f;
  int runningPID = -1;

  std::vector<Process> ps_copy(ps);

  std::sort(ps_copy.begin(), ps_copy.end(), arrivalComparator);
  // std::cout << "[[DEBUG]]" << ps_copy.front().arrival_time << std::endl;

  while (!ps_copy.empty()) {
    Process lowestArrival = ps_copy.front();

    if (lowestArrival.arrival_time <= t && state == "idle") {
      state = "switching";
      start_switch = t;
    }

    if (state == "switching" && t >= start_switch + in.contextSwitching) {
      state = "running";
      runningPID = lowestArrival.pid;
      start_running = t;
      addStartTime(runningPID, ps, t);
    }

    if (t >= lowestArrival.working_time + start_running && state == "running") {
      state = "idle";
      start_switch = t;
      addFinishTime(runningPID, ps, t);
      runningPID = -1;
      ps_copy.erase(ps_copy.begin());  // delete the front of the processes
    }

    t += 0.1;
  }
}

void scheduler::SRTNAlgo(std::vector<Process>& ps,
                         struct scheduler::InputData in) {
  // TODO:
}

void scheduler::HPFAlgo(std::vector<Process>& ps,
                        struct scheduler::InputData in) {
  // TODO: same as FCFS but put processes that come
  // while running in priority queue

  float t = 0.0f;
  auto ps_copy = std::vector<Process>(ps);
  std::string state = "idle";
  float start_switch = 0.0f;
  float start_running = 0.0f;

  std::sort(ps_copy.begin(), ps_copy.end(), arrivalComparator);

  std::priority_queue<Process> pQ;
  pQ.push(ps_copy.front());  // start with first process

  while (!pQ.empty()) {
    Process currentLowest = pQ.top();
    // std::cout << "[[DEBUG]] " << currentLowest.pid << " " << state <<
    // std::endl;

    if (state == "idle" && t >= currentLowest.arrival_time) {
      state = "switching";
      start_switch = t;
    }

    if (state == "switching" && t >= start_switch + in.contextSwitching) {
      state = "running";
      start_running = t;
      addStartTime(currentLowest.pid, ps, t);
    }

    if (state == "running" && t >= start_running + currentLowest.working_time) {
      state = "idle";
      addFinishTime(currentLowest.pid, ps, t);

      for (auto x : ps_copy) {
        if (x.pid == currentLowest.pid) x.done = true;
      }
      pQ.pop();

      // std::cout << "DONE REMOVING " << currentLowest.pid << " " << pQ.size()
      // << std::endl;

      // std::cout << "[[DEBUG]] b4 while ";

      for (auto x : ps_copy) {
        if (!x.done && x.arrival_time <= t) {
          pQ.push(x);
        }
      }
    }

    t += 0.1;
  }
}

void scheduler::RRAlgo(std::vector<Process>& ps,
                       struct scheduler::InputData in) {
  // TODO:
}
