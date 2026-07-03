#pragma once

#include <string>
#include <vector>

#include "yaml-cpp/node/node.h"
#include "yaml-cpp/node/parse.h"
#include <string>
#include <vector>
#include <yaml-cpp/yaml.h>
// config is gona have a list of this then when we need a new formatter for one of thos languge we
// can use the formatter as a key for the hash_map of formatters we have
struct Language {
    std::string name;
    std::string formatter;
    std::vector<std::string> filetypes;
};

namespace YAML {
  template <> struct convert<Language> {
      static Node encode(const Language& rhs);
      static bool decode(const Node& node, Language& rhs);
  };
}; // namespace YAML
