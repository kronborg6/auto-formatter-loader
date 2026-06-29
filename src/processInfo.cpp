#include "processInfo.hpp"
#include "formatters/formatter.hpp"
#include "formatters/templateLoader.hpp"
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

ProcessInfo::ProcessInfo(std::string pid,
                         std::string path,
                         // const std::unordered_map<std::string, Formatter>& formatters) {
                         const option::TemplateLoader& formatters) {
  if (pid.empty())
    throw std::invalid_argument("pid cannot be emty");
  if (path.empty())
    throw std::invalid_argument("path cannot be emty");

  pid_ = pid;
  path_ = path;

  const std::unordered_set<std::string> folders_to_skip = {".git", "build"};

  const auto options = fs::directory_options::skip_permission_denied;

  std::unordered_map<ProgramingLaunge, int> typeCount;

  for (fs::recursive_directory_iterator it(path, options), end; it != end; ++it) {

    const fs::directory_entry& entry = *it;
    std::string filepath = entry.path().filename().string();

    if (entry.is_directory()) {
      if (folders_to_skip.contains(filepath)) {
        it.disable_recursion_pending();
        continue;
      }
    }

    std::string filename = entry.path().filename().string().substr(
        entry.path().filename().string().find_last_of("/") + 1);

    std::vector<std::string> splitString = split(filename, ".");

    std::string& last = splitString[splitString.size() - 1];

    if (last == "clang-format") {
      Formatter oldformater = Formatter{
          filename = ".clang-format",
          filepath = entry.path().filename(),
      };
      oldFormatter_ = oldformater;
    }

    if (last == "cpp" || last == "hpp") {
      typeCount[ProgramingLaunge::Cpp]++;
      continue;
    } else if (last == "c" || last == "h") {
      std::cout << entry.path() << '\n';
      std::cout << entry.path() << '\n';
      typeCount[ProgramingLaunge::C]++;
      continue;
    } else if (last == "zig") {
      typeCount[ProgramingLaunge::Zig]++;
      continue;
    }
    std::cout << entry.path() << '\n';
  }

  for (const auto& [key, value] : typeCount) {
    std::cout << toString(key) << ": " << value << "\n";
  }

  auto maxType = std::max_element(
      typeCount.begin(), typeCount.end(), [](const auto& a, const auto& b) { return a < b; });

  type_ = maxType->first;

  std::cout << std::boolalpha << "has_value = " << oldFormatter_.has_value() << '\n';
  if (oldFormatter_.has_value()) {
    std::cout << oldFormatter_.value().filePath << "\n";
    return;
  }

  switch (type_) {
  case ProgramingLaunge::Cpp:
    // need to get formater from config
    // if (std::unordered_map<std::string, Formatter>::const_iterator it =
    //         formatters.find(".clang-format");
    //     it != formatters.end()) {
    //   formatterTemplate_ = &it->second;
    // }
    formatterTemplate_ = &formatters.getFormatter(".clang-format");
    break;
  case ProgramingLaunge::C:
    break;
  case ProgramingLaunge::Zig:
    break;
  case ProgramingLaunge::Rust:
    break;
  }
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
