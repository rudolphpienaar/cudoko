// Trajectory.h
#ifndef TRAJECTORY_H
#define TRAJECTORY_H

#include <vector>
#include "../models/data.h"
#include "path.h"

class Trajectory {
public:
    Trajectory(const Dimensions& gridSize = Dimensions(0, 0));

    std::vector<Path> paths_find(const GridCoord& origin, int length);

    Dimensions gridSize;
    std::vector<Path> paths;
};

#endif // TRAJECTORY_H
