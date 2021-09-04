#pragma once

#include "xhfr.hpp"
#include "sol/sol.hpp"
class Console : public xhfr::Window  {
 public:
  Console();
  virtual void onDraw() override;


  sol::state* state;

  void addTextToConsole(const std::string& text);
  void addLineToConsole(const std::string& line);
  void initState();

 private:
  bool firstFrame = true;
  std::string consoleBuffer;
  bool lineChange = false;
  size_t historyPos = 0;
  std::array<std::string, 7> unprintable = {
      "require", "=", "if ", "while ", "for ", "repeat ", "\n"};

  bool isImmediate(const std::string& line);
  const std::string& getHistory();
  std::array<std::string, 3> history = {"A", "B", "C"};
  xhfr::Image trashImg = xhfr::Image(":/res/app/icons/trash.png");
};

