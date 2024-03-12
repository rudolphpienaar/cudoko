// Source file (Grid.cpp)

#include "data.h"

bool Space::has(const std::string& attrib) {
    return attributes.find(attrib) != attributes.end();
}

bool Space::rm(const std::string& attrib) {
    if (!has(attrib)) {
        return false;
    }
    attributes.erase(attrib);
    return true;
}

GridCoord::GridCoord(int x, int y): x(x), y(y) {}

GridCoord GridCoord::operator+(const GridCoord& coord) {
    return GridCoord{x + coord.x, y + coord.y};
}

std::string GridCoord::to_string() const {
    return "(" + std::to_string(x) + ", " + std::to_string(y) + ")";
}

std::pair<int, int> GridCoord::to_tuple() const {
    return std::make_pair(x, y);
}

Dimensions::Dimensions(): x(0), y(0) {}
Dimensions::Dimensions(int x, int y): x(x), y(y) {}


std::vector<GridDir> GridDirValues() {
    return {
        GridDir::N,
        GridDir::S,
        GridDir::E,
        GridDir::W,
        GridDir::NE,
        GridDir::NW,
        GridDir::SE,
        GridDir::SW,

    };
}

