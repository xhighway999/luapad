#include "ToolBar.hpp"
#include "SDL.h"


ToolBar::ToolBar()
{
    setTitle("ToolBar");
}

void ToolBar::onDraw()
{


    float iconSize = ImGui::GetFrameHeight();
    if (ImGui::ImageButton(trashImg.textureID(), ImVec2(iconSize, iconSize),
                           ImVec2(), ImVec2(1, 1), 0)) {
        runHandler();
    }

    if (ImGui::IsItemHovered()) {
        ImGui::SetTooltip("Or press CTRL + Enter");
    }
    ImGui::SameLine();
    if (ImGui::Button("Clear Lua state")) {
        clearStateHandler();
    }
    ImGui::SameLine();
    ImGui::Text("LuaPad v0.5.1");
    ImColor link_color(255,0,0);



    ImGui::SameLine();
    ImGui::Link("www.coffeecupentertainment.com","https://www.coffeecupentertainment.com",ImColor(89,179,255));
    ImGui::SameLine();
    ImGui::Link("Github Repo","https://github.com/xhighway999/luapad",ImColor(89,179,255));


}
