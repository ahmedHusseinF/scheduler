#include <bits/stdc++.h>
#include "common.hpp"

namespace generator {
struct InputData {
  int num_processes;
  float arrival_mu, arrival_sigma;
  float working_mu, working_sigma;
  float priority_lambda;
};

struct generator::InputData readFile(std::string);
void saveFile(std::string, std::vector<Process>);
std::vector<Process> generateProcesses(struct generator::InputData in);
}  // namespace generator
