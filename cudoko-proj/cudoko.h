// cudoko.h
#ifndef CUDOKO_H
#define CUDOKO_H

#include <string>
#include <vector>
#include <map>
// Include the header for the Argh class
#include "argh.h"

// Assuming Dimensions, Space, Solution, WordIterate, and Grid are already defined in their respective headers

class Wudoko {
public:
    Wudoko(std::map<std::string, std::string> optionsMap = {});
    void solve();

private:
    Space options;
    std::string desc;
    Dimensions gridSize;
    std::vector<std::string> words;
    std::vector<std::string> wordsExclude;
    Solution solution;

    Dimensions gridDimensions_set();
    void words_populate();
    void boards_headerPrint(int numberOfBoards, std::string qualifier = "solution");
    void boards_print(const std::vector<Grid>& boards);
    void solve_allBoards();
    void prune_illegalBoards();
};

// Function declarations
Argh parser_setup(int argc, char const* argv[]);
bool namespace_isempty(std::map<std::string, std::string>& namespace_map);
std::vector<std::string> wordFile_read(std::string filename);

#endif // CUDOKO_H

