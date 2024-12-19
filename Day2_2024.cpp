#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>

enum class increment {
  ASCENDING, 
  DESCENDING
};

bool is_report_safe(const std::vector<int>& report) {
  bool safe_report {false};
  increment direction = report[1] > report[0] ? increment::ASCENDING : increment::DESCENDING;
  for (size_t i {1}; i < report.size(); i++) {
    int diff {abs(report[i] - report[i-1])};
    if (diff >= 1 && diff <= 3) {
      switch (direction) {
        case increment::ASCENDING:
          if (report[i] > report[i-1]) {safe_report = true; continue;}
          break;
        case increment::DESCENDING:
          if (report[i] < report[i-1]) {safe_report = true; continue;}
          break;
      }
    }
    safe_report = false;
    break;
  }
  return safe_report;
}

int main () {
  std::string line;
  std::vector<std::vector<int>> reports;
  std::ifstream input_file ("Input/Day2_2024.txt");

  while (getline(input_file, line)) 
  { 
    std::stringstream ssline {std::move(line)};
    std::string num;
    std::vector<int> levels;
    while (getline(ssline, num, ' ')) {
      levels.push_back(stoi(num));
    }
    reports.push_back(levels);
  }
  input_file.close();
  
  /* -------------------- Day 1: Part 1 -------------------- */
  { 
    int safe_reports {0};
    for (const auto& report: reports) {
      if (is_report_safe(report)) {
        ++safe_reports;
      }
    }
    std::cout << "Part 1 result: " << safe_reports << std::endl;
  }

  /* -------------------- Day 1: Part 2 -------------------- */
  {
    int safe_reports {0};
    for (const auto& report: reports) {
      if (is_report_safe(report)) {
          ++safe_reports;
          continue;
      } 
      for (size_t i {0}; i < report.size(); i++) {
        auto temp {report};
        temp.erase(temp.begin() + i);
        if (is_report_safe(temp)) {
          ++safe_reports;   
          break;
        }
      }
    }
    std::cout << "Part 2 result: " << safe_reports << std::endl;
  }
}
