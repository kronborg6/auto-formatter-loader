#include "formatters/config.hpp"
#include "language.hpp"
#include "yaml-cpp/node/node.h"
#include "yaml-cpp/node/parse.h"
#include <cstdlib>
#include <filesystem>
#include <optional>
#include <set>
#include <stdexcept>
#include <string>
#include <string_view>
#include <vector>

namespace fs = std::filesystem;

namespace option {

  const fs::path localGetLogPath(const YAML::Node& node);
  Config::Config() {
    std::optional<fs::path> home = getHomePath();
    if (!home.has_value())
      throw std::invalid_argument("missing home path");

    fs::path path = home.value() / ".auto-formatter.yaml";

    if (!fs::exists(path))
      throw std::invalid_argument("failed to find config (.auto-formatter.yaml) at: " +
                                  path.string());

    // logsPath_ = fs::path(home) / "autoFormatter/logs";
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
      language_ = node["formatters"].as<std::vector<Language>>();
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

    if (node["logLevel"]) {

      int lvl = node["logLevel"].as<int>();
      logLevel_ = static_cast<LogLevel>(lvl);
    }

    switch (logLevel_) {
    case option::LogLevel::FILE:
      if (node["logPath"]) {
        logsPath_ = localGetLogPath(node);
      } else {
        auto home = getHomePath();
        if (home.has_value())
          logsPath_ = home.value() / ".config/autoFormatter/logs";
      }
      break;
    case option::LogLevel::PRINT:
    case option::LogLevel::NONE:
      logsPath_ = std::nullopt;
      break;
    }
  }

  const fs::path localGetLogPath(const YAML::Node& node) {
    std::string_view path = node["logPath"].as<std::string_view>();
    return fs::path(path);
  }

  const std::optional<fs::path> getHomePath() {
    const char* home = std::getenv("HOME");

    if (!home) {
      return std::nullopt;
    }

    return fs::path(home);
  }
} // namespace option
