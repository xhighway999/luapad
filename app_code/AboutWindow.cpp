#include "AboutWindow.hpp"

AboutWindow::AboutWindow() {
  setTitle("About");
  // load images
  // images.reserve(frameCount);
  for (size_t i = 0; i < frameCount; ++i) {
    std::string path = ":/res/texgen/xhfr/";

    char s[4];
    sprintf(s, "%03lu", i + 1);
    path += s;
    path += ".png";

    images.emplace_back(path.c_str());
  }
  setColor(ImGuiCol_WindowBg, ImVec4(0, 0, 0, 1.0));
  texgenlogo.loadImageFromFile((":/res/texgen/logos/texgen.png"));
}

void AboutWindow::onDraw() {
  ImGui::PushTextWrapPos(800);
  ImGui::SetCursorPosX((ImGui::GetWindowWidth() - 400) * 0.5);
  ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(0, 0));
  auto centeredText = [](std::string str) {
    std::vector<size_t> newLines;
    newLines.push_back(0);
    // find where newlines are
    for (size_t i = 0; i < str.size(); ++i) {
      if (str[i] == '\n') {
        newLines.emplace_back(i);
      }
    }
    // render every item
    for (size_t i = 0; i < newLines.size() - 1; ++i) {
      size_t start = newLines[i];
      size_t end = newLines[i + 1];
      float width = ImGui::CalcTextSize(str.data() + start, str.data() + end).x;
      ImGui::SetCursorPosX((ImGui::GetWindowWidth() - width) * 0.5);
      ImGui::TextUnformatted(str.data() + start, str.data() + end);
    }
  };
  ImGui::PopStyleVar();

  ImGui::SetCursorPosX((ImGui::GetWindowWidth() - 400) * 0.5);
  ImGui::Image(texgenlogo.textureID(), ImVec2(400, 160));

  centeredText(
      "Based on XHFR public branch (CLANG / GCC 64 bit)\n"
      "Copyright 2020 Quentin Kammann \n"
      "Redistribution and use in source and binary forms,\n"
      "with or without modification, are permitted.\n"
      "THIS SOFTWARE IS PROVIDED 'AS-IS',\n"
      "WITHOUT ANY EXPRESS OR IMPLIED WARRANTY.\n"
      "IN NO EVENT WILL THE AUTHORS BE HELD LIABLE\n"
      "FOR ANY DAMAGES ARISING FROM THE USE OF THIS SOFTWARE.\n");

  // ImGui::Text();

  // ImGui::SetCursorPos((GetWindowSize() - image_size) * 0.5f);

  ImGui::SetCursorPosX((ImGui::GetWindowWidth() - 400) * 0.5);
  ImGui::Image(images[counter++].textureID(), ImVec2(400, 128));
  if (counter == frameCount) {
    counter = 0;
  }
  ImGui::SetCursorPosX((ImGui::GetWindowWidth() - 100) * 0.5);
  if (ImGui::Button("Close", ImVec2(100, 0))) {
    setVisible(false);
  }
}
