#pragma once

#include "formatter.hpp"

#include <string>
#include <unordered_map>
#include <vector>
namespace option {
//
class FormatterTemplateConfig {
  public:
    FormatterTemplateConfig();
    explicit FormatterTemplateConfig(std::string path);

  private:
    std::string path_ = "~/.config/formattersTemplates";
    std::unordered_map<std::string, Formatter> formatters_;
    // std::vector<Formatter> formatters_;
};

} // namespace option
