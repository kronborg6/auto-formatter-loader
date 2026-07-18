#include "helper.hpp"
#include <chrono>
#include <iomanip>

std::time_t Helper::getTimeNowUtc() {
  const auto now = std::chrono::system_clock::now();
  return std::chrono::system_clock::to_time_t(now);
}

std::string Helper::getTimeNow(bool withDate) {
  const std::time_t now = getTimeNowUtc();
  std::tm utcTime{};

#ifdef _WIN32
  gmtime_s(&utcTime, &now);
#else
  gmtime_r(&now, &utcTime);
#endif

  std::ostringstream output;
  if (withDate) {
    output << std::put_time(&utcTime, "%Y-%m-%d %H:%M:%S UTC");
  } else {
    output << std::put_time(&utcTime, "%H:%M:%S UTC");
  }

  return output.str();
}

std::string Helper::getTimeNow(std::string format) {
  const std::time_t now = getTimeNowUtc();
  std::tm utcTime{};

#ifdef _WIN32
  gmtime_s(&utcTime, &now);
#else
  gmtime_r(&now, &utcTime);
#endif

  std::ostringstream output;
  output << std::put_time(&utcTime, format.c_str());

  return output.str();
}
