#include "generator.hpp"

Generator::Generator(std::string filename) {
  int var_count = 0;
  inputFile.open(filename);

  inputFile >> num_processes;
  inputFile >> arrival_mu >> arrival_sigma;
  inputFile >> working_mu >> working_sigma;
  inputFile >> priority_lambda;

  inputFile.close();
}

std::vector<Process> Generator::getProcesses() {
  //
  gsl_rng *r = gsl_rng_alloc(gsl_rng_default);

  std::vector<Process> processes(num_processes);

  for (int i = 0; i < num_processes; i++) {
    struct Process ps;

    ps.process_pid = i;
    ps.arrival_time = gsl_ran_lognormal(r, arrival_mu, arrival_sigma);
    ps.working_time = gsl_ran_lognormal(r, working_mu, working_sigma);
    ps.priority = gsl_ran_poisson(r, priority_lambda);

    processes[i] = ps;
  }
}