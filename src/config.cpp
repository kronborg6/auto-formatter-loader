#include "formatters/config.hpp"
#include "language.hpp"
#include "yaml-cpp/node/node.h"
#include "yaml-cpp/node/parse.h"
#include <cstdlib>
#include <filesystem>
#include <stdexcept>
#include <string>
#include <vector>

namespace fs = std::filesystem;

namespace option {
  Config::Config() {
    const char* home = std::getenv("HOME");
    if (!home)
      throw std::invalid_argument("");

    fs::path configPath = fs::path(home) / ".auto-formatter.yaml";

    if (!fs::exists(configPath))
      throw std::invalid_argument("");

    YAML::Node config = YAML::LoadFile(configPath);

    if (config["IDE"]) {
      this->ides_ = config["IDE"].as<std::vector<std::string>>();
    }

    if (config["formatters"]) {
      // std::vector<Language> lang ;
      languge_ = config["formatters"].as<std::vector<Language>>();
    }
  }
  Config::Config(fs::path path) {
  }
  Config::Config(YAML::Node node) {
  }
} // namespace option
