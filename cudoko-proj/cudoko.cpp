// This module provides some very simple shell-based job running methods.
#include <algorithm>
#include <cstdio>
#include <fstream>
#include <iostream>
#include <map>
#include <stdexcept>
#include <stdio.h>
#include <string>
#include <vector>
// Include other necessary headers and libraries
#include "argh.h"
#include "cudoko.h"
#include "lib/board.h"
#include "lib/grid.h"
#include "models/data.h"

// Define the version and other constants
const std::string VERSION = "version_number";

// Function declarations
Space parser_setup(int argc, char const *argv[], int &retval) {
  Space options = Space();
  std::string gridSize = "4x4", wordsIncludeFile = "", wordsExcludeFile = "";

  bool help;
  Argh argh;
  argh.addFlag(help, "--help");
  argh.addOption<std::string>(options.gridSize, "", "--gridSize",
                              "the size of the grid to solve");
  argh.addOption<std::string>(options.wordsIncludeFile, "",
                              "--wordsIncludeFile",
                              "a file containing MUST have words");
  argh.addOption<std::string>(options.wordsExcludeFile, "",
                              "--wordsExcludeFile",
                              "a file containing MUST NOT have words");
  argh.parse(argc, argv);

  options.gridSize = "4x4";
  options.wordsIncludeFile = "samples/4x4/wordsInclude.txt";
  options.wordsExcludeFile = "samples/4x4/wordsExclude.txt";

  if (help) {
    std::cout << argh.getUsage() << std::endl;
    retval = 0;
  }

  // Parse gridSize into row and col
  if (!options.gridSize.empty()) {
    std::stringstream ss(options.gridSize);
    std::string token;
    std::getline(ss, token, 'x');
    options.rows = std::stoi(token);
    std::getline(ss, token, 'x');
    options.cols = std::stoi(token);
    retval = 1;
  }

  // std::cout << options.str();
  return options;
}

// Define other functions such as parser_interpret, parser_JSONinterpret, etc.

bool namespace_isempty(std::map<std::string, std::string> &namespace_map) {
  for (const auto &pair : namespace_map) {
    if (pair.second != "")
      return false;
  }
  return true;
}

std::vector<std::string> wordFile_read(std::string filename, bool shouldsort) {
  std::vector<std::string> lines;
  std::string line;
  std::ifstream file(filename);
  if (file.is_open()) {
    while (getline(file, line)) {
      if (!line.empty()) {
        lines.push_back(line);
      }
    }
    file.close();
    if (shouldsort) {
      std::sort(lines.begin(), lines.end(),
                [](const std::string &a, const std::string &b) {
                  return a.length() > b.length();
                });
    }
  } else {
    std::cerr << "File not found: " << filename << std::endl;
  }
  return lines;
}

// Include other necessary headers

// Assuming Dimensions, Space, Solution, WordIterate, and Grid are already
// defined in C++

Cudoko::Cudoko(const Space &optionsMap) {
  options = optionsMap;
  std::cout << options.str();
  gridSize = Dimensions(options.cols, options.rows);
  words = wordFile_read(options.wordsIncludeFile);
  solution = Solution();
  solution.legalWords = words;
  if (options.wordsExcludeFile.length()) {
    wordsExclude = wordFile_read(options.wordsExcludeFile);
    solution.illegalWords = wordsExclude;
  }
}

void Cudoko::boards_headerPrint(int numberOfBoards,
                                const std::string qualifier) {
  std::cout << numberOfBoards << " " << qualifier;
  if (numberOfBoards != 1) {
    std::cout << "s";
  }
  std::cout << std::endl;
}

void Cudoko::boards_print(const std::vector<Grid> &boards) {
  for (const Grid &board : boards) {
    std::cout << "Board:" << std::endl << board.cstr() << std::endl;
    std::cout << "Board:" << std::endl;
  }
}

void Cudoko::solve_allBoards() {
  std::cout << "Solving wudoko!" << std::endl;
  std::cout << "Legal words: ";
  for (const std::string &word : words) {
    std::cout << word << " ";
  }
  std::cout << std::endl;

  std::cout << "Illegal words: ";
  for (const std::string &word : wordsExclude) {
    std::cout << word << " ";
  }
  std::cout << std::endl;

  Grid initialGrid(gridSize, " ");
  WordIterate wordIterator(words);
  solution.add_word(initialGrid, wordIterator);

  std::cout << "\nAll boards:" << std::endl;
  boards_headerPrint(solution.boards.size());
}

void Cudoko::prune_illegalBoards() {
  if (!wordsExclude.empty()) {
    std::cout << "Removing all grids with illegal words: ";
    for (const std::string &word : wordsExclude) {
      std::cout << word << " ";
    }
    std::cout << std::endl;

    std::vector<Grid> illegalSolutions =
        solution.pruneFromSolution(wordsExclude);
    if (!illegalSolutions.empty()) {
      std::cout << "Disallowed Solutions:" << std::endl;
      boards_headerPrint(illegalSolutions.size(), "illegal");
      // boards_print(illegalSolutions);
    }

    std::cout << "Legal Solutions:" << std::endl;
  }
}

void Cudoko::solve() {
  solve_allBoards();
  // prune_illegalBoards();
  boards_print(solution.boards);
  std::cout << "done!" << std::endl;
}
