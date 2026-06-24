#pragma once

#include "project_type.hpp"
#include <string>
class Formater {
  public:
    Formater(std::string pid, std::string path) : pid_(pid), path_(path) {
    }
    Formater(Formater&&) = default;
    Formater(const Formater&) = default;
    Formater& operator=(Formater&&) = default;
    Formater& operator=(const Formater&) = default;
    ~Formater() = default;

    bool deletFormater();
    bool createFormater();
    bool createFormater(std::string formaterPath);

  private:
    std::string pid_;
    std::string path_;
    std::string file_;
    bool formater_ = false;
    ProgramingLaunge type;
};
