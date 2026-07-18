#include "formatters/log.hpp"
#include "helper.hpp"
#include <iostream>
#include <ostream>
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
  Log::Log(std::ostream& output) : output_(output) {
    auto time = Helper::getTimeNow();
    output_ << "[started at: " << time << "]\n";
  }
  void Log::write(std::string_view text) {
    output_ << text << "\n";
  }

} // namespace Config
