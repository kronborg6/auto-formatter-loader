#include <gtest/gtest.h>

#include "formatters/config.hpp"
#include "yaml-cpp/node/node.h"
#include <yaml-cpp/yaml.h>

const YAML::Node node = YAML::Load(R"(
IDE:
  - "nvim"
  - "code"

# Optional. Default: true
overrideFormatter: true

# Optional. Default: true
addToGitIgnore: true

# Optional. Default: 3
depth: 3

# Optional. Default: 2
logLvl: 2
# Optional. Default: "~/.config/autoFormatter/logs"
logPath: "~/.config/autoFormatter/logs"

# Optional. Default: [".git", "build", "target"]
excludeFolders:
  - ".git"
  - "build"
  - "target"
  - "extern"

formatters:
  - cpp:
      formatter: ".clang-format"
      filetypes:
        - ".cpp"
        - ".hpp"
        - ".h"
  - c:
      formatter: ".clang-format"
      filetypes:
        - ".c"
        - ".h"
  - rust:
      formatter: ".rustfmt.toml"
      filetypes:
        - ".rs"
  - odin:
      formatter: "odinfmt.json"
      filetypes:
        - ".odin"
  - Csharp:
      formatter: ".editorconfig"
      filetypes:
        - ".cs"
)");

TEST(ConfigTest, load_config) {
  EXPECT_EQ(1, 1);
}

TEST(ConfigTest, FindsLanguageByName) {

  const option::Config config(node);

  const auto language = config.findLanugeByFileType("cpp");

  ASSERT_TRUE(language.has_value());
  EXPECT_EQ(language->name, "cpp");
}
