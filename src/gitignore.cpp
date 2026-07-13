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
  std::fstream ignore(this->path, std::ios::in | std::ios::out | std::ios::app);

  if (!ignore.is_open()) {
    return false;
  }

  std::string temp;
  // std::size_t lineNumber = 0;
  //
  // while (std::getline(ignore, temp)) {
  //   ++lineNumber;
  // }

  ignore.clear(); // clear EOF/fail state
  ignore << value << '\n';

  if (!ignore) {
    return false;
  }

  // this->line = lineNumber + 1;
  this->text = value;

  this->init = true;
  return true;
}
