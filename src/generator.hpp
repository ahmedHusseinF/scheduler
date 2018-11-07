#include "process.hpp"
#include <bits/stdc++.h>
#include <gsl/gsl_randist.h>

class Generator {

public:
  Generator(std::string filename);
  ~Generator();

  std::vector<Process> getProcesses();
  void saveFile();

private:
  std::ifstream inputFile;
  std::ofstream outputFile;
  int num_processes;
  float arrival_mu, arrival_sigma;
  float working_mu, working_sigma;
  float priority_lambda;
};