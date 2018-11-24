
struct Process {
  int pid;
  float arrival_time, start_time;
  float working_time;
  float finish_time;
  int priority;
  bool operator<(const Process& rhs) const { arrival_time < rhs.arrival_time; }
};
