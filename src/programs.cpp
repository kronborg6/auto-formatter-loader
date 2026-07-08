#include "formatters/templateLoader.hpp"
#include "processInfo.hpp"
#include "progams.hpp"
#include <algorithm>
#include <cctype>
#include <filesystem>
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
      if (!process.getIsEnable()) {
        process.enable();
        this->enablePids.insert(pid);
        std::cout << "enable formatter for pid: " << pid << " cwd: " << cwd.string() << std::endl;
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
