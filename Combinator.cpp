#include "Combinator.hpp"

using namespace std;

Combinator::Combinator(string inputFile) {
  inputFileName = inputFile;
}

Combinator::~Combinator() {

}

void Combinator::readInputFile() {
  ifstream CombinatorFile;
  CombinatorFile.open(inputFileName.c_str());
  if (!CombinatorFile.is_open()) {
    cerr << " Input File could not be opened" << endl;
    return;
  }

  string line;
  while(!CombinatorFile.eof()) {
    getline(CombinatorFile, line);
    if (line[line.length() - 1] == '\r') {
      line.pop_back();
    }
    if (line.empty()) {
      break;
    }
    if (line[0] == '-') {
      break;
    }
    line = '(' + line + ')';
    inputStrings.push_back(line);
  }
  while(!CombinatorFile.eof()) {
    getline(CombinatorFile, line);
    if (line[line.length() - 1] == '\r') {
      line.pop_back();
    }
    if (line.empty()) {
      break;
    }
    outputStrings.push_back(line);
  }
}

void Combinator::printInput() {
  for (unsigned int i = 0; i < inputStrings.size(); i++) {
    cout << inputStrings[i] << endl;
    cout << outputStrings[i] << endl;
  }
}

bool Combinator::findLeftMost(unsigned int& index) {
  for (unsigned int i = 0; i < computationString.size(); i++) {
    if (computationString[i] == 'I') {
      if (!variablesAvailable(i, 0)) {
        continue;
      }
      index = i;
      return true;
    }
    if (computationString[i] == 'K') {
      if (!variablesAvailable(i, 2)) {
        continue;
      }
      index = i;
      return true;
    }
    if (computationString[i] == 'S') {
      if (!variablesAvailable(i, 3)) {
        continue;
      }
      index = i;
      return true;
    }
  }
  return false;
}

bool Combinator::variablesAvailable(unsigned int index, int number) {
  int count = 0;
  for (unsigned int i = index + 1; i < computationString.length(); i++) {

    if (computationString[i] == ')') {
      return false;
    }

    if (computationString[i] == '(') {
      int leftParenthasisCount = 1;
      int rightParenthasisCount = 0;
      while (!(leftParenthasisCount == rightParenthasisCount)) {
        i++;
        if (computationString[i] == '(') {
          leftParenthasisCount++;
        }
        if (computationString[i] == ')') {
          rightParenthasisCount++;
        }
      }
      count++;
    }
    else {
      count++;
    }
    if (count == number) {
      return true;
    }
  }
  return false;
}

void Combinator::compute() {
  unsigned int index = 0;
  while (findLeftMost(index)) {
    char variable = computationString[index];
    if (variable == 'I') {
      I(index);
    }
    if (variable == 'K') {
      K(index);
    }
    if (variable == 'S') {
      S(index);
    }
  }
}

void Combinator::I(unsigned int index) {
  if (computationString[index] != 'I') {
    cerr << "No 'I' to replace " << computationString << endl;
    return;
  }
  string beforeI = computationString.substr(0,index);
  string afterI = computationString.substr(index + 1, computationString.length() - (index + 1));
  computationString = beforeI + afterI;
}

void Combinator::K(unsigned int index) {

}

void Combinator::S(unsigned int index) {

}

void Combinator::cleanComputationString(unsigned int index) {
  int count = 0;
  for (unsigned int i = index + 1; i < computationString.length(); i++) {

    if (computationString[i] == '(' {
      cleanComputationString(i);
    }

    if (computationString[i] == ')') {
      string
    }

  }
}
