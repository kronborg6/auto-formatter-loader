#include "formatters/log.hpp"
#include "formatters/templateLoader.hpp"
#include "processInfo.hpp"
#include "progams.hpp"
#include <algorithm>
#include <cctype>
#include <filesystem>
#include <format>
#include <iostream>
#include <string>

bool Programs::CreateNewFormatter(const std::filesystem::directory_entry& entry,
                                  const option::Config& config,
                                  const option::TemplateLoader& templates) {
  if (!entry.is_directory())
    return false;

  auto pid = entry.path().filename().string();

  if (!std::all_of(pid.begin(), pid.end(), ::isdigit))
    return false;

  if (match_name(pid, "nvim")) {
    auto cwd = std::filesystem::read_symlink("/proc/" + pid + "/cwd");
    ProcessInfo process(pid, cwd.string(), config, templates);

    if (!formaters.contains(cwd.string())) {
      formaters.emplace(cwd.string(), std::move(process));
      process.enable();
    }
  }
  return false;
}

bool Programs::CreateNewFormatter(const std::string& pid,
                                  const option::Config& config,
                                  const option::TemplateLoader& templates) {

  if (match_name(pid, config.getIdes())) {
    auto cwd = std::filesystem::read_symlink("/proc/" + pid + "/cwd");

    if (!formaters.contains(cwd.string())) {
      ProcessInfo process(pid, cwd.string(), config, templates);
      Config::GlobalLogger::instance().Logln(std::format(""));
      if (!process.getIsEnable()) {
        process.enable();
        this->enablePids.insert(pid);
        Config::GlobalLogger::instance().Logln(
            std::format("enable formatter for PID: {}, CWD: {}", pid, cwd.string()));
        formaters.emplace(cwd.string(), std::move(process));
      }
    } else {
      ProcessInfo& process = this->formaters.at(cwd.string());
      process.insert(pid);
      this->enablePids.insert(pid);
    }
  }
  return true;
}
bool Programs::removeFormatterViaPid(const std::string& pid) {
  for (auto& [key, value] : this->formaters) {
    if (value.containPid(pid)) {
      std::set<std::string> active_pids = value.getPids();
      this->formaters.erase(key);
      std::erase_if(this->enablePids,
                    [&](const std::string& x) { return active_pids.contains(x); });

      return true;
    }
  }
  return false;
}
