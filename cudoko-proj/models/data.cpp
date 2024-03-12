#include <iostream>
#include <string>
#include <map>
#include <stdexcept>

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
    int x = 0;
    int y = 0;

    GridCoord operator+(const GridCoord& coord) {
        return GridCoord{this->x + coord.x, this->y + coord.y};
    }

    std::string to_string() {
        return "(" + std::to_string(this->x) + ", " + std::to_string(this->y) + ")";
    }

    std::pair<int, int> to_tuple() {
        return std::make_pair(this->x, this->y);
    }
};

// Just another name for a GridCoord
using Dimensions = GridCoord;

// Equivalent to Python's Namespace
class Space {
    std::map<std::string, int> attributes;

public:
    bool has(const std::string& attrib) {
        return attributes.find(attrib) != attributes.end();
    }

    bool rm(const std::string& attrib) {
        if (!has(attrib)) {
            return false;
        }
        attributes.erase(attrib);
        return true;
    }
};

// Equivalent to Python's custom exception class
class BreakOut : public std::exception {
    const char* what() const throw() {
        return "BreakOut exception occurred";
    }
};

