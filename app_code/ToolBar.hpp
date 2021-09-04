#pragma once

#include "xhfr.hpp"

class ToolBar : public xhfr::Window {
 public:
    ToolBar();
  virtual void onDraw();
  virtual void onClosePressed() { setVisible(false); }
std::function<void()> runHandler;
std::function<void()> clearStateHandler;
 private:

xhfr::Image trashImg = xhfr::Image(":/res/app/icons/play.png");
};
