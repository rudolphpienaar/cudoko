// Path.cpp
#include "path.h"
#include <sstream>
#include <stdexcept>

std::string invalid_direction(GridDir direction) {
  std::stringstream ss;
  ss << "Invalid direction " << static_cast<int>(direction) << "\n"
     << "Must be one of\n"
     << "'N'\n"
     << "'NW' 'NE'\n"
     << "'W' 'E'\n"
     << "'SW' 'SE'\n"
     << "'S'\n";
  return ss.str();
}

Path::Path(const GridCoord &initialPosition, const Dimensions &gridSize)
    : gridSize(gridSize) {
  path.push_back(initialPosition);
}

std::string Path::str(Orient orientation) const {
  std::stringstream ss;
  ss << "[";
  if (orientation == Orient::row) {
    for (std::size_t i = 0; i < path.size(); ++i) {
      if (i > 0) {
        ss << " ";
      }
      ss << path[i].to_string();
    }
  } else {
    for (std::size_t i = 0; i < path.size(); ++i) {
      if (i > 0) {
        ss << "\n";
      }
      ss << path[i].to_string();
    }
  }
  ss << "]";
  return ss.str();
}

GridCoord Path::dv_get(GridDir direction) const {
  GridCoord dxy(0, 0);
  switch (direction) {
  case GridDir::N:
    dxy = GridCoord(0, -1);
    break;
  case GridDir::S:
    dxy = GridCoord(0, 1);
    break;
  case GridDir::E:
    dxy = GridCoord(1, 0);
    break;
  case GridDir::W:
    dxy = GridCoord(-1, 0);
    break;
  case GridDir::NE:
    dxy = GridCoord(1, -1);
    break;
  case GridDir::NW:
    dxy = GridCoord(-1, -1);
    break;
  case GridDir::SE:
    dxy = GridCoord(1, 1);
    break;
  case GridDir::SW:
    dxy = GridCoord(-1, 1);
    break;
  default:
    throw std::invalid_argument(invalid_direction(direction));
  }
  return dxy;
}

std::vector<GridCoord> Path::grow(GridDir direction, int distance) {
  std::vector<GridCoord> new_positions;
  try {
    GridCoord dxy = dv_get(direction);

    if (path.empty()) {
      throw std::invalid_argument("Cannot grow from an empty path");
    }

    GridCoord pathEndCoord = path.back();
    for (int i = 0; i < distance; ++i) {
      pathEndCoord = pathEndCoord + dxy;
      if (pathEndCoord.x < 0 || pathEndCoord.x >= gridSize.x ||
          pathEndCoord.y < 0 || pathEndCoord.y >= gridSize.y) {
        std::stringstream ss;
        ss << "Path extends outside the grid in " << gridDirName(direction)
           << " direction\n"
           << "Violation at grid space: " << pathEndCoord.x << ", "
           << pathEndCoord.y << "\n"
           << "Current path: " << str(Orient::row);
        throw std::out_of_range(ss.str());
      }
      new_positions.push_back(pathEndCoord);
    }

    path.insert(path.end(), new_positions.begin(), new_positions.end());
  } catch (const std::exception &e) {
    throw;
  }

  return new_positions;
}
