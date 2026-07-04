#include "language.hpp"
#include "yaml-cpp/node/node.h"
#include "yaml-cpp/node/parse.h"
#include <string>
#include <vector>
#include <yaml-cpp/yaml.h>

namespace YAML {

bool convert<Language>::decode(const Node& node, Language& rhs) {
  if (!node.IsMap() || node.size() != 1)
    return false;

  auto it = node.begin();

  rhs.name = it->first.as<std::string>();

  YAML::Node body = it->second;

  if (!body.IsMap())
    return false;

  if (!body["formatter"] || !body["filetypes"])
    return false;

  rhs.formatter = body["formatter"].as<std::string>();
  rhs.filetypes = body["filetypes"].as<std::vector<std::string>>();
  for (auto& filetype : rhs.filetypes) {
    if (filetype[0] == '.')
      filetype.erase(0, 1);
  }

  return true;
}
} // namespace YAML
