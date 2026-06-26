#include "stringHelper.hpp"
#include <string>
#include <vector>

std::vector<std::string> split(std::string s, const std::string& delimiter) {
  std::vector<std::string> tokns;
  size_t pos = 0;
  std::string token;

  while ((pos = s.find(delimiter)) != std::string::npos) {
    token = s.substr(0, pos);
    tokns.push_back(token);
    s.erase(0, pos + delimiter.length());
  }
  tokns.push_back(s);

  return tokns;
}
