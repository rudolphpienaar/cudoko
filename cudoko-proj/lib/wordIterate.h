// WordIterate.h
#ifndef WORDITERATE_H
#define WORDITERATE_H

#include <string>
#include <vector>

class WordIterate {
public:
    WordIterate(const std::vector<std::string>& words);

    std::string operator()();
    WordIterate copy() const;
    std::string str() const;

private:
    std::vector<std::string> words;
    std::size_t index;
};

#endif // WORDITERATE_H
