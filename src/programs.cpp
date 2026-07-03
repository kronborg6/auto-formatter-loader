#include "formatters/templateLoader.hpp"
#include "progams.hpp"
#include <algorithm>
#include <cctype>
#include <filesystem>

bool Programs::CreateNewFormatter(const std::filesystem::directory_entry &entry,
                                  const option::TemplateLoader &templates) {
  if (!entry.is_directory())
    return false;

  auto pid = entry.path().filename().string();

  if (!std::all_of(pid.begin(), pid.end(), ::isdigit))
    return false;

  if (match_name(pid, "nvim")) {
    auto cwd = std::filesystem::read_symlink("/proc/" + pid + "/cwd");
    ProcessInfo process = ProcessInfo(pid, cwd.string(), templates);

    if (!formaters.contains(cwd.string())) {
      formaters.emplace(cwd.string(), process);
      process.enable();
    }
  }
  return false;
}
