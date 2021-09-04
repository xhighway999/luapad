#pragma once

#include "xhfr.hpp"

#include "AboutWindow.hpp"
#include "TinyIDE.hpp"
#include "ToolBar.hpp"
#include "sol/sol.hpp"
#include "Console.hpp"

class App {
 public:
  App();
  void init(int argc, char* argv[], const char* appName, int w, int h);
  std::shared_ptr<TinyIDE> zw;
  std::shared_ptr<ToolBar> toolBar;
  std::shared_ptr<Console> console;
  sol::state luaState;
};
