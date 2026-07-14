#pragma once

#include <ostream>

namespace Config {
  class Log {
    public:
      Log();
      // explicit Log(std::ostream& output) : output_(output) {};
      void log(std::ostream& output, std::string text);
      void log(std::string text);

    private:
      std::ostream& output_;
  };
} // namespace Config
