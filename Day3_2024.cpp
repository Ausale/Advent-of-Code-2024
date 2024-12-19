#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <regex>

namespace {
  bool g_doMultiply {true};
};

int multiplyValuesFromLine(std::string& line, bool doMultiplyAll = true) {
  int lineResult {0};
  std::regex patterns(R"(mul\(\d+,\d+\)|don't\(\)|do\(\))");
  std::regex nums(R"(\d+)");
  std::regex_token_iterator<std::string::iterator> regend;
  
  std::regex_token_iterator<std::string::iterator> it (line.begin(), line.end(), patterns);
  while (it != regend) {
    std::string patternMatch {*it++};
    if (patternMatch.find("don't()") != std::string::npos) {g_doMultiply = false; continue;}
    if (patternMatch.find("do()") != std::string::npos) {g_doMultiply = true; continue;}
    if (doMultiplyAll || g_doMultiply) {
      std::vector<int> numVec;
      std::regex_token_iterator<std::string::iterator> it2 (patternMatch.begin(), patternMatch.end(), nums);
      while (it2 != regend) {
        std::string numString {*it2++};
        numVec.push_back(stoi(numString));
      }
      lineResult += (numVec[0]*numVec[1]);
    }
  }
  return lineResult;
}

int main () {
  std::string line;
  std::vector<std::string> lines;
  std::ifstream inputFile ("Input/Day3_2024.txt");

  while (getline(inputFile, line)) 
  { 
    lines.push_back(line);
  }
  inputFile.close();

  
  /* -------------------- Day 1: Part 1 -------------------- */
  { 
    int result {0};
    for (auto& line: lines) {
      result += multiplyValuesFromLine(line, true);
    }
    std::cout << "Part 1 result: " << result << std::endl;
  }
  g_doMultiply = true; // reset global variable

  /* -------------------- Day 1: Part 2 -------------------- */
  {
    int result {0};
    for (auto& line: lines) {
      result += multiplyValuesFromLine(line, false);
    }
    std::cout << "Part 2 result: " << result << std::endl;
  }
  g_doMultiply = true; // reset global variable
}
