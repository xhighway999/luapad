#pragma once

#include "xhfr.hpp"

class ZepWindow : public xhfr::Window {
 public:
  ZepWindow();
  virtual void onDraw();
  virtual void onClosePressed() { setVisible(false); }

 private:
};
