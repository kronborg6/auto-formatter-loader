#pragma once

#include <filesystem>
#include <string>

struct Formatter {
    std::string filename;
    std::filesystem::path filePath;
    bool inGitignore = false;
};
