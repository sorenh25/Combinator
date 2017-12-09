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
  //cout << "Find left most" << endl;
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
  //cout << "variables available index: " << index << " number: " << number << endl;
  int count = 0;
  for (unsigned int i = index + 1; i < computationString.length(); i++) {

    if (computationString[i] == ')') {
      return false;
    }

    else if (computationString[i] == '(') {
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
    if (count >= number) {
      return true;
    }
  }
  return false;
}

void Combinator::compute() {
  for (unsigned int i = 0; i < inputStrings.size(); i++) {
    computationString = inputStrings[i];
    computeString();
  }
}

void Combinator::computeString() {
  cout << "Computation on: " << computationString << endl;
  unsigned int index = 0;
  while (findLeftMost(index)) {
    char variable = computationString[index];
    if (variable == 'I') {
      I(index);
      cleanComputationString();
      cout << "=>"<< computationString << endl;
    }
    if (variable == 'K') {
      K(index);
      cleanComputationString();
      cout << "=>"<< computationString << endl;
    }
    if (variable == 'S') {
      S(index);
      cleanComputationString();
      cout << "=>"<< computationString << endl;
    }
  }
  rmFirstParenthesis(0);
  cout << "=>"<< computationString << endl;

}

void Combinator::I(unsigned int index) {
  //cout << "Combinator I at " << index << endl;
  if (computationString[index] != 'I') {
    cerr << "No 'I' to replace " << computationString << endl;
    return;
  }
  computationString.erase(index, 1);
}

void Combinator::K(unsigned int index) {
  unsigned int startIndexOfSecondArgument, endIndexOfSecondArgument;
  startIndexOfSecondArgument = index + 1;
  getArgument(startIndexOfSecondArgument, endIndexOfSecondArgument);
  startIndexOfSecondArgument = endIndexOfSecondArgument + 1;
  getArgument(startIndexOfSecondArgument, endIndexOfSecondArgument);
  cut(startIndexOfSecondArgument, endIndexOfSecondArgument);
  cut(index, index);
}
/*
void Combinator::K(unsigned int index) {
  if (computationString[index] != 'K') {
    cerr << "No 'K' to replace " << computationString << endl;
    return;
  }
  int argumentCount = 0;
  int startIndexOfSecondArgument = 0;
  int endIndexOfSecondArgument = 0;

  for (unsigned int i = index + 1; i < computationString.length(); i++) {
    if (computationString[i] == '(') {
      cout << "Enter and argument ()\n";
      startIndexOfSecondArgument = i;
      int parenthasisBalance = 1;
      for (unsigned int j = i + 1; j < computationString.length(); j++) {
        if (computationString[j] == '(') {
          parenthasisBalance++;
        }
        if (computationString[j] == ')') {
          parenthasisBalance--;
          if (parenthasisBalance == 0) {
            endIndexOfSecondArgument = j;
            argumentCount++;
            i = j;
          }
          if (argumentCount == 2)
            cout << "Cut start: " << startIndexOfSecondArgument << " end " << endIndexOfSecondArgument << endl;
            cut(startIndexOfSecondArgument, endIndexOfSecondArgument);
            cut(index, index);
            return;
          }
          break;
        }
      }

    if (computationString[i] == ')') {
      cout << "!!!Something went wrong we have a lone ')'" << endl;
    }
    argumentCount++;
    if (argumentCount == 2) {
      cut(i,i);
      cut(index, index);
      return;
    }
  }
}
*/

void Combinator::S(unsigned int index) {
  //cout << index << endl;
  unsigned int startOne, endOne, startTwo, endTwo, startThree, endThree;
  startOne = index + 1;
  //cout << "Start One " << startOne << endl;
  getArgument(startOne, endOne);
  startTwo = endOne + 1;
  //cout << "Start two " << startTwo << endl;
  getArgument(startTwo, endTwo);
  startThree = endTwo + 1;
  //cout << "startThree " << startThree << endl;
  getArgument(startThree, endThree);
  string begin, two, three, end;
  begin = computationString.substr(0, startTwo);
  //cout << "Begin " << begin << endl;
  two = computationString.substr(startTwo, endTwo - startTwo + 1);
  //cout << "Two " << two << endl;
  three = computationString.substr(startThree, endThree - startThree + 1);
  //cout << "Three " << three << endl;
  end = computationString.substr(endThree + 1);
  //cout << "End " << end << endl;
  computationString = begin + three + "(" + two + three + ')' + end;
  //cout << "computationString " << computationString << endl;
  cut(index, index);
  //cout << "computationString " << computationString << endl;
}


bool Combinator::rmParenthesis() {
  vector<int> leftParenthasisIndices;
  //vector<int> rightParenthasisIndices;
  //vector<int> normalVariableCount;
  //vector<int> combinatorVaribaleCount;
  int leftParenthasisIndex = 0;
  int rightParenthasisIndex = 0;
  int normalVariableCount = 0;
  int combinatorVaribaleCount = 0;
  int allVariableCount = 0;
  int rightParenthasisCount = 0;
  //int leftParenthasisCount = 0;
  //int rightParenthasisCount = 0;

  for (unsigned int i = 0; i < computationString.length(); i++) {
    if (computationString[i] == '(') {
      leftParenthasisIndices.push_back(i);
      //leftParenthasisIndex = i;
      normalVariableCount = 0;
      combinatorVaribaleCount = 0;

    }

    else if (computationString[i] == ')') {
      leftParenthasisIndex = leftParenthasisIndices.back();
      leftParenthasisIndices.pop_back();
      rightParenthasisIndex = i;
      rightParenthasisCount++;
      if (normalVariableCount == 0 && combinatorVaribaleCount == 0) {
        computationString.erase(rightParenthasisIndex, 1);
        computationString.erase(leftParenthasisIndex, 1);
        return true;
      }
      if (combinatorVaribaleCount == 0 && rightParenthasisCount == 1 && allVariableCount == normalVariableCount) {
        computationString.erase(rightParenthasisIndex, 1);
        computationString.erase(leftParenthasisIndex, 1);
        return true;
      }
      if (normalVariableCount == 0 && combinatorVaribaleCount == 1) {
        computationString.erase(rightParenthasisIndex, 1);
        computationString.erase(leftParenthasisIndex, 1);
        return true;
      }
    }

    else if ((computationString[i] == 'I') || (computationString[i] == 'S') || (computationString[i] == 'K')) {
      combinatorVaribaleCount++;
      allVariableCount++;
    }

    else {
      normalVariableCount++;
      allVariableCount++;
    }

  }
  return false;
}

bool Combinator::rmFirstParenthesis(unsigned int pos) {
 unsigned int start, end;
 start = pos;
 getArgument(start, end);
 if (computationString[start] == '(' && computationString[end] == ')') {
   cut(end, end);
   cut(start, start);
   return true;
 }
 return false;
}

void Combinator::cut(int startIndex, int endIndex) {
  computationString.erase(startIndex, (endIndex - startIndex + 1));
}

void Combinator::getArgument(unsigned int start, unsigned int& end) {
    if (computationString[start] == '(') {
      int parenthasisBalance = 1;
      for (unsigned int j = start + 1; j < computationString.length(); j++) {
        if (computationString[j] == '(') {
          parenthasisBalance++;
        }
        if (computationString[j] == ')') {
          parenthasisBalance--;
        }
        if (parenthasisBalance == 0) {
          end = j;
          return;
        }
      }
    }
    if (computationString[start] == ')') {
      cout << "This is not right. We got an ')'" << endl;
    }
    end = start;
}

void Combinator::cleanComputationString() {
  bool changes = true;
  while (changes) {
    if (rmParenthesis()) {
      continue;
    }
    if (rmFirstParenthesis(1)) {
      continue;
    }
    changes = false;
  }
}

/*
void Combinator::cleanComputationString(unsigned int index) {
  int normalVariableCount = 0;
  int combinatorVaribaleCount = 0;
  int count = 0;
  //unsigned int beginParenthesisCount = 1;
  //unsigned int endParenthesesCount = 0;
  unsigned int beginParenthesis = index;
  unsigned int endParentheses = 0;
  for (unsigned int i = index + 1; i < computationString.length(); i++) {

    if (computationString[i] == '(' {
      cleanComputationString(i);
    }

    else if (computationString[i] == ')') {

      string;
    }
    else if (computationString[i] == 'S' | computationString[i] == 'K' | computationString == 'I'){
      combinatorVaribaleCount++;
    }


  }
}
*/
