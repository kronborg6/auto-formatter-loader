#include "formatters/log.hpp"
#include "helper.hpp"
#include <filesystem>
#include <fstream>
#include <iostream>
#include <optional>
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
    output_ << text;
    output_.flush();
  }
  void Log::writeln(std::string_view text) {
    output_ << text << "\n";
    output_.flush();
  }

  // bool GlobalLogger::initialize(const std::filesystem::path& path) {
  //   output_.open(path, std::ios::app);
  //
  //   if (!output_)
  //     return false;
  //
  //   log_.emplace(output_);
  //
  //   return true;
  // }
  //
  // Config::Log* GlobalLogger::get() {
  //   return log_ ? &*log_ : nullptr;
  // }
  //
  // std::ofstream output_;
  // std::optional<Config::Log> log_;

} // namespace Config
