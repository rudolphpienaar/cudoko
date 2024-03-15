// Header file (Grid.h)
#ifndef DATA_H
#define DATA_H

#include <exception>
#include <map>
#include <string>
#include <vector>

enum class GridDir {
  N = 1,
  S,
  E,
  W,
  NE,
  NW,
  SE,
  SW

};

std::vector<GridDir> GridDirValues();
std::string gridDirName(GridDir gridDir);

enum class Orient { row = 1, col };

class GridCoord {
public:
  int x = 0;
  int y = 0;

  GridCoord(int x, int y);
  GridCoord operator+(const GridCoord &coord);
  std::string to_string() const;
  std::pair<int, int> to_tuple() const;
};

class Dimensions {
public:
  int x = 0;
  int y = 0;

  Dimensions();
  Dimensions(int x, int y);
};

class Space {
public:
  Space();
  std::string gridSize = "";
  int rows, cols;
  std::string wordsIncludeFile = "";
  std::string wordsExcludeFile = "";
  bool man = false;
  bool version = false;

  std::map<std::string, int> attributes;
  std::string str();
  bool has(const std::string &attrib);
  bool rm(const std::string &attrib);
};

class BreakOut : public std::exception {
  const char *what() const throw() { return "BreakOut exception occurred"; }
};

#endif
