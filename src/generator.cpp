#include "../includes/generator.hpp"

struct generator::InputData generator::readFile(std::string filename) {
  std::ifstream inputFile;

  inputFile.open(filename);

  struct generator::InputData in;
  inputFile >> in.num_processes;
  inputFile >> in.arrival_mu >> in.arrival_sigma;
  inputFile >> in.working_mu >> in.working_sigma;
  inputFile >> in.priority_lambda;

  inputFile.close();

  return in;
}

void generator::saveFile(std::string filename, std::vector<Process> processes) {
  std::ofstream outputFile;

  outputFile.open(filename);

  outputFile << processes.size() << std::endl;

  for (int i = 0; i < processes.size(); i++) {
    outputFile << std::fixed << std::setprecision(1) << processes[i].pid << " "
               << processes[i].arrival_time << " " << processes[i].working_time
               << " " << processes[i].priority << std::endl;
  }
}

std::vector<Process> generator::generateProcesses(
    struct generator::InputData in) {
  std::vector<Process> processes;

  std::default_random_engine generator;

  std::normal_distribution<float> arrivalDistribution(in.arrival_mu,
                                                      in.arrival_sigma);
  std::normal_distribution<float> workingDistribution(in.working_mu,
                                                      in.working_sigma);
  std::poisson_distribution<int> priorityDistribution(in.priority_lambda);

  for (int i = 0; i < in.num_processes; i++) {
    struct Process ps;

    ps.pid = i + 1;

    do {
      ps.arrival_time = arrivalDistribution(generator);
    } while (ps.arrival_time <= 0);

    do {
      ps.working_time = workingDistribution(generator);
    } while (ps.working_time <= 0);

    ps.priority = priorityDistribution(generator);

    processes.push_back(ps);  // always push back
  }

  return processes;
}