#include "formatters/templateLoader.hpp"
#include <cstdlib>
#include <filesystem>
#include <stdexcept>
#include <string>

namespace fs = std::filesystem;

#define DEFAULT_FORMATER_TEMPLATE_FOLDER "~/.config/formattersTemplates"

fs::path GetPath() {
  const char* home = std::getenv("HOME");
  if (!home) {
    throw std::invalid_argument("need templates path or provide a vailed path");
  }
  fs::path templateFolder = fs::path(home) / ".config" / "formattersTemplates";
  if (!fs::exists(templateFolder)) {
    throw std::invalid_argument("need templates path or provide a vailed path");
  }
  return templateFolder;
}
fs::path GetPath(std::string customerPath) {

  fs::path templateFolder = fs::path(customerPath);
  if (!fs::exists(templateFolder)) {
    throw std::invalid_argument("need templates path or provide a vailed path");
  }
  return templateFolder;
}

namespace option {
  TemplateLoader::TemplateLoader() {

    path_ = GetPath();

    for (const fs::directory_entry& entry : fs::directory_iterator(path_)) {
      if (entry.is_regular_file()) {
        fs::path filePath = entry.path();

        std::string name = filePath.filename();
        if (formatters_.contains(name)) {
          continue;
        }
        formatters_.emplace(name, Formatter(name, filePath));
      }
    }
  }

  TemplateLoader::TemplateLoader(std::string path) {

    path_ = GetPath(path);

    for (const fs::directory_entry& entry : fs::directory_iterator(path_)) {
      if (entry.is_regular_file()) {
        fs::path filePath = entry.path();

        std::string name = filePath.filename();
        if (formatters_.contains(name)) {
          continue;
        }
        formatters_.emplace(name, Formatter(name, filePath));
      }
    }
  }
} // namespace option
