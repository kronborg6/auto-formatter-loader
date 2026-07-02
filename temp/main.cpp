#include "iostream"
#include "yaml-cpp/node/node.h"
#include "yaml-cpp/node/parse.h"
#include <string>
#include <vector>
#include <yaml-cpp/yaml.h>

#define PATH "/home/kronborg/project/setup/temp/test.yaml"

struct Language {
    std::string name;
    std::string formatter;
    std::vector<std::string> filetypes;
};

namespace YAML {
  template <> struct convert<Language> {
      static Node encode(const Language& rhs) {
        Node node;
        node["name"] = rhs.name;
        node["formatter"] = rhs.formatter;
        node["filetype"] = rhs.filetypes;
        return node;
      };
      static bool decode(const Node& node, Language& rhs) {
        if (!node.IsMap() || node.size() != 1) {
          return false;
        }

        // Each item looks like:
        //
        // - cpp:
        //     formatter: ".clang-formatter"
        //     filetype:
        //       - ".cpp"
        //
        auto it = node.begin();

        rhs.name = it->first.as<std::string>();

        YAML::Node body = it->second;

        if (!body.IsMap()) {
          return false;
        }

        if (!body["formatter"] || !body["filetype"]) {
          return false;
        }

        rhs.formatter = body["formatter"].as<std::string>();
        rhs.filetypes = body["filetype"].as<std::vector<std::string>>();

        return true;
      }
  };
}; // namespace YAML

int main(void) {

  try {
    YAML::Node config = YAML::LoadFile(PATH);
    std::vector<std::string> ide = config["IDE"].as<std::vector<std::string>>();
    std::cout << "Loaded config\n";
    for (const std::string& name : ide) {
      std::cout << "ide: " + name << std::endl;
    }
    std::vector<Language> languages = config["formatters"].as<std::vector<Language>>();

    for (const Language& lang : languages) {
      std::cout << lang.name << " -> " << lang.formatter << '\n';
    }
  } catch (const YAML::BadFile& e) {
    std::cerr << "Could not open config file: " << e.what() << '\n';
  }
  return 0;
}
