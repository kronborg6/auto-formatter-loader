#pragma once

#include <ctime>
#include <string>
namespace Helper {
  std::time_t getTimeNowUtc();
  std::string getTimeNow(bool withDate = false);
  std::string getTimeNow(std::string format);
} // namespace Helper
