#include "iostream"
#include "yaml-cpp/node/node.h"
#include "yaml-cpp/node/parse.h"
#include <string>
#include <vector>
#include <yaml-cpp/yaml.h>

#define PATH "/home/kronborg/project/setup/temp/test.yaml"

int main(void) {

  try {
    YAML::Node config = YAML::LoadFile(PATH);
    std::vector<std::string> ide = config["IDE"].as<std::vector<std::string>>();
    std::cout << "Loaded config\n";
    for (const std::string& name : ide) {
      std::cout << "ide: " + name << std::endl;
    }
  } catch (const YAML::BadFile& e) {
    std::cerr << "Could not open config file: " << e.what() << '\n';
  }
  return 0;
}
