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
  ImGui::Text("LuaPad v0.10.0");
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
  static float fontScale = as.value("/gui/fontScale", 1.0f);
  static bool firstLoad = true;
  if ( firstLoad) {
      firstLoad = false;
      if (lightTheme) {
          changeColorHandler(!lightTheme);
        if (lightTheme) {
          ImGui::StyleColorsLight();
        }
      }

      auto& io = ImGui::GetIO();
      io.FontGlobalScale = fontScale;



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

      if (ImGui::SliderFloat("Font Scale",&fontScale,0.5,4)) {
          as.setValue("/gui/fontScale",fontScale);

          auto& io = ImGui::GetIO();
          io.FontGlobalScale = fontScale;

      }

      ImGui::EndPopup();
  }

}

void ToolBar::setRunning(bool newRunning)
{
    running = newRunning;
}
