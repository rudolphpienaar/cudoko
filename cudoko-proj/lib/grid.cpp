// Grid.cpp
#include "grid.h"
#include "../models/data.h"
#include <iostream>
#include <sstream>

Grid::Grid(const Dimensions& gridSize, const std::string& fillChar)
    : fillChar(fillChar), gridSize(gridSize) {
    grid = std::vector<std::vector<char>>(gridSize.y, std::vector<char>(gridSize.x, fillChar[0]));
}

std::vector<int> Grid::rows() const {
    std::vector<int> rows(gridSize.y);
    for (int i = 0; i < gridSize.y; ++i) {
        rows[i] = i;
    }
    return rows;
}

std::vector<int> Grid::cols() const {
    std::vector<int> cols(gridSize.x);
    for (int i = 0; i < gridSize.x; ++i) {
        cols[i] = i;
    }
    return cols;
}

char Grid::get(const GridCoord& coord) const {
    int x, y;
    std::tie(x, y) = coord.to_tuple();
    if (x < 0 || x >= gridSize.x || y < 0 || y >= gridSize.y) {
        throw std::out_of_range("Coordinate " + coord.toString() + " is out of bounds");
    }
    return grid[y][x];
}

std::string Grid::get_alongPath(const Path& trajectory) const {
    std::string lookup;
    for (const auto& cell : trajectory.path) {
        lookup += get(cell);
    }
    return lookup;
}

void Grid::cellIterate() {
    for (int y = 0; y < gridSize.y; ++y) {
        for (int x = 0; x < gridSize.x; ++x) {
            GridCoord coord(x, y);
            // Yield coord
        }
    }
}

Grid Grid::copy() const {
    Grid gridCopy(gridSize, fillChar);
    gridCopy.grid = grid;
    return gridCopy;
}

char Grid::set(const GridCoord& coord, const std::string& value) {
    int x, y;
    std::tie(x, y) = coord.to_tuple();
    if (x < 0 || x >= gridSize.x || y < 0 || y >= gridSize.y) {
        throw std::out_of_range("Coordinate " + coord.toString() + " is out of bounds");
    }
    if (value.length() != 1) {
        throw std::invalid_argument("Character must be a single character string, got '" + value + "'");
    }
    grid[y][x] = value[0];
    return value[0];
}

bool Grid::empty(const GridCoord& coord) const {
    return get(coord) == fillChar[0];
}

bool Grid::word_canInsert(const std::string& word, const Path& alonglocation) const {
    if (word.length() != alonglocation.path.size()) {
        return false;
    }
    for (std::size_t i = 0; i < word.length(); ++i) {
        const GridCoord& gridPos = alonglocation.path[i];
        if (word[i] != get(gridPos) && !empty(gridPos)) {
            return false;
        }
    }
    return true;
}

std::string Grid::word_insert(const std::string& word, const Path& alonglocation) {
    if (word.length() != alonglocation.path.size()) {
        throw std::invalid_argument("Length of word " + word + " and location path (len: " + std::to_string(alonglocation.path.size()) + ") mismatch");
    }
    std::string inserted;
    for (std::size_t i = 0; i < word.length(); ++i) {
        const GridCoord& gridPos = alonglocation.path[i];
        if (word[i] == get(gridPos) || empty(gridPos)) {
            set(gridPos, std::string(1, word[i]));
            inserted += word[i];
        } else {
            break;
        }
    }
    return inserted;
}

bool Grid::has_word(const std::string& word) const {
    for (int y = 0; y < gridSize.y; ++y) {
        for (int x = 0; x < gridSize.x; ++x) {
            GridCoord cell(x, y);
            if (get(cell) != word[0]) {
                continue;
            }
            Trajectory trajectory(gridSize);
            std::vector<Path> trajectories = trajectory.paths_find(cell, word.length());
            for (const auto& path : trajectories) {
                if (get_alongPath(path) == word) {
                    return true;
                }
            }
        }
    }
    return false;
}

std::vector<GridCoord> Grid::has_char(const std::string& ch) const {
    std::vector<GridCoord> indices;
    for (int y = 0; y < gridSize.y; ++y) {
        for (int x = 0; x < gridSize.x; ++x) {
            if (grid[y][x] == char[0]) {
                indices.emplace_back(x, y);
            }
        }
    }
    return indices;
}

bool Grid::contains_word(const std::string& word) const {
    std::vector<GridCoord> gridCoords = has_char(std::string(1, word[0]));
    for (const auto& cell : gridCoords) {
        Trajectory trajectory(gridSize);
        std::vector<Path> trajectories = trajectory.paths_find(cell, word.length());
        for (const auto& path : trajectories) {
            if (get_alongPath(path) == word) {
                return true;
            }
        }
    }
    return false;
}

bool Grid::is_full() const {
    for (const auto& row : grid) {
        for (char c : row) {
            if (c == fillChar[0]) {
                return false;
            }
        }
    }
    for (const auto& row : grid) {
        for (char c : row) {
            if ((c < 'a' || c > 'z') && (c < 'A' || c > 'Z')) {
                return false;
            }
        }
    }
    return true;
}

std::string Grid::rows_get() const {
    std::ostringstream oss;
    for (const auto& row : grid) {
        for (char c : row) {
            oss << c << ' ';
        }
        oss << '\n';
    }
    return oss.str();
}

std::string Grid::strRep() const {
    std::string sprint = rows_get();
    for (char& c : sprint) {
        if (c == '\n') {
            c = '_';
        }
    }
    return sprint;
}

