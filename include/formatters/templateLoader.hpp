#pragma once

#include "formatter.hpp"

#include <optional>
#include <string>
#include <unordered_map>

namespace option {
  class TemplateLoader {
    public:
      TemplateLoader();
      explicit TemplateLoader(std::string path);

      // Formatter getFormatter(std::string key) const {
      //   return formatters_.at(key);
      // }
      const Formatter* getFormatter(const std::string& key) const {
        auto it = formatters_.find(key);
        if (it != formatters_.end()) {
          return &it->second;
        }
        return nullptr;
      }

      const std::unordered_map<std::string, Formatter> GetFormatters() const {
        return formatters_;
      }

    private:
      std::string path_;
      std::unordered_map<std::string, Formatter> formatters_;
  };

  class FormatterConfig {};

} // namespace option
