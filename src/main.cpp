#include "formatters/config.hpp"
#include "formatters/templateLoader.hpp"
#include "iostream"
#include "progams.hpp"
#include "yaml-cpp/node/node.h"
#include "yaml-cpp/node/parse.h"
#include <filesystem>
#include <yaml-cpp/yaml.h>
// #include <print>
#include <string>

int main(void) {
  try {
    option::Config config = option::Config(YAML::LoadFile("/home/kronborg/.auto-formatter.yaml"));
    // YAML::Node config =
    // YAML::LoadFile("/home/kronborg/project/setup/config.yaml");
    std::cout << "Loaded config\n";
  } catch (const YAML::BadFile& e) {
    std::cerr << "Could not open config file: " << e.what() << '\n';
  }
  // YAML::Node config =
  // YAML::LoadFile("/home/kronborg/project/setup/config.yaml");

  // std::println("dev: {}", config["DEV"].as<std::string>());

  Programs progams;
  // need to make a load from config her
  // then load the templates check for args to change dir
  const option::TemplateLoader templates = option::TemplateLoader();

  // this is how we are gona check what ides that is runing need to get options
  // from config
  for (auto& e : std::filesystem::directory_iterator("/proc")) {
    progams.CreateNewFormatter(e, templates);
  }

  for (const auto& [key, x] : progams.formaters) {

    // std::println("pid: {}, CWD: {}", x.getPid(), x.getPath());
  }
  return 0;
}
