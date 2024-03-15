// Solution.cpp
#include "board.h"
#include "trajectory.h"
#include <algorithm>
#include <iostream>
#include <sstream>

Solution::Solution() : stateCount(0), stateCountShow(true) {}

void Solution::addToSolution(const Grid &grid) { boards.push_back(grid); }

void Solution::terminate(const Grid &grid) {
  if (grid.is_full()) {
    bool containsIllegalWord = false;
    for (const std::string &word : illegalWords) {
      if (grid.contains_word(word)) {
        containsIllegalWord = true;
        break;
      }
    }
    if (!containsIllegalWord) {
      addToSolution(grid);
      std::cout << "Valid solution found! Adding solution #" << boards.size()
                << "..." << std::endl;
    }
  }
}

void Solution::state_incr() {
  stateCount++;
  if (stateCountShow) {
    std::cout << "Board state: " << stateCount << "          \r" << std::flush;
  }
}

Grid Solution::add_word(Grid grid, WordIterate nextWordIterator) {
  state_incr();
  std::string word = nextWordIterator();
  if (word.empty()) {
    terminate(grid);
    return grid;
  }

  GridCoord cell(0, 0);
  for (const GridCoord &c : grid.gridCoords_get()) {
    if (!grid.cell_isEmpty(c)) {
      continue;
    }

    Trajectory trajectory(grid.gridSize);
    std::vector<Path> trajectories = trajectory.paths_find(c, word.length());

    for (const Path &path : trajectories) {
      Grid newGrid = grid.copy();
      if (newGrid.word_canInsert(word, path)) {
        newGrid.word_insert(word, path);
        WordIterate newWordIterator = nextWordIterator.copy();
        Grid nextGrid = add_word(newGrid, newWordIterator);
        terminate(nextGrid);
      }
    }
  }

  terminate(grid);
  return grid;
}

std::vector<Grid> Solution::removeSolution(const std::vector<int> &indices) {
  std::vector<Grid> result;
  for (size_t i = 0; i < boards.size(); i++) {
    if (std::find(indices.begin(), indices.end(), i) == indices.end()) {
      result.push_back(boards[i]);
    }
  }
  return result;
}

std::vector<Grid>
Solution::pruneFromSolution(const std::vector<std::string> &illegalWords) {
  std::vector<Grid> illegalBoards;
  std::vector<int> illegalIndices;

  for (const std::string &word : illegalWords) {
    int boardIndex = 0;
    for (const Grid &grid : boards) {
      if (grid.contains_word(word)) {
        illegalIndices.push_back(boardIndex);
        illegalBoards.push_back(grid);
      }
      boardIndex++;
    }
  }

  if (!illegalIndices.empty()) {
    boards = removeSolution(illegalIndices);
  }

  return illegalBoards;
}
