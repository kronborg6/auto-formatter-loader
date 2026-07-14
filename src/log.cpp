#include "formatters/log.hpp"
#include <fstream>
#include <iostream>
#include <stdexcept>

namespace {
  std::ostream& getLogOutput() {
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
  }
} // namespace Config
