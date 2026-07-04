#include "processInfo.hpp"
#include "formatters/config.hpp"
#include "formatters/formatter.hpp"
#include "formatters/templateLoader.hpp"
#include "language.hpp"
#include "project_type.hpp"
#include "stringHelper.hpp"
#include <algorithm>
#include <cstdio>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>
namespace fs = std::filesystem;

ProcessInfo::~ProcessInfo() {

  if (isEnable_ && fs::is_symlink(this->path_ + "/" + this->formatterTemplate_->filename)) {

    if (fs::remove(this->path_ + "/" + this->formatterTemplate_->filename)) {
      std::cout << "i remove the link"
                << "\n";
    } else {

      std::cout << "failed to remove the link"
                << "\n";
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

  pid_ = pid;
  path_ = path;

  // const std::unordered_set<std::string> folders_to_skip =
  //     config.getExcludeFolders<std::unordered_set<std::string>>();
  const std::unordered_set<std::string> folders_to_skip = config.getExcludeFolders();

  const auto options = fs::directory_options::skip_permission_denied;

  std::unordered_map<std::string, int> typeCount;

  // make the filetype ProgramingLaunge hash_maps here
  std::unordered_map<std::string, std::string> all;
  for (const auto& lang : config.getLauges()) {
    for (const auto& type : lang.filetypes) {
      all[lang.name] = type;
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

    std::size_t dotPos = filename.find_last_of('.');

    if (dotPos == std::string::npos) {
      continue; // no extension
    }

    std::string last = filename.substr(dotPos + 1);
    // std::string filename = entry.path().filename().string().substr(
    //     entry.path().filename().string().find_last_of("/") + 1);
    //
    // std::vector<std::string> splitString = split(filename, ".");
    //
    // std::string& last = splitString[splitString.size() - 1];

    if (last == "clang-format") {
      Formatter oldformater = Formatter{
          filename = ".clang-format",
          filepath = entry.path().filename(),
      };
      oldFormatter_ = oldformater;
    }

    // need to change this to use langue from config
    // i was thinking about making hash_maps where the filetype is the key and ProgramingLaunge is
    // the value

    if (all.contains(last)) {
      typeCount[last]++;
    }
    std::cout << entry.path() << '\n';
  }

  for (const auto& [key, value] : typeCount) {
    std::cout << key << ": " << value << "\n";
  }

  if (typeCount.empty()) {
    return;
  }

  auto maxType = std::max_element(
      typeCount.begin(), typeCount.end(), [](const auto& a, const auto& b) { return a < b; });

  type_ = maxType->first;

  std::cout << std::boolalpha << "has_value = " << oldFormatter_.has_value() << '\n';
  if (oldFormatter_.has_value()) {
    std::cout << oldFormatter_.value().filePath << "\n";
    return;
  }

  Language la = config.findLanuge(type_);

  formatterTemplate_ = &templates.getFormatter(la.formatter);

  // switch (type_) {
  // case ProgramingLaunge::Cpp:
  //   formatterTemplate_ = &formatters.getFormatter(".clang-format");
  //   break;
  // case ProgramingLaunge::C:
  //   break;
  // case ProgramingLaunge::Zig:
  //   break;
  // case ProgramingLaunge::Rust:
  //   break;
  // }
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

void ProcessInfo::enable() {
  if (formatterTemplate_ == nullptr || isEnable_ || oldFormatter_.has_value())
    return;

  if (!fs::exists(this->path_ + "/" + this->formatterTemplate_->filename)) {
    fs::create_symlink(formatterTemplate_->filePath,
                       this->path_ + "/" + this->formatterTemplate_->filename);
    std::cout << "created system link\n";
    isEnable_ = true;
  }
}

bool ProcessInfo::createFormater(std::string formaterPath) {
  if (this->formater_)
    return true;
  return true;
}

bool ProcessInfo::createFormater() {
  if (this->formater_)
    return true;
  return true;
}

bool ProcessInfo::deletFormater() {
  if (this->formater_) {
    std::string filePath = this->path_ + "" + this->file_;
    std::remove(filePath.c_str());
  } else {
    return false;
  }
}
