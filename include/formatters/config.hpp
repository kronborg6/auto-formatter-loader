#pragma once

#include "language.hpp"
#include <filesystem>
#include <string>
#include <unordered_map>
#include <vector>
namespace fs = std::filesystem;

namespace option {
  class Config {
    public:
      Config();
      Config(fs::path path);

    private:
      fs::path path_;
      std::string filename_;
      std::vector<Language> languge_;
      std::vector<std::string> ides_;
  };

} // namespace option
