#pragma once

#include "formatters/config.hpp"
#include "formatters/formatter.hpp"
#include "formatters/templateLoader.hpp"
#include "gitignore.hpp"
#include <algorithm>
#include <iterator>
#include <optional>
#include <sstream>
#include <string>

bool match_name(const std::string& pid, const std::string& target);
bool match_name(const std::string& pid, const std::set<std::string>& target);

// not sure if it need to get a refresh of all template options or have a function that set the
// formater via a template
class ProcessInfo {
  public:
    ProcessInfo(std::string pid,
                std::string path,
                const option::Config& config,
                const option::TemplateLoader& templates);
    ProcessInfo(ProcessInfo&& other) noexcept
        : pids_(std::move(other.pids_)), path_(std::move(other.path_)),
          file_(std::move(other.file_)), formatter_(std::move(other.formatter_)),
          formatterTemplate_(std::move(other.formatterTemplate_)),
          oldFormatter_(std::move(other.oldFormatter_)), isEnable_(other.isEnable_),
          type_(std::move(other.type_)) {
      other.isEnable_ = false;
    }

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

    std::set<std::string> getPids() const {
      return pids_;
    }

    const std::string print() const {
      std::ostringstream steam;
      std::copy(pids_.begin(), pids_.end(), std::ostream_iterator<std::string>(steam, ", "));
      return steam.str();
    }

    std::string getPath() const {
      return path_;
    }
    bool containPid(const std::string& pid) const {
      if (pids_.contains(pid))
        return true;
      return false;
    }

    void insert(std::string pid) {
      pids_.insert(pid);
    }

    bool getIsEnable() const {
      return isEnable_;
    }

    void enable();

  private:
    std::set<std::string> pids_;
    std::string path_;
    std::string file_;

    Formatter formatter_;
    const Formatter* formatterTemplate_ = nullptr;
    std::optional<Formatter> oldFormatter_;
    std::optional<Gitignore> gitingore_;

    bool formater_ = false;
    bool isEnable_ = false;
    std::string type_;
    // ProgramingLaunge type_;
};
