#include "processInfo.hpp"
#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <stdexcept>

ProcessInfo::ProcessInfo(std::string pid, std::string path) {
  if (pid.empty())
    throw std::invalid_argument("pid cannot be emty");
  if (path.empty())
    throw std::invalid_argument("path cannot be emty");

  pid_ = pid;
  path_ = path;
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
