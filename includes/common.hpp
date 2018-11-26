
struct Process {
  int pid;
  float arrival_time;
  std::vector<float> start_time;
  float working_time, remaining_time;
  std::vector<float> finish_time;
  int priority;
  bool done;
  bool operator<(const Process& rhs) const {
    // if (this->priority == p.priority) return this->pid > p.pid;
    return this->priority < rhs.priority;
  }
  Process() {}
  Process(const Process& copy) {
    for (auto x : copy.start_time) {
      this->start_time.push_back(x);
    }
    for (auto x : copy.finish_time) {
      this->finish_time.push_back(x);
    }
    pid = copy.pid;
    arrival_time = copy.arrival_time;
    working_time = copy.working_time;
    remaining_time = copy.remaining_time;
    priority = copy.priority;
  }
};

template <typename T>
T max(const std::vector<T>& v1) noexcept {
  T maxx = INT32_MIN;

  for (auto x : v1) {
    if (maxx < x) maxx = x;
  }
  return maxx;
}

template <typename T>
T min(const std::vector<T>& v1) noexcept {
  T minn = INT32_MAX;

  for (auto x : v1) {
    if (minn > x) minn = x;
  }
  return minn;
}
