// Trajectory.cpp
#include "trajectory.h"
#include "path.h"

Trajectory::Trajectory(const Dimensions& gridSize)
    : gridSize(gridSize) {
}

std::vector<Path> Trajectory::paths_find(const GridCoord& origin, int length) {
    paths.clear();

    for (const auto& direction : GridDir::values()) {
        bool canAddPath = true;
        Path path(origin, gridSize);

        try {
            path.grow(direction, length - 1); // length-1 since distances count from zero!
        } catch (...) {
            canAddPath = false;
        }

        if (canAddPath) {
            paths.push_back(path);
        }
    }

    return paths;
}
