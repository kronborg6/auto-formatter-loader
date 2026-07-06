#include "formatters/config.hpp"
#include "formatters/templateLoader.hpp"
#include "iostream"
#include "progams.hpp"
#include "watcherEvent.hpp"
#include "yaml-cpp/node/node.h"
#include "yaml-cpp/node/parse.h"
#include <cctype>
#include <cerrno>
#include <chrono>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <filesystem>
#include <ranges>
#include <set>
#include <string>
#include <sys/inotify.h>
#include <sys/poll.h>
#include <thread>
#include <unistd.h>
#include <utility>
#include <vector>
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

int main(void) {
  option::Config config = option::Config(YAML::LoadFile("/home/kronborg/.auto-formatter.yaml"));

  Programs progams;
  // need to make a load from config her
  // then load the templates check for args to change dir
  const option::TemplateLoader templates = option::TemplateLoader();

  // this is how we are gona check what ides that is runing need to get options
  // from config
  // auto temp = std::filesystem::directory_iterator("/proc");
  // for (auto& e : std::filesystem::directory_iterator("/proc")) {
  //   if (!is_pid_dir(e))
  //     continue;
  //   progams.CreateNewFormatter(e, config, templates);
  // }

  std::set<std::string> pids;
  // std::set<std::string> pids = get_pids();
  for (;;) {
    std::this_thread::sleep_for(std::chrono::seconds(3));

    std::set<std::string> new_pids = get_pids();
    for (const std::string& pid : new_pids) {
      if (!progams.enablePids.contains(pid))
        progams.CreateNewFormatter(pid, config, templates);
    }
    for (const std::string& pid : progams.enablePids) {
      if (!pids.contains(pid)) {
        // remove it
        progams.formaters.erase(pid);
      }
    }
    pids = std::move(progams.enablePids);
  }

  for (const auto& x : progams.formaters | std::views::values) {

    std::cout << "pid: " << x.getPid() << "CWD: " << x.getPath() << std::endl;

    // std::println("pid: {}, CWD: {}", x.getPid(), x.getPath());
  }
  return 0;
}

// int main(void) {
//   option::Config config = option::Config(YAML::LoadFile("/home/kronborg/.auto-formatter.yaml"));
//
//   Programs progams;
//   // need to make a load from config her
//   // then load the templates check for args to change dir
//   const option::TemplateLoader templates = option::TemplateLoader();
//
//   // this is how we are gona check what ides that is runing need to get options
//   // from config
//   char buf;
//   int fd, poll_num;
//   int wd;
//   struct pollfd fds[2];
//   nfds_t nfds;
//
//   fd = inotify_init1(IN_NONBLOCK);
//
//   if (fd == -1) {
//     perror("inotify_init1");
//     exit(EXIT_FAILURE);
//   }
//
//   wd = inotify_add_watch(fd, "/proc", IN_CREATE | IN_DELETE | IN_MOVED_TO);
//   // wd = inotify_add_watch(fd, "/home/kronborg/project/setup/ideas", IN_CREATE | IN_DELETE);
//
//   if (wd == -1) {
//     std::cout << "failed to create watch " << strerror(errno);
//     exit(EXIT_FAILURE);
//   }
//
//   nfds = 2;
//
//   fds[0].fd = STDIN_FILENO;
//   fds[0].events = POLLIN;
//
//   fds[1].fd = fd;
//   fds[1].events = POLLIN;
//
//   std::cout << "Listening for events." << std::endl;
//
//   for (;;) {
//     poll_num = poll(fds, nfds, -1);
//
//     if (poll_num == -1) {
//       if (errno == EINTR)
//         continue;
//       perror("poll");
//       exit(EXIT_FAILURE);
//     }
//
//     if (poll_num > 0) {
//       if (fds[0].revents & POLLIN) {
//         while (read(STDIN_FILENO, &buf, 1) > 0 && buf != '\n')
//           continue;
//         break;
//       }
//
//       if (fds[1].revents & POLLIN) {
//         StartListing(fd, config, templates);
//       }
//     }
//   }
//
//   std::cout << "stoped" << std::endl;
//
//   close(fd);
//
//   return 0;
// }
