#pragma once

#include <string>
#include <vector>

// config is gona have a list of this then when we need a new formatter for one of thos languge we
// can use the formatter as a key for the hash_map of formatters we have
struct Language {
    std::string name;
    std::string formatter;
    std::vector<std::string> filetypes;
};
