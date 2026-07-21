#pragma once
#include <filesystem>
#include <string>
#include <unordered_map>

namespace fs = std::filesystem;

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
template <typename T, typename Options, typename Target>
std::optional<T> FindMatch(const Options& options, const Target& targets);

template <typename Key, typename Value>
std::optional<Value> FindMatch(const Key& key, const std::unordered_map<Key, Value>& targets) {
  auto target = targets.find(key);

  if (target == targets.end()) {
    return std::nullopt;
  }
  return target->second;
}
