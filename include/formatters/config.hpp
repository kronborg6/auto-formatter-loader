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
  enum LogLevel {
    NONE = 0,
    PRINT = 1,
    FILE = 2
  };
  const std::optional<fs::path> getHomePath();
  class Config {
    public:
      // template <typename T> T getExcludeFolders() const;
      Config();
      Config(YAML::Node node);
      Config(fs::path path);

      std::vector<Language> getLanguages() const {
        return language_;
      }
      std::optional<std::string> getPrograming(const std::string& name) const {
        for (const auto& lang : language_) {
          if (lang.name == name) {
            return lang.name;
          }
        }
        return std::nullopt;
      }
      std::optional<Language> findLanugeByFileType(const std::string& name) const {
        for (const auto& lang : language_) {
          for (const std::string& type : lang.filetypes) {
            if (type == name) {
              return lang;
            }
          }
        }
        return std::nullopt;
      }
      std::optional<Language> findLanuge(const std::string& name) const {
        for (const auto& lang : language_) {
          if (lang.name == name) {
            return lang;
          }
        }
        return std::nullopt;
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

      LogLevel getLogLevel() const {
        return logLevel_;
      }
      std::optional<fs::path> getLogPath() const {
        if (logLevel_ == LogLevel::FILE && logsPath_.has_value())
          return logsPath_;

        return std::nullopt;
      }

    private:
      fs::path path_;
      std::string filename_;
      std::vector<Language> language_;
      std::set<std::string> ides_;
      std::vector<std::string> excludeFolders_ = {".git", "build"};
      int maxDepth_ = 3;
      bool overrideFormatter_ = true;
      bool addToGitIgnore_ = true;
      std::optional<fs::path> logsPath_;
      LogLevel logLevel_ = LogLevel::FILE;

      void LoadFromNode(const YAML::Node& node);
  };
} // namespace option
