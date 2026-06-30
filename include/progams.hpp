#pragma once

#include "processInfo.hpp"

#include <filesystem>
#include <string>
#include <unordered_map>
#include <vector>

struct Programs {
    // std::vector<ProcessInfo> formaters;
    std::unordered_map<std::string, ProcessInfo> formaters;
    bool CreateNewFormatter(const std::filesystem::directory_entry& entry,
                            const option::TemplateLoader& templates);
};
