// Grid.h
#ifndef GRID_H
#define GRID_H

#include <string>
#include <vector>
#include "path.h"
#include "../models/data.h"

class Grid {
public:
    Grid(const Dimensions& gridSize, const std::string& fillChar = "*");

    std::vector<int> rows() const;
    std::vector<int> cols() const;
    char get(const GridCoord& coord) const;
    std::string get_alongPath(const Path& trajectory) const;
    void cellIterate();
    Grid copy() const;
    char set(const GridCoord& coord, const std::string& value);
    bool empty(const GridCoord& coord) const;
    bool word_canInsert(const std::string& word, const Path& alonglocation) const;
    std::string word_insert(const std::string& word, const Path& alonglocation);
    bool has_word(const std::string& word) const;
    std::vector<GridCoord> has_char(const std::string& ch) const;
    bool contains_word(const std::string& word) const;
    bool is_full() const;
    std::string rows_get() const;
    std::string strRep() const;

private:
    std::string fillChar;
    Dimensions gridSize;
    std::vector<std::vector<char>> grid;
};

#endif // GRID_H

