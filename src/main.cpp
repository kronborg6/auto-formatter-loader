#include "formatters/config.hpp"
#include "formatters/templateLoader.hpp"
#include "iostream"
#include "progams.hpp"
#include "yaml-cpp/node/node.h"
#include "yaml-cpp/node/parse.h"
#include <filesystem>
#include <ranges>
#include <string>
#include <yaml-cpp/yaml.h>

int main(void) {
  option::Config config = option::Config(YAML::LoadFile("/home/kronborg/.auto-formatter.yaml"));

  Programs progams;
  // need to make a load from config her
  // then load the templates check for args to change dir
  const option::TemplateLoader templates = option::TemplateLoader();

  // this is how we are gona check what ides that is runing need to get options
  // from config
  auto temp = std::filesystem::directory_iterator("/proc");
  for (auto& e : std::filesystem::directory_iterator("/proc")) {
    progams.CreateNewFormatter(e, config, templates);
  }

  for (const auto& x : progams.formaters | std::views::values) {

    std::cout << "pid: " << x.getPid() << "CWD: " << x.getPath() << std::endl;

    // std::println("pid: {}, CWD: {}", x.getPid(), x.getPath());
  }
  return 0;
}
