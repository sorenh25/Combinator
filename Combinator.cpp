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

void printInput() {
  for (unsigned int i = 0; i < inputStrings.size(); i++) {
    cout << inputStrings[i] << endl;
    cout << outputStrings[i] << endl;
  }
}
