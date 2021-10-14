#include "ToolBar.hpp"
#include "SDL.h"

ToolBar::ToolBar() {
  setTitle("ToolBar");
}

void ToolBar::onDraw() {
  float iconSize = ImGui::GetFrameHeight();

  if (running) {
      if (ImGui::Button("Program running ...",ImVec2(0,iconSize))) {

      }
  }
  else {
      if (ImGui::ImageButton(trashImg.textureID(), ImVec2(iconSize, iconSize),
                             ImVec2(), ImVec2(1, 1), 0)) {
        runHandler();
      }
  }



  if (ImGui::IsItemHovered()) {
    ImGui::SetTooltip("Or press CTRL + Enter");
  }
  ImGui::SameLine();
  if (ImGui::Button("Clear Lua state")) {
    clearStateHandler();
  }
  ImGui::SameLine();
  ImGui::Text("LuaPad v0.9.1");
  ImColor link_color(255, 0, 0);

  ImGui::SameLine();
  ImGui::Link("www.coffeecupentertainment.com",
              "https://www.coffeecupentertainment.com", ImColor(89, 179, 255));
  ImGui::SameLine();
  ImGui::Link("Github Repo", "https://github.com/xhighway999/luapad",
              ImColor(89, 179, 255));


  auto w = ImGui::GetContentRegionAvailWidth();

  ImGui::SameLine(w - iconSize);



  if (ImGui::ImageButton(settingsImg.textureID(),ImVec2(iconSize,iconSize),ImVec2(),ImVec2(1,1),0)) {
    ImGui::OpenPopup("SETTINGS");
  }

  static bool lightTheme = as.value("/gui/useLightTheme",false);
  static bool useLightThemeFirst = true;
  if (lightTheme && useLightThemeFirst) {
      useLightThemeFirst = false;
      changeColorHandler(!lightTheme);
    if (lightTheme) {
      ImGui::StyleColorsLight();
    }

  }
  if (ImGui::BeginPopup("SETTINGS")) {
      bool lightTheme = as.value("/gui/useLightTheme",false);
      ImGui::Checkbox("Use light theme",&lightTheme);
      as.setValue("/gui/useLightTheme",lightTheme);
        xhfr::styles::StyleDefault();

        changeColorHandler(!lightTheme);
      if (lightTheme) {
        ImGui::StyleColorsLight();
      }
      ImGui::EndPopup();
  }

}

void ToolBar::setRunning(bool newRunning)
{
    running = newRunning;
}
