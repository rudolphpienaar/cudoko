// WordIterate.cpp
#include "wordIterate.h"
#include <sstream>

WordIterate::WordIterate(const std::vector<std::string>& words)
    : words(words), index(0) {}

std::string WordIterate::operator()() {
    if (index >= words.size()) {
        return "";
    }

    std::string word = words[index];
    ++index;
    return word;
}

WordIterate WordIterate::copy() const {
    WordIterate iterateCopy(words);
    iterateCopy.index = index;
    return iterateCopy;
}

std::string WordIterate::str() const {
    std::stringstream ss;
    ss << index << ":" << "[";
    for (std::size_t i = 0; i < words.size(); ++i) {
        if (i > 0) {
            ss << ", ";
        }
        ss << words[i];
    }
    ss << "]";
    return ss.str();
}

