// Path.h
#ifndef PATH_H
#define PATH_H

#include <string>
#include <vector>
#include "../models/data.h"

std::string invalid_direction(GridDir direction);

class Path {
public:
    Path(const GridCoord& initialPosition, const Dimensions& gridSize);

    std::string str(Orient orientation = Orient::row) const;
    GridCoord dv_get(GridDir direction) const;
    std::vector<GridCoord> grow(GridDir direction, int distance);

    Dimensions gridSize;
    std::vector<GridCoord> path;
};

#endif // PATH_H
