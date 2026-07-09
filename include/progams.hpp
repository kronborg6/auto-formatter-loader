#pragma once

#include "formatters/config.hpp"
#include "processInfo.hpp"

#include <filesystem>
#include <set>
#include <string>
#include <unordered_map>

struct Programs {
    std::unordered_map<std::string, ProcessInfo> formaters;
    std::set<std::string> enablePids;

    bool CreateNewFormatter(const std::filesystem::directory_entry& entry,
                            const option::Config& config,
                            const option::TemplateLoader& templates);

    bool CreateNewFormatter(const std::string& pid,
                            const option::Config& config,
                            const option::TemplateLoader& templates);

    bool removeFormatterViaPid(const std::string& pid);
};
