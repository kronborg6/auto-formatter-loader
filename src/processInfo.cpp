#include "processInfo.hpp"
#include "fileFinder.hpp"
#include "formatters/config.hpp"
#include "formatters/formatter.hpp"
#include "formatters/log.hpp"
#include "formatters/templateLoader.hpp"
#include "language.hpp"
#include <algorithm>
#include <cassert>
#include <cstdio>
#include <filesystem>
#include <format>
#include <fstream>
#include <iostream>
#include <optional>
#include <stdexcept>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace fs = std::filesystem;

ProcessInfo::~ProcessInfo() {

  if (isEnable_ && !file_.empty() &&
      fs::is_symlink(this->path_ + "/" + this->formatterTemplate_->filename)) {

    if (fs::remove(this->path_ + "/" + this->formatterTemplate_->filename)) {

      Config::GlobalLogger::instance().Logln(
          std::format("Remove formater for PID: {}", this->print()));

      if (this->gitingore_.has_value())
        this->gitingore_->removeFromGitignore();
      if (this->oldFormatter_.has_value())
        removeOldFormaterTag();

    } else {

      Config::GlobalLogger::instance().Logln(
          std::format("Failed to remove formater for PID: {}", this->print()));
    }
  }
}

ProcessInfo::ProcessInfo(std::string pid,
                         std::string path,
                         const option::Config& config,
                         const option::TemplateLoader& templates) {
  if (pid.empty())
    throw std::invalid_argument("pid cannot be emty");
  if (path.empty())
    throw std::invalid_argument("path cannot be emty");

  pids_.insert(pid);
  path_ = path;

  // const std::unordered_set<std::string> folders_to_skip =
  //     config.getExcludeFolders<std::unordered_set<std::string>>();
  const std::unordered_set<std::string> folders_to_skip = config.getExcludeFolders();

  const auto options = fs::directory_options::skip_permission_denied;

  std::unordered_map<std::string, int> typeCount;

  // make the filetype ProgramingLaunge hash_maps here
  std::unordered_map<std::string, std::string> all;
  for (const auto& lang : config.getLanguages()) {
    for (const auto& type : lang.filetypes) {
      all[type] = lang.name;
    }
  }

  for (fs::recursive_directory_iterator it(path, options), end; it != end; ++it) {
    if (it.depth() >= config.getMaxDepth()) {
      it.disable_recursion_pending();
    }

    const fs::directory_entry& entry = *it;
    std::string filepath = entry.path().filename().string();

    if (entry.is_directory()) {
      if (folders_to_skip.contains(filepath)) {
        it.disable_recursion_pending();
        continue;
      }
    }
    std::string filename = entry.path().filename().string();

    if (filename == ".gitignore" && !this->gitingore_ && config.getAddToGitignore()) {
      this->gitingore_.emplace(Gitignore{
          .path = entry.path(),
          .init = false,
          .text = "",
      });

      assert(this->gitingore_.has_value());
    }

    std::size_t dotPos = filename.find_last_of('.');

    if (dotPos == std::string::npos) {
      continue; // no extension
    }

    std::string last = filename.substr(dotPos + 1);

    if (config.getOverRideFormater()) {

      std::optional<Formatter> temp = FindMatch(filename, templates.GetFormatters());
      if (temp.has_value()) {
        Formatter oldformater{
            .filename = temp.value().filename,
            .filePath = entry.path(),
        };
        oldFormatter_ = oldformater;
      }
    }

    // need to change this to use langue from config
    // i was thinking about making hash_maps where the filetype is the key and ProgramingLaunge is
    // the value

    if (all.contains(last)) {
      typeCount[last]++;
    }
  }

  if (typeCount.empty()) {
    Config::GlobalLogger::instance().Logln(std::format("{}", print()));
    return;
  }

  auto maxType = std::max_element(
      typeCount.begin(), typeCount.end(), [](const auto& a, const auto& b) { return a < b; });

  type_ = maxType->first;

  if (oldFormatter_.has_value() && !config.getOverRideFormater()) {
    return;
  }

  std::optional<Language> la = config.findLanugeByFileType(type_);

  if (!la)
    return;
  // need to make a check her if la is null and make it so we don't crach if they is no formatter in
  // templates
  auto it = templates.getFormatter(la.value().formatter);
  if (!it) {
    return;
  }
  formatterTemplate_ = it;

  // need to check what kid of project it is
  // after check if it contains a formater
  // if it does copy path and file name then change it to fx filename.temp
  // add avore own
  // check .gitignore if it have the formater inside if not add it
}

bool match_name(const std::string& pid, const std::string& target) {
  std::ifstream f("/proc/" + pid + "/comm");
  std::string name;
  std::getline(f, name);
  return name == target;
}

bool match_name(const std::string& pid, const std::set<std::string>& target) {
  std::ifstream f("/proc/" + pid + "/comm");
  std::string name;
  std::getline(f, name);
  return target.contains(name);
}

void ProcessInfo::enable() {
  if (formatterTemplate_ == nullptr || isEnable_)
    return;

  if (oldFormatter_) {
    auto newPath = oldFormatter_->filePath.string() + ".old-formatter";

    fs::rename(oldFormatter_->filePath, newPath);

    Config::GlobalLogger::instance().Logln(
        std::format("Renamed old formatter: {} to {}", oldFormatter_->filePath.string(), newPath));
  }

  if (!fs::exists(this->path_ + "/" + this->formatterTemplate_->filename)) {

    fs::create_symlink(formatterTemplate_->filePath,
                       this->path_ + "/" + this->formatterTemplate_->filename);

    file_ = this->formatterTemplate_->filename;

    Config::GlobalLogger::instance().Logln(std::format("created system link for {}", print()));

    if (this->gitingore_.has_value()) {
      this->gitingore_->addToGitignore(formatterTemplate_->filename);
    }

    isEnable_ = true;
  }
}

bool ProcessInfo::createFormater() {
  if (this->formater_)
    return true;
  return true;
}
bool ProcessInfo::removeOldFormaterTag() {
  if (oldFormatter_.has_value()) {
    auto oldPath = oldFormatter_->filePath.string() + ".old-formatter";

    Config::GlobalLogger::instance().Logln(std::format(
        "Restoring old formatter from: {} to {}", oldPath, oldFormatter_->filePath.string()));

    fs::rename(oldPath, oldFormatter_->filePath);

    return true;
  }
  return false;
}

bool ProcessInfo::deletFormater() {
  if (this->formater_) {
    std::string filePath = this->path_ + "" + this->file_;
    std::remove(filePath.c_str());
    return true;
  }
  return false;
}
