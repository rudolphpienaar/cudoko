// Solution.cpp
#include "board.h"
#include "trajectory.h"
#include <iostream>
#include <sstream>
#include <algorithm>

Solution::Solution()
    : usememoization(false), stateCount(0), stateCountShow(true) {}

void Solution::addToSolution(const Grid& grid) {
    boards.push_back(grid);
}

void Solution::terminate(const Grid& grid) {
    if (grid.is_full()) {
        addToSolution(grid);
    }
}

void Solution::state_incr() {
    ++stateCount;
    if (stateCountShow) {
        std::cout << "Board state: " << stateCount << "\r" << std::flush;
    }
}

Grid Solution::add_word(Grid grid, WordIterate nextWordIterator) {
    state_incr();

    if (usememoization) {
        std::string state = grid.strRep() + "," + nextWordIterator.str();
        if (memo.find(state) != memo.end()) {
            std::cout << "found state!" << std::endl;
            return memo[state];
        }
    }

    std::string word = nextWordIterator();
    if (word.empty()) {
        terminate(grid);
        return grid;
    }

    /* for (const auto& cell : grid.cellIterate()) { */
    /*     Trajectory trajectory(grid.gridSize()); */
    /*     std::vector<Path> trajectories = trajectory.paths_find(cell, word.length()); */
    /*     for (const auto& path : trajectories) { */
    /*         Grid newGrid = grid.copy(); */
    /*         if (newGrid.word_canInsert(word, path)) { */
    /*             newGrid.word_insert(word, path); */
    /*             WordIterate newWordIterator = nextWordIterator.copy(); */
    /*             Grid nextGrid = add_word(newGrid, newWordIterator); */
    /*             if (usememoization) { */
    /*                 std::string nextState = nextGrid.strRep() + "," + newWordIterator.str(); */
    /*                 memo[nextState] = nextGrid; */
    /*             } */
    /*         } */
    /*     } */
    /* } */

    terminate(grid);
    return grid;
}

std::vector<Grid> Solution::removeSolution(const std::vector<int>& indices) {
    std::vector<Grid> result;
    for (std::size_t i = 0; i < boards.size(); ++i) {
        if (std::find(indices.begin(), indices.end(), static_cast<int>(i)) == indices.end()) {
            result.push_back(boards[i]);
        }
    }
    return result;
}

std::vector<Grid> Solution::pruneFromSolution(const std::vector<std::string>& illegalWords) {
    std::vector<Grid> illegalBoards;
    std::vector<int> illegalIndices;

    for (const auto& word : illegalWords) {
        int boardIndex = 0;
        for (const auto& grid : boards) {
            if (grid.contains_word(word)) {
                if (std::find(illegalIndices.begin(), illegalIndices.end(), boardIndex) == illegalIndices.end()) {
                    illegalIndices.push_back(boardIndex);
                    illegalBoards.push_back(grid);
                }
            }
            ++boardIndex;
        }
    }

    if (!illegalIndices.empty()) {
        boards = removeSolution(illegalIndices);
    }

    return illegalBoards;
}

