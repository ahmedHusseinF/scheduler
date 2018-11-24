#include "../includes/generator.hpp"

int main(int argc, char const *argv[]) {
  if (argc < 3) {
    std::cerr << "missing arguments" << std::endl;
    return EXIT_FAILURE;
  }

  struct generator::InputData in = generator::readFile(argv[1]);

  std::vector<Process> processes = generator::generateProcesses(in);

  generator::saveFile(argv[2], processes);

  return EXIT_SUCCESS;
}
