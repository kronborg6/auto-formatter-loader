#pragma once

#include <ctime>
#include <ostream>
#include <string>
#include <string_view>

namespace Config {

  class Log {
    public:
      Log();
      Log(std::ostream& config);
      // explicit Log(std::ostream& output) : output_(output) {};
      void write(std::ostream& output, std::string_view text);
      void write(std::string_view text);
      std::time_t getTimeNowUtc();
      std::string getTimeNow(bool withDate = false);
      std::string getTimeNow(std::string format);

    private:
      std::ostream& output_;
  };
} // namespace Config
