#pragma once

#include "formatters/config.hpp"
#include "processInfo.hpp"

#include <filesystem>
#include <string>
#include <unordered_map>

struct Programs {
    std::unordered_map<std::string, ProcessInfo> formaters;

    bool CreateNewFormatter(const std::filesystem::directory_entry& entry,
                            const option::Config& config,
                            const option::TemplateLoader& templates);
};
