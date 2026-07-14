#include "formatters/log.hpp"
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <string_view>

namespace {
  std::ostream& getLogOutput() {
    // need to change this so i can put where i wan't to store the logs and maby give the user
    // option to change it to
#ifdef NDEBUG
    static std::ofstream file{"app.log", std::ios::app};

    if (!file) {
      throw std::runtime_error{"Could not open app.log"};
    }

    return file;
#else
    return std::cout;
#endif
  }
} // namespace

namespace Config {
  Log::Log() : output_(getLogOutput()) {
    output_ << "LOG START AT XXXXXXX" << "\n";
  }
  void Log::write(std::string_view text) {
    output_ << text << "\n";
  }
} // namespace Config
