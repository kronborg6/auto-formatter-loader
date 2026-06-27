#include "config.hpp"
#include "formatter.hpp"
#include <cstdlib>
#include <filesystem>
#include <iostream>
#include <stdexcept>
#include <string>

namespace fs = std::filesystem;

#define DEFAULT_FORMATER_TEMPLATE_FOLDER "~/.config/formattersTemplates"

namespace option {
  FormatterTemplateConfig::FormatterTemplateConfig() {
    const char* home = std::getenv("HOME");
    if (!home) {
      throw std::invalid_argument("need templates path or provide a vailed path");
    }
    fs::path templateFolder = fs::path(home) / ".config" / "formattersTemplates";
    if (!fs::exists(templateFolder)) {
      throw std::invalid_argument("need templates path or provide a vailed path");
    }

    for (const fs::directory_entry& entry : fs::directory_iterator(templateFolder)) {
      if (entry.is_regular_file()) {
        fs::path filePath = entry.path();

        std::cout << "file: " << filePath << '\n';
        std::cout << "filename: " << filePath.filename() << '\n';
        std::cout << "extension: " << filePath.extension() << '\n';

        std::string name = filePath.filename();
        if (formatters_.contains(name)) {
          continue;
        }
        formatters_.emplace(name, Formatter(name, filePath));
      }
    }
  }
} // namespace option
