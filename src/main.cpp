#include <algorithm>
#include <filesystem>
#include <fstream>
// #include <iostream>
#include <print>
#include <string>

bool match_name(const std::string& pid, const std::string& target) {
  std::ifstream f("/proc/" + pid + "/comm");
  std::string name;
  std::getline(f, name);
  return name == target;
}

int main(void) {

  for (auto& e : std::filesystem::directory_iterator("/proc")) {
    if (!e.is_directory())
      continue;

    auto pid = e.path().filename().string();

    if (!std::all_of(pid.begin(), pid.end(), ::isdigit))
      continue;

    if (match_name(pid, "nvim")) {
      auto cwd = std::filesystem::read_symlink("/proc/" + pid + "/cwd");
      std::println("pid: {}, CWD: {}", pid, cwd.string());
    }
  }
  return 0;
}
