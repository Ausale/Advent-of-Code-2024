#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <exception>

enum Direction {
  DiagonalLeft = -1,
  Vertical = 0,
  DiagonalRight = 1
};

struct GridPosition { 
    size_t row {0};
    size_t column {0};
};

void lookForXmas(const std::vector<std::string>& grid, GridPosition pos, Direction dir, int& count) {
  std::string word;
  for (int i = {0}; i < 4; ++i) {
      word += grid[pos.row + i][pos.column + (i * dir)];
  }
  if (word == "XMAS" || word == "SAMX") {
      ++count;
  }
}

void lookForXmasCross(const std::vector<std::string>& grid, GridPosition pos, Direction dir, std::vector<int>& rightDiagHits, int& count) {
  std::string word;
  for (int i = {0}; i < 3; ++i) {
      word += grid[pos.row + i][pos.column + (i * dir)];
  }
  if (word == "MAS" || word == "SAM") {
    switch (dir) {
      case Direction::DiagonalRight:
        rightDiagHits.push_back(pos.column);
        break;
      case Direction::DiagonalLeft:
        if (std::find(rightDiagHits.begin(), rightDiagHits.end(), pos.column - 2) != rightDiagHits.end()) {
          ++count;
        } break;
      case Direction::Vertical:
        return throw std::runtime_error("Direction::Vertical not supported in lookForXmasCross()");
    }
  }
}

int main() {
  std::string line;
  std::vector<std::string> grid;
  std::ifstream inputFile("Input/Day4_2024.txt");

  while (getline(inputFile, line)) {
      grid.push_back(line);
  }
  inputFile.close();

  /* -------------------- Day 4: Part 1 -------------------- */
  { 
    int count {0};

    // Horizontal
    for (const auto& line : grid) {
        for (std::string::size_type i = 0; i < line.size() - 3; ++i) {
            if (line.substr(i, 4) == "XMAS" || line.substr(i, 4) == "SAMX") {
                ++count;
            }
        }
    }
    // Vertical, Diagonal Right, Diagonal Left
    for (size_t row = 0; row < grid.size() - 3; ++row) {
        for (size_t column = 0; column < grid[0].size(); ++column) {
            lookForXmas(grid, {row, column}, Direction::Vertical, count);
            if (column <= grid[0].size() - 4) {
              lookForXmas(grid, {row, column}, Direction::DiagonalRight, count);
            }
            if (column >= 3) {
              lookForXmas(grid, {row, column}, Direction::DiagonalLeft, count);
            }
        }
    }
    std::cout << "Part 1 result: " << count << std::endl;
  }

  /* -------------------- Day 4: Part 2 -------------------- */
  {
    int count {0};

    for (size_t row = 0; row < grid.size() - 2; ++row) {
        std::vector<int> rightDiagHits;
        for (size_t column = 0; column < grid[0].size(); ++column) {
            if (column <= grid[0].size() - 2) {
              lookForXmasCross(grid, {row, column}, Direction::DiagonalRight, rightDiagHits, count);
            }
            if (column >= 2) {
              lookForXmasCross(grid, {row, column}, Direction::DiagonalLeft, rightDiagHits, count);
            }
        }
    }
    std::cout << "Part 2 result: " << count << std::endl;
  }
}
