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

  private:
    fs::path path_;
    std::string filename_;
    std::vector<Language> languge_;
    std::vector<std::string> ides_;

    void LoadFromNode(const YAML::Node& node);
};

} // namespace option
