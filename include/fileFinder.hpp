#pragma once
#include <filesystem>

namespace fs = std::filesystem;

template <typename Container>
std::optional<fs::directory_entry> FindMatch(const fs::path& path, const Container& targets);
