

#include "watcherEvent.hpp"
#include "formatters/config.hpp"
#include "formatters/templateLoader.hpp"
#include <cerrno>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <memory>
#include <string>
#include <sys/inotify.h>
#include <sys/types.h>
#include <unistd.h>
#include <vector>

std::string testHelper(uint32_t mask) {
  switch (mask & (IN_CREATE | IN_DELETE | IN_MOVED_TO)) {
  case IN_CREATE:
    return "created a new ";
  case IN_DELETE:
    return "deleted a ";
  case IN_MOVED_TO:
    return "move a ";
  defualt:
    return "undifind cruse of action";
  }
}

int StartListing(int fd,
                 const option::Config& config,
                 const option::TemplateLoader& templateLoader) {
  // return 0;

  std::vector<char> buffer(4096);
  const struct inotify_event* event;
  ssize_t size;

  for (;;) {

    size = read(fd, buffer.data(), buffer.size());
    if (size == -1 && errno != EAGAIN) {
      perror("read");
      exit(EXIT_FAILURE);
    }

    if (size <= 0)
      break;

    // size_t i = 0;
    // while (i < size) {
    for (ssize_t i = 0; i < size; i += sizeof(inotify_event) + event->len) {
      event = reinterpret_cast<inotify_event*>(&buffer[i]);

      // switch (event->mask & (IN_CREATE | IN_DELETE)) {
      // case IN_CREATE:
      //   std::cout << "create new: " << std::endl;
      // case IN_DELETE:
      //   std::cout << "delete: " << std::endl;
      // }

      if (event->len)
        std::cout << testHelper(event->mask)
                  << (event->mask & IN_ISDIR ? "[directory] " : "[file] ")
                  << "named: " << event->name << std::endl;
    }
  }
  return 0;
}
