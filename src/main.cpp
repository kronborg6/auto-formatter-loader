#include "formatters/templateLoader.hpp"
#include "processInfo.hpp"
#include "progams.hpp"
#include <algorithm>
#include <filesystem>
#include <print>
#include <string>

int main(void) {

  Programs progams;
  // need to make a load from config her
  // then load the templates check for args to change dir
  option::TemplateLoader templates = option::TemplateLoader();

  // this is how we are gona check what ides that is runing need to get options from config
  for (auto& e : std::filesystem::directory_iterator("/proc")) {
    if (!e.is_directory())
      continue;

    auto pid = e.path().filename().string();

    if (!std::all_of(pid.begin(), pid.end(), ::isdigit))
      continue;

    if (match_name(pid, "nvim")) {
      auto cwd = std::filesystem::read_symlink("/proc/" + pid + "/cwd");
      ProcessInfo process = ProcessInfo(pid, cwd.string());

      progams.formaters.push_back(process);
    }
  }

  for (ProcessInfo& x : progams.formaters) {

    std::println("pid: {}, CWD: {}", x.getPid(), x.getPath());
  }
  return 0;
}
