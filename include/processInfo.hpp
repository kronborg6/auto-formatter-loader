#pragma once

#include "filesystem"
#include "formatters/config.hpp"
#include "formatters/formatter.hpp"
#include "formatters/templateLoader.hpp"
#include "project_type.hpp"
#include <memory>
#include <optional>
#include <string>
#include <unordered_map>

bool match_name(const std::string& pid, const std::string& target);

// not sure if it need to get a refresh of all template options or have a function that set the
// formater via a template
class ProcessInfo {
  public:
    ProcessInfo(std::string pid,
                std::string path,
                const option::Config& config,
                const option::TemplateLoader& templates);
    // ProcessInfo(ProcessInfo&&) = default;
    // ProcessInfo(const ProcessInfo&) = default;
    // ProcessInfo& operator=(ProcessInfo&&) = default;
    // ProcessInfo& operator=(const ProcessInfo&) = default;
    //
    // need to change this from defualt to a function that clean op the systemlink, restore if a old
    // formater existen and undo if we make change to .gitignore
    // ~ProcessInfo() = default;
    ~ProcessInfo();

    bool deletFormater();
    bool createFormater();
    bool createFormater(std::string formaterPath);

    std::string getPid() const {
      return pid_;
    }

    std::string getPath() const {
      return path_;
    }

    void enable();

  private:
    std::string pid_;
    std::string path_;
    std::string file_;

    Formatter formatter_;
    const Formatter* formatterTemplate_ = nullptr;
    std::optional<Formatter> oldFormatter_;

    bool formater_ = false;
    bool isEnable_ = false;
    std::string type_;
    // ProgramingLaunge type_;
};
