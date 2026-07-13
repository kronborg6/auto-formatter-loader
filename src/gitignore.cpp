#include "gitignore.hpp"
#include <cstddef>
#include <filesystem>
#include <fstream>
#include <ios>
#include <string>

bool Gitignore::removeFromGitignore() {
  if (this->init) {
    const std::string filename = this->path;
    std::filesystem::path tempFile = this->path;
    tempFile += ".temp";

    std::ifstream input(filename);
    std::ofstream output(tempFile);

    std::string line;
    while (std::getline(input, line)) {
      bool removeThisLine = (line == this->text);

      if (!removeThisLine) {
        output << line << '\n';
      }
    }

    input.close();
    output.close();

    std::remove(filename.c_str());
    std::rename(tempFile.c_str(), filename.c_str());
  }
  return false;
}

bool Gitignore::addToGitignore(const std::string& value) {

  std::ifstream input(this->path);

  std::string temp;

  if (!input.is_open()) {
    return false;
  }

  while (std::getline(input, temp)) {
    if (value == temp) {
      this->init = false;
      this->text = value;
      return true;
    }
  }
  input.close();

  std::ofstream output(this->path, std::ios::app);

  if (!output.is_open()) {
    return false;
  }
  output << value << '\n';

  if (!output) {
    return false;
  }

  this->text = value;
  this->init = true;

  return true;
}
