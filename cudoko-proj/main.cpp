// (c) 2024 Fetal-Neonatal Neuroimaging & Developmental Science Center
//                   Boston Children's Hospital
//
//              http://childrenshospital.org/FNNDSC/
//                        dev@babyMRI.org
//

#include <iostream>
#include <iterator>
#include <regex>
#include <string>
#include <vector>
// Include other necessary headers and libraries
#include "argh.h"
#include "cudoko.h"
#include "lib/grid.h"
#include "lib/trajectory.h"
#include "models/data.h"

// Define the version and other constants
const std::string VERSION = "version_number";
const std::string CY = "\033[36m"; // Cyan color code
const std::string YL = "\033[33m"; // Yellow color code
const std::string NC = "\033[0m";  // Reset color code
                                   //
// Define other color codes

// Define the str_desc with the appropriate color codes and version
const std::string str_desc = CY + R"(

 ██████╗██╗   ██╗██████╗  ██████╗ ██╗  ██╗ ██████╗
██╔════╝██║   ██║██╔══██╗██╔═══██╗██║ ██╔╝██╔═══██╗
██║     ██║   ██║██║  ██║██║   ██║█████╔╝ ██║   ██║
██║     ██║   ██║██║  ██║██║   ██║██╔═██╗ ██║   ██║
╚██████╗╚██████╔╝██████╔╝╚██████╔╝██║  ██╗╚██████╔╝
 ╚═════╝ ╚═════╝ ╚═════╝  ╚═════╝ ╚═╝  ╚═╝ ╚═════╝
)" + NC + R"(
                                make word grids
fth
                             -- version )" +
                             YL + VERSION + R"(
...

)" + "\033[0m"; // Reset color code

// Define other strings and constants

void path_test() {
  Dimensions gridSize = Dimensions(10, 10);
  GridCoord initialPosition = GridCoord(5, 5);

  Path path = Path(initialPosition, gridSize);
  Path leg = Path(initialPosition, gridSize);
  std::vector<GridCoord> trajectory;

  leg.path = path.grow(GridDir::E, 4);
  std::cout << leg.str() << std::endl;
  leg.path = path.grow(GridDir::N, 3);
  std::cout << leg.str() << std::endl;
  // leg.path = path.grow(GridDir::SE, 4);
  // std::cout << leg.str() << std::endl;

  std::cout << path.str() << std::endl;
}

void trajectory_test() {
  Trajectory trajectory = Trajectory(Dimensions(10, 10));
  trajectory.paths_find(GridCoord(1, 1), 3);
}

void gridWord_banner(std::string word) {
  Grid grid = Grid(Dimensions(13, 13), "-");
  Trajectory trajectory = Trajectory(Dimensions(13, 13));
  GridCoord origin = GridCoord(6, 6);

  for (const auto &path : trajectory.paths_find(origin, word.length())) {
    if (grid.word_canInsert(word, path)) {
      grid.word_insert(word, path);
    }
  }
  std::cout << grid.cstr();
}

int main(int argc, char const *argv[]) {
  // Parse arguments and implement the logic
  // Call the synopsis function if needed
  // Implement other functionalities
  Space options = Space();
  int parserOK = 0;
  options = parser_setup(argc, argv, parserOK);

  // path_test();
  // trajectory_test();
  gridWord_banner("cudoko");

  Cudoko cudoko = Cudoko(options);
  cudoko.solve();

  printf("about to exit!\n");
  return 0;
}

// Function definitions
void synopsis(bool ab_shortOnly) {
  // Define the scriptName and shortSynopsis with the appropriate strings
  // Define the description and other parts of the synopsis
  // Print the synopsis based on the ab_shortOnly flag
  // Implement other function definitions
}
