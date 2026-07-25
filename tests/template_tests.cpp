#include <gtest/gtest.h>

#include "formatters/templateLoader.hpp"
#include "processInfo.hpp"

#include <chrono>
#include <filesystem>
#include <fstream>
#include <memory>
#include <string>

namespace fs = std::filesystem;

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
