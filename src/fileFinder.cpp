#include "fileFinder.hpp"

template <typename Container>
std::optional<fs::directory_entry> FindMatch(const fs::path& path, const Container& targets) {
  for (const auto& entry : fs::directory_iterator(path)) {
    const auto filename = entry.path().filename().string();

    if (std::find(targets.begin(), targets.end(), filename) != targets.end()) {
      return entry;
    }
  }
  return std::nullopt;
}
