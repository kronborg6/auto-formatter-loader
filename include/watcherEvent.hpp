#pragma once

// this need the pid
#include "formatters/config.hpp"
#include "formatters/templateLoader.hpp"
#include <filesystem>
#include <string>
#include <vector>
// void handle_event(int fd, const std::filesystem::directory_entry& entry) {
//   std::vector<char> buffer(4096);
// };

int StartListing(int fd,
                 const option::Config& config,
                 const option::TemplateLoader& templateLoader);
