#pragma once

#include "language.hpp"
#include "yaml-cpp/node/node.h"
#include <filesystem>
#include <string>
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

  private:
    fs::path path_;
    std::string filename_;
    std::vector<Language> languge_;
    std::vector<std::string> ides_;

    void LoadFromNode(const YAML::Node& node);
};

} // namespace option
