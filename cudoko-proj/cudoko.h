// cudoko.h
#ifndef CUDOKO_H
#define CUDOKO_H

#include <map>
#include <string>
#include <vector>

#include "lib/board.h"
#include "models/data.h"
// Include the header for the Argh class
#include "argh.h"

// Assuming Dimensions, Space, Solution, WordIterate, and Grid are already
// defined in their respective headers

Space parser_setup(int argc, char const *argv[], int &retval);

class Cudoko {
public:
  Space options;
  std::string desc;
  Dimensions gridSize;
  std::vector<std::string> words;
  std::vector<std::string> wordsExclude;
  Solution solution;

  Dimensions gridDimensions_set();
  Cudoko(const Space &optionsMap = {});
  void solve();
  void words_populate();
  void boards_headerPrint(int numberOfBoards,
                          const std::string qualifier = "solution");
  void boards_print(const std::vector<Grid> &boards);
  void solve_allBoards();
  void prune_illegalBoards();
};

// Function declarations
bool namespace_isempty(std::map<std::string, std::string> &namespace_map);
std::vector<std::string> wordFile_read(std::string filename,
                                       bool shouldsort = false);

#endif // CUDOKO_H
