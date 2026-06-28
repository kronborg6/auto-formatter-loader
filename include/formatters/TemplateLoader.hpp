
#pragma once

#include "formatter.hpp"

#include <string>
#include <unordered_map>

namespace option {
  class TemplateLoader {
    public:
      TemplateLoader();
      explicit TemplateLoader(std::string path);

    private:
      std::string path_;
      std::unordered_map<std::string, Formatter> formatters_;
  };

  class FormatterConfig {};

} // namespace option
