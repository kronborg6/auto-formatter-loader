#pragma once

#include "formatters/formatter.hpp"
#include "project_type.hpp"
#include <optional>
#include <string>

bool match_name(const std::string& pid, const std::string& target);

// not sure if it need to get a refresh of all template options or have a function that set the
// formater via a template
class ProcessInfo {
  public:
    ProcessInfo(std::string pid, std::string path);
    ProcessInfo(ProcessInfo&&) = default;
    ProcessInfo(const ProcessInfo&) = default;
    ProcessInfo& operator=(ProcessInfo&&) = default;
    ProcessInfo& operator=(const ProcessInfo&) = default;
    ~ProcessInfo() = default;

    bool deletFormater();
    bool createFormater();
    bool createFormater(std::string formaterPath);

    std::string getPid() const {
      return pid_;
    }

    std::string getPath() const {
      return path_;
    }

  private:
    std::string pid_;
    std::string path_;
    std::string file_;

    Formatter formatter_;
    std::optional<Formatter> oldFormatter_;

    bool formater_ = false;
    ProgramingLaunge type_;
};
