// Source file (Grid.cpp)

#include "data.h"
#include <iostream>
#include <sstream>
#include <string>

Space::Space(){};

bool Space::has(const std::string &attrib) {
  return attributes.find(attrib) != attributes.end();
}

bool Space::rm(const std::string &attrib) {
  if (!has(attrib)) {
    return false;
  }
  attributes.erase(attrib);
  return true;
}

std::string Space::str() {
  std::ostringstream oss;
  oss << "gridSize: " << gridSize << '\n';
  oss << "rows: " << rows << '\n';
  oss << "cols: " << cols << '\n';
  oss << "wordsIncludeFile: " << wordsIncludeFile << '\n';
  oss << "wordsExcludeFile: " << wordsExcludeFile << '\n';
  return oss.str();
}

GridCoord::GridCoord(int x, int y) : x(x), y(y) {}

GridCoord GridCoord::operator+(const GridCoord &coord) {
  return GridCoord{x + coord.x, y + coord.y};
}

std::string GridCoord::to_string() const {
  return "(" + std::to_string(x) + ", " + std::to_string(y) + ")";
}

std::pair<int, int> GridCoord::to_tuple() const { return std::make_pair(x, y); }

Dimensions::Dimensions() : x(0), y(0) {}
Dimensions::Dimensions(int x, int y) : x(x), y(y) {}

std::vector<GridDir> GridDirValues() {
  return {
      GridDir::N,  GridDir::S,  GridDir::E,  GridDir::W,
      GridDir::NE, GridDir::NW, GridDir::SE, GridDir::SW,
  };
}

std::string gridDirName(GridDir gridDir) {
  switch (gridDir) {
  case GridDir::N:
    return "North";
  case GridDir::S:
    return "South";
  case GridDir::E:
    return "East";
  case GridDir::W:
    return "West";
  case GridDir::NE:
    return "North East";
  case GridDir::NW:
    return "North West";
  case GridDir::SE:
    return "South East";
  case GridDir::SW:
    return "South West";
  }
}
