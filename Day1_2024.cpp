#include <iostream>
#include <fstream>
#include <string>
#include <vector>

int main () {
  std::string line;
  std::vector<int> list1;
  std::vector<int> list2;
  std::ifstream input_file ("Input/Day1_2024.txt");

  while (getline(input_file, line)) 
  { 
    size_t pos {line.find(' ')};
    list1.push_back(stoi(line.substr(0, pos)));
    list2.push_back(stoi(line.substr(pos)));
  }
  input_file.close();

  /* -------------------- Day 1: Part 1 -------------------- */
  {
    std::sort(list2.begin(), list2.end());
    std::sort(list1.begin(),list1.end());
    std::vector<int> diffs;
    for (size_t i {0}; i < list1.size(); i++) {
      int diff = list1[i] > list2[i] ? list1[i]-list2[i] : list2[i]-list1[i];
      diffs.push_back(diff);
    }
    auto diff_sum = std::reduce(diffs.begin(), diffs.end());
    std::cout << "Part 1 result: " << diff_sum << std::endl;
  }

  /* -------------------- Day 1: Part 2 -------------------- */
  {
    int similarity_score {0};
    for (auto& num: list1) {
      similarity_score += num * std::count(list2.begin(), list2.end(), num);
    }
    std::cout << "Part 2 result: " << similarity_score << std::endl;
  }
}
