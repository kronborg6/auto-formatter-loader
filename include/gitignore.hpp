#pragma once

#include <cstdint>
#include <filesystem>
#include <optional>

namespace fs = std::filesystem;

struct Gitignore {
    fs::path path;
    // bool include = false;
    std::optional<std::uint16_t> line;
    std::string text;
};
