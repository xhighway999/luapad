#pragma once

#include "xhfr.hpp"

class AboutWindow : public xhfr::Window {
 public:
  AboutWindow();
  virtual void onDraw();
  virtual void onClosePressed() { setVisible(false); }

 private:
  const size_t frameCount = 115;
  size_t counter = 0;
  std::vector<xhfr::Image> images;
  xhfr::Image texgenlogo;
};
