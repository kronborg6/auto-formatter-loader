#include "formatters/config.hpp"
#include "formatters/templateLoader.hpp"
#include "iostream"
#include "progams.hpp"
#include "yaml-cpp/node/parse.h"
#include <cctype>
#include <chrono>
#include <cstddef>
#include <filesystem>
#include <ranges>
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
  option::Config config = option::Config(YAML::LoadFile("/home/kronborg/.auto-formatter.yaml"));

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

    // TODO: change this to get the cwd in side the first if and use that to make a list of the once
    // that need to get removed
    for (const std::string& pid : progams.enablePids) {
      if (!new_pids.contains(pid)) {
        // remove it
        if (progams.removeFormatterViaPid(pid))
          break;
      }
    }
    if (count != progams.formaters.size()) {
      count = progams.formaters.size();
      std::cout << "formaters cout: " << count << std::endl;
    }
    pids = progams.enablePids;
  }

  for (const auto& x : progams.formaters | std::views::values) {
    std::cout << "pid: " << x.print() << "CWD: " << x.getPath() << std::endl;
  }
  return 0;
}
