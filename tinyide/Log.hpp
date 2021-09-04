#ifndef LOG_HPP
#define LOG_HPP

#include "xhfr.hpp"

#include "core/debug.hpp"

class Log : public xhfr::Window {
 public:
  Log();
  void addLogEntry(const std::string& str);
  void onDraw() override;

 private:
  std::vector<std::string> logMessages;
};

#endif  // LOG_HPP
