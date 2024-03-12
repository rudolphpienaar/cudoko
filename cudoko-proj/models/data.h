#ifndef DATA_H
#define DATA_H

#include <iostream>
#include <string>
#include <map>
#include <utility>

// Equivalent to Python's Enum
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

enum class Orient {
    row = 1,
    col
};

// Equivalent to Python's BaseSettings
struct GridCoord {
    int x;
    int y;

    GridCoord(int x = 0, int y = 0);
    GridCoord operator+(const GridCoord& coord);
    std::string to_string();
    std::pair<int, int> to_tuple();
};

// Just another name for a GridCoord
using Dimensions = GridCoord;

// Equivalent to Python's Namespace
class Space {
    public:
    std::map<std::string, int> attributes;
    std::string gridSize;
    std::string wordInclude;
    std::string wordExclude;

    bool has(const std::string& attrib);
    bool rm(const std::string& attrib);
};

// Equivalent to Python's custom exception class
class BreakOut : public std::exception {
public:
    const char* what() const throw();
};

#endif // DATA_H

