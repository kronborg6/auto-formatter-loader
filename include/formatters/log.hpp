#pragma once

#include <ostream>
#include <string_view>

namespace Config {
  class Log {
    public:
      Log();
      // explicit Log(std::ostream& output) : output_(output) {};
      void write(std::ostream& output, std::string_view text);
      void write(std::string_view text);

    private:
      std::ostream& output_;
  };
} // namespace Config
