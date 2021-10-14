#pragma once

#include "xhfr.hpp"

class ToolBar : public xhfr::Window {
 public:
  ToolBar();
  virtual void onDraw();
  virtual void onClosePressed() { setVisible(false); }
  std::function<void()> runHandler;
  std::function<void()> clearStateHandler;
  std::function<void(bool useDark)> changeColorHandler;
  //std::function<void()> openSettingsHandler;

  void setRunning(bool newRunning);



private:
  bool running = false;
  xhfr::ApplicationSettings as;
  xhfr::Image trashImg = xhfr::Image(":/res/app/icons/play.png");
  xhfr::Image settingsImg = xhfr::Image(":/res/app/icons/gear.png");
};
