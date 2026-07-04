#pragma once

#include "language.hpp"
#include "yaml-cpp/node/node.h"
#include <filesystem>
#include <string>
#include <unordered_set>
#include <vector>
namespace fs = std::filesystem;

namespace option {
class Config {
  public:
    Config();
    Config(YAML::Node node);
    Config(fs::path path);

    std::vector<Language> getLauges() const {
      return languge_;
    }
    std::string getPrograming(const std::string& name) const {
      for (const auto& lang : languge_) {
        if (lang.name == name) {
          return lang.name;
        }
      }
    }
    Language findLanuge(const std::string& name) const {
      for (const auto& lang : languge_) {
        if (lang.name == name) {
          return lang;
        }
      }
    }
    template <typename T> T getExcludeFolders() const;
    template <> std::vector<std::string> getExcludeFolders<std::vector<std::string>>() const {
      return excludeFolders_;
    }
    template <>
    std::unordered_set<std::string> getExcludeFolders<std::unordered_set<std::string>>() const {
      return std::unordered_set<std::string>(excludeFolders_.begin(), excludeFolders_.end());
      ;
    }

  private:
    fs::path path_;
    std::string filename_;
    std::vector<Language> languge_;
    std::vector<std::string> ides_;
    std::vector<std::string> excludeFolders_ = {".git", "build"};
    int depth_ = 2;

    void LoadFromNode(const YAML::Node& node);
};

} // namespace option
