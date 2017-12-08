
#include <string>
#include <vector>
#include <fstream>
#include <iostream>

class Combinator {
public:
  Combinator(std::string);
  ~Combinator();

  void readInputFile();
  void printInput();

private:
  std::string inputFileName;
  std::vector<std::string> inputStrings;
  std::vector<std::string> outputStrings;

  std::string computationString;
};
