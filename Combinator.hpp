
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
  bool findLeftMost(unsigned int&);
  bool variablesAvailable(unsigned int index, int number);
  void compute();
  void computeString();

  void I(unsigned int);
  void K(unsigned int);
  void S(unsigned int);

  void cleanComputationString();

  bool rmParenthesis();
  bool rmFirstParenthesis(unsigned int);
  void getArgument(unsigned int start, unsigned int& end);
  void cut(int, int);

private:
  std::string inputFileName;
  std::vector<std::string> inputStrings;
  std::vector<std::string> outputStrings;

  std::string computationString;
};
