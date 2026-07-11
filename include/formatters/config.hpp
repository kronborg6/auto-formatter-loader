#pragma once

#include "language.hpp"
#include "yaml-cpp/node/node.h"
#include <filesystem>
#include <optional>
#include <string>
#include <unordered_set>
#include <vector>
namespace fs = std::filesystem;

namespace option {
class Config {
  public:
    // template <typename T> T getExcludeFolders() const;
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
    std::optional<Language> findLanugeByFileType(const std::string& name) const {
      for (const auto& lang : languge_) {
        for (const std::string& type : lang.filetypes) {
          if (type == name) {
            return lang;
          }
        }
      }
      return std::nullopt;
    }
    Language findLanuge(const std::string& name) const {
      for (const auto& lang : languge_) {
        if (lang.name == name) {
          return lang;
        }
      }
    }
    std::unordered_set<std::string> getExcludeFolders() const {
      return std::unordered_set<std::string>(excludeFolders_.begin(), excludeFolders_.end());
    }

    std::set<std::string> getIdes() const {
      return ides_;
    }

    bool getAddToGitignore() const {
      return addToGitIgnore_;
    }

    int getMaxDepth() const {
      return maxDepth_;
    }

  private:
    fs::path path_;
    std::string filename_;
    std::vector<Language> languge_;
    std::set<std::string> ides_;
    std::vector<std::string> excludeFolders_ = {".git", "build"};
    int maxDepth_ = 3;
    bool overrideFormatter_ = true;
    bool addToGitIgnore_ = true;

    void LoadFromNode(const YAML::Node& node);
};

// template <>
// inline std::vector<std::string> Config::getExcludeFolders<std::vector<std::string>>() const {
//   return excludeFolders_;
// }
//
// template <>
// inline std::unordered_set<std::string>
// Config::getExcludeFolders<std::unordered_set<std::string>>() const {
//   return std::unordered_set<std::string>(excludeFolders_.begin(), excludeFolders_.end());
} // namespace option
