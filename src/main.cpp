#include "formatters/config.hpp"
#include "formatters/log.hpp"
#include "formatters/templateLoader.hpp"
#include "helper.hpp"
#include "iostream"
#include "progams.hpp"
#include <cctype>
#include <chrono>
#include <cstddef>
#include <filesystem>
#include <format>
#include <set>
#include <string>
#include <sys/inotify.h>
#include <sys/poll.h>
#include <thread>
#include <unistd.h>
#include <yaml-cpp/yaml.h>

bool is_pid_dir(const std::filesystem::directory_entry& entry) {
  if (!entry.is_directory())
    return false;

  std::string name = entry.path().filename().string();

  for (char c : name) {
    if (!std::isdigit(static_cast<unsigned char>(c)))
      return false;
  }

  return !name.empty();
}

std::set<std::string> get_pids() {
  std::set<std::string> pids;

  for (auto& entry : std::filesystem::directory_iterator("/proc")) {
    if (!is_pid_dir(entry))
      continue;

    pids.insert(entry.path().filename().string());
    auto temp = std::filesystem::directory_entry("/proc/" + entry.path().filename().string());
  }
  return pids;
}

size_t count = 0;

int main(void) {
#ifdef DEV_MODE
  option::Config config = option::Config(YAML::LoadFile("/home/kronborg/.auto-formatter.yaml"));
#else
  option::Config config = option::Config();
#endif

  switch (config.getLogLevel()) {
  case option::LogLevel::FILE:
    if (config.getLogPath().has_value()) {
      // need to be a customer name somfig like log-2026-07-21-17-60:01
      std::string format = "_%y-%m-%d.log";
      std::string name = "log" + Helper::getTimeNow(format);
      std::filesystem::create_directories(config.getLogPath().value());
      auto path = config.getLogPath().value() / name;

      if (!Config::GlobalLogger::instance().initialize(path)) {
        std::cerr << "failed to initialize logger\n";
        return 1;
      }
    }
    break;
  case option::LogLevel::PRINT:
    if (!Config::GlobalLogger::instance().initialize()) {
      std::cerr << "failed to initialize logger\n";
      return 1;
    }
    break;
  case option::LogLevel::NONE:
    break;
  }

  Programs progams;
  // need to make a load from config her
  // then load the templates check for args to change dir
  const option::TemplateLoader templates = option::TemplateLoader();

  std::set<std::string> pids = get_pids();
  for (const std::string& pid : pids) {
    if (!progams.enablePids.contains(pid))
      progams.CreateNewFormatter(pid, config, templates);
  }
  for (;;) {
    std::this_thread::sleep_for(std::chrono::seconds(3));

    std::set<std::string> new_pids = get_pids();
    for (const std::string& pid : new_pids) {
      if (!progams.enablePids.contains(pid))
        progams.CreateNewFormatter(pid, config, templates);
    }

    // TODO: need to change this to get a list of the cwd insted then loop over the once that need
    // to get removed so we don't need to break after removeing
    for (const std::string& pid : progams.enablePids) {
      if (!new_pids.contains(pid)) {
        // remove it
        if (progams.removeFormatterViaPid(pid))
          break;
      }
    }
    if (count != progams.formaters.size()) {
      count = progams.formaters.size();

      Config::GlobalLogger::instance().Logln(std::format("enabled formater count: {} ", count));
    }
    pids = progams.enablePids;
  }

  // for (const auto& x : progams.formaters | std::views::values) {
  //   Config::GlobalLogger::instance().Logln(std::format("pid: "));
  //   // std::cout << "pid: " << x.print() << "CWD: " << x.getPath() << std::endl;
  // }
  return 0;
}
