// Solution.h
#ifndef SOLUTION_H
#define SOLUTION_H

#include "grid.h"
#include "wordIterate.h"
#include <string>
#include <unordered_map>
#include <vector>

class Solution {
public:
  Solution();

  void addToSolution(const Grid &grid);
  void terminate(const Grid &grid);
  void state_incr();
  Grid add_word(Grid grid, WordIterate nextWordIterator);
  std::vector<Grid> removeSolution(const std::vector<int> &indices);
  std::vector<Grid>
  pruneFromSolution(const std::vector<std::string> &illegalWords);

  std::vector<Grid> boards;
  std::vector<std::string> illegalWords;
  std::vector<std::string> legalWords;
  std::unordered_map<std::string, Grid> memo;
  int stateCount;
  bool stateCountShow;
};

#endif // SOLUTION_H
