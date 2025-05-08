#include <fstream>
#include <iostream>
#include <regex>
#include <string>

int main() {
  const std::string inputFileName{"input.txt"};
  std::ifstream inputFile{inputFileName};
  if (!inputFile) {
    std::cerr << "Failed to open " << inputFileName << std::endl;
    return 1;
  }

  const std::string memoryContent{std::istreambuf_iterator<char>{inputFile},
                                  std::istreambuf_iterator<char>{}};

  const std::regex mulPattern{R"(mul\((\d{1,3}),(\d{1,3})\))"};
  std::smatch matchResults;
  int totalSum{0};

  std::string::const_iterator searchStart{memoryContent.cbegin()};
  const std::string::const_iterator searchEnd{memoryContent.cend()};

  while (std::regex_search(searchStart, searchEnd, matchResults, mulPattern)) {
    const int leftOperand{std::stoi(matchResults[1].str())};
    const int rightOperand{std::stoi(matchResults[2].str())};
    totalSum += leftOperand * rightOperand;

    searchStart = matchResults.suffix().first;
  }

  std::cout << "Total: " << totalSum << std::endl;
}
