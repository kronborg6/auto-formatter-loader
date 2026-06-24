#include "formater.hpp"
#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <iostream>

bool Formater::createFormater(std::string formaterPath) {
  if (this->formater_)
    return true;
  return true;
}

bool Formater::createFormater() {
  if (this->formater_)
    return true;
  return true;
}

bool Formater::deletFormater() {
  if (this->formater_) {
    std::string filePath = this->path_ + "" + this->file_;
    std::remove(filePath.c_str());
  } else {
    return false;
  }
}
