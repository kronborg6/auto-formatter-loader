#pragma once

#include "helper.hpp"
#include <filesystem>
#include <format>
#include <fstream>
#include <ostream>
#include <string>
#include <string_view>

namespace Config {

  class Log {
    public:
      Log();
      Log(std::ostream& config);
      // explicit Log(std::ostream& output) : output_(output) {};
      void write(std::ostream& output, std::string_view text);
      void write(std::string_view text);
      void writeln(std::string_view text);

    private:
      std::ostream& output_;
  };
  class GlobalLogger {
    public:
      static GlobalLogger& instance() {
        static GlobalLogger logger;
        return logger;
      }

      bool initialize(const std::filesystem::path& path) {
        output_.open(path, std::ios::app);

        if (!output_) {
          return false;
        }

        log_.emplace(output_);
        return true;
      }
      Config::Log* get() {
        return log_ ? &*log_ : nullptr;
      }

      void writeln(const std::string& message) {
        if (log_) {
          log_->writeln(message);
        }
      }
      void Logln(const std::string& message) {
        if (log_) {
          std::string format = "%H:%M:%S";
          std::string msg = std::format("[{}] {}", Helper::getTimeNow(format), message);
          log_->writeln(msg);
        }
      }

    private:
      GlobalLogger() = default;

      std::ofstream output_;
      std::optional<Config::Log> log_;
  };
  // class GlobalLogger {
  //   public:
  //     static GlobalLogger& Glinstance() {
  //       static GlobalLogger logger;
  //       return logger;
  //     }
  //
  //     bool initialize(const std::filesystem::path& path);
  //
  //     Config::Log* get();
  //
  //   private:
  //     GlobalLogger() = default;
  //
  //     std::ofstream output_;
  //     std::optional<Config::Log> log_;
  // };
} // namespace Config
