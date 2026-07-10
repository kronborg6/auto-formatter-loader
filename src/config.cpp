#include "formatters/config.hpp"
#include "language.hpp"
#include "yaml-cpp/node/node.h"
#include "yaml-cpp/node/parse.h"
#include <cstdlib>
#include <filesystem>
#include <set>
#include <stdexcept>
#include <string>
#include <vector>

namespace fs = std::filesystem;

namespace option {
  Config::Config() {
    const char* home = std::getenv("HOME");
    if (!home)
      throw std::invalid_argument("");

    fs::path path = fs::path(home) / ".auto-formatter.yaml";

    if (!fs::exists(path))
      throw std::invalid_argument("failed to find config (.auto-formatter.yaml) at: " +
                                  path.string());

    Config::LoadFromNode(YAML::LoadFile(path));
  }
  Config::Config(fs::path path) {

    if (!fs::exists(path))
      throw std::invalid_argument("failed to find config.yaml file at: " + path.string());

    path_ = path;
    filename_ = path.filename();

    Config::LoadFromNode(YAML::LoadFile(path));

    // YAML::Node config = YAML
  }
  Config::Config(YAML::Node config) {

    Config::LoadFromNode(config);
  }

  void Config::LoadFromNode(const YAML::Node& node) {

    if (node["IDE"] && node["IDE"].IsSequence()) {
      auto temp = node["IDE"].as<std::vector<std::string>>();
      ides_ = std::set<std::string>(temp.begin(), temp.end());
    } else {
      // need to either thow a error
      // print it
      // or log it
      // becus
      // wee need to no this
    }

    if (node["formatters"]) {
      languge_ = node["formatters"].as<std::vector<Language>>();
    } else {
      // need to either thow a error
      // print it
      // or log it
      // becus
      // wee need to no this
    }

    if (node["maxDepth"]) {
      maxDepth_ = node["depth"].as<int>();
    }

    if (node["excludeFolders"]) {
      excludeFolders_ = node["excludeFolders"].as<std::vector<std::string>>();
    }

    if (node["overrideFormatter"]) {
      overrideFormatter_ = node["overrideFormatter"].as<bool>();
    }

    if (node["addToGitIgnore"]) {
      addToGitIgnore_ = node["addToGitIgnore"].as<bool>();
    }
  }

} // namespace option
