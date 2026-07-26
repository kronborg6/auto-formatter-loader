#pragma once

#include <gtest/gtest.h>

#include <chrono>
#include <filesystem>
#include <fstream>
#include <stdexcept>
#include <string>
#include <system_error>

namespace fs = std::filesystem;

class TempDirectory {
  public:
    TempDirectory() {
      const auto uniqueName =
          "template_loader_test_" +
          std::to_string(std::chrono::steady_clock::now().time_since_epoch().count());

      path_ = fs::temp_directory_path() / uniqueName;
      fs::create_directories(path_);
    }

    ~TempDirectory() {
      std::error_code error;
      fs::remove_all(path_, error);
    }

    const fs::path& path() const {
      return path_;
    }

    void createFile(const std::string& filename, const std::string& contesnts) {
      std::ofstream file(path_ / filename);

      if (!file) {
        throw std::runtime_error("Could not create test file: " + filename);
      }

      file << contesnts;
    }

  private:
    fs::path path_;
};
