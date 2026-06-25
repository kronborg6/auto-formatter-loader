#pragma once

#include <string>

struct Formatter {
    std::string filename;
    std::string filePath;
    bool inGitignore = false;
};
