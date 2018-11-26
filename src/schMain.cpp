#include "../includes/scheduler.hpp"

int main(int argc, char** argv) {
  if (argc < 5) {
    std::cerr << "Missing arguments" << std::endl;
    return EXIT_FAILURE;
  }

  if (atoi(argv[3]) == 2 && argc < 6) {
    std::cerr << "Missing quantum time and you choose RR" << std::endl;
    return EXIT_FAILURE;
  }

  struct scheduler::InputData in;
  in.Algo = atoi(argv[3]);
  in.contextSwitching = atof(argv[4]);
  if (in.Algo == 2) in.quantumTime = atof(argv[6]);

  auto ps = scheduler::getProcessesFromFile(argv[1]);

  scheduler::run(ps, in);
  scheduler::saveProcessesStats(argv[2], ps);

  return EXIT_SUCCESS;
}