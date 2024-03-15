// Path.h
#ifndef PATH_H
#define PATH_H

#include "../models/data.h"
#include <string>
#include <vector>

std::string invalid_direction(GridDir direction);

class Path {
public:
  Dimensions gridSize;
  std::vector<GridCoord> path;

  Path(const GridCoord &initialPosition, const Dimensions &gridSize);

  std::string str(Orient orientation = Orient::row) const;
  GridCoord dv_get(GridDir direction) const;
  std::vector<GridCoord> grow(GridDir direction, int distance);
};

#endif // PATH_H
