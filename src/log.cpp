#include "formatters/log.hpp"
#include "formatters/config.hpp"
#include <algorithm>
#include <chrono>
#include <ctime>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <ostream>
#include <sstream>
#include <stdexcept>
#include <string>
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
    auto time = getTimeNow();
    output_ << "[started at: " << time << "]\n";
  }
  void Log::write(std::string_view text) {
    output_ << text << "\n";
  }

  std::time_t Log::getTimeNowUtc() {
    const auto now = std::chrono::system_clock::now();
    return std::chrono::system_clock::to_time_t(now);
  }

  std::string Log::getTimeNow(bool withDate) {
    const std::time_t now = getTimeNowUtc();
    std::tm utcTime{};

#ifdef _WIN32
    gmtime_s(&utcTime, &now);
#else
    gmtime_r(&now, &utcTime);
#endif

    std::ostringstream output;
    if (withDate) {
      output << std::put_time(&utcTime, "%Y-%m-%d %H:%M:%S UTC");
    } else {
      output << std::put_time(&utcTime, "%H:%M:%S UTC");
    }

    return output.str();
  }

} // namespace Config
