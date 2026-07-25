#include <gtest/gtest.h>

#include "formatters/templateLoader.hpp"
#include "processInfo.hpp"

#include <chrono>
#include <filesystem>
#include <fstream>
#include <memory>
#include <string>

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

namespace fs = std::filesystem;

class ProcessInfoTest : public ::testing::Test {
  protected:
    void SetUp() override {
      testDirectory = fs::temp_directory_path() /
                      ("setup_process_info_test_" +
                       std::to_string(std::chrono::steady_clock::now().time_since_epoch().count()));

      fs::create_directories(testDirectory);

      // Construct these according to their actual constructors.
      config = std::make_unique<option::Config>();
      templates = std::make_unique<option::TemplateLoader>();

      process = std::make_unique<ProcessInfo>("1234", testDirectory.string(), *config, *templates);
    }

    void TearDown() override {
      process.reset();
      templates.reset();
      config.reset();

      std::error_code error;
      fs::remove_all(testDirectory, error);
    }

    fs::path testDirectory;

    std::unique_ptr<option::Config> config;
    std::unique_ptr<option::TemplateLoader> templates;
    std::unique_ptr<ProcessInfo> process;
};
class ProcessInfoEnableTest : public ::testing::Test {
  protected:
    void SetUp() override {
      const auto uniqueId = std::chrono::steady_clock::now().time_since_epoch().count();

      rootDirectory = fs::temp_directory_path() / ("setup_test_" + std::to_string(uniqueId));

      projectDirectory = rootDirectory / "project";
      templateDirectory = rootDirectory / "templates";

      fs::create_directories(projectDirectory);
      fs::create_directories(templateDirectory);

      formatterTemplatePath = templateDirectory / ".clang-format";

      std::ofstream formatterFile(formatterTemplatePath);
      formatterFile << "BasedOnStyle: LLVM\n";
    }

    void TearDown() override {
      std::error_code error;
      fs::remove_all(rootDirectory, error);
    }
    option::TemplateLoader makeTemplateLoader(const fs::path& templatePath) {
      Formatter formatter;
      formatter.filename = ".clang-format";
      formatter.filePath = templatePath;

      return option::TemplateLoader(templatePath);
    }

    fs::path rootDirectory;
    fs::path projectDirectory;
    fs::path templateDirectory;
    fs::path formatterTemplatePath;
};
class TemplateEnableTest : public ::testing::Test {
  protected:
    void SetUp() override {

      const auto uniqueId = std::chrono::steady_clock::now().time_since_epoch().count();

      templateDirectory = fs::temp_directory_path() / ("setup_test_" + std::to_string(uniqueId));
      fs::create_directory(templateDirectory);
      // process = std::make_unique<ProcessInfo>("1234", testDirectory.string(), *config,
      // *templates);

      Formatter formatter;
      formatter.filename = ".clang-format";
      formatter.filePath = templateDirectory / "kronborg";

      template_ = std::make_unique<option::TemplateLoader>(templateDirectory);
      // template_.
    }

    void TearDown() override {
      std::error_code error;
      template_.reset();
      // fs::remove_all(rootDirectory, error);
    }
    option::TemplateLoader makeTemplateLoader(const fs::path& templatePath) {
      Formatter formatter;
      formatter.filename = ".clang-format";
      formatter.filePath = templatePath;

      return option::TemplateLoader(templatePath);
    }

    fs::path templateDirectory;
    std::string path_;
    std::unordered_map<std::string, Formatter> formatters_;
    std::unique_ptr<option::TemplateLoader> template_;
};
TEST_F(ProcessInfoTest, ContainsInitialPid) {
  EXPECT_TRUE(process->containPid("1234"));
}

TEST_F(ProcessInfoTest, DoesNotContainUnknownPid) {
  EXPECT_FALSE(process->containPid("9999"));
}

TEST_F(ProcessInfoTest, InsertsPid) {
  process->insert("5678");

  EXPECT_TRUE(process->containPid("5678"));
}

TEST_F(ProcessInfoTest, DuplicatePidIsStoredOnlyOnce) {
  process->insert("1234");

  const auto pids = process->getPids();

  EXPECT_EQ(pids.size(), 1U);
}

TEST_F(ProcessInfoTest, ReturnsConfiguredPath) {
  EXPECT_EQ(process->getPath(), testDirectory.string());
}

TEST_F(ProcessInfoTest, StartsDisabled) {
  EXPECT_FALSE(process->getIsEnable());
}

TEST_F(ProcessInfoEnableTest, DoesNothingWithoutSelectedTemplate) {
  option::Config config(node);
  option::TemplateLoader templates{/* required arguments */};

  ProcessInfo process("1234", projectDirectory.string(), config, templates);

  process.enable();

  EXPECT_FALSE(process.getIsEnable());
}

TEST_F(ProcessInfoTest, StartsWithoutGitignore) {
  EXPECT_FALSE(process->hasGitignore());
}
