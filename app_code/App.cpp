#include "App.hpp"
#ifdef EMSCRIPTEN
#include "core/EmscriptenExtentions.hpp"
#endif
#include "../data.c"

void setupRetroTheme() {
  ImGuiStyle& mStyle = ImGui::GetStyle();
  mStyle.WindowMinSize = ImVec2(160, 20);
  mStyle.FramePadding = ImVec2(5, 4);
  mStyle.WindowPadding = ImVec2(10, 10);
  mStyle.ItemSpacing = ImVec2(5, 4);
  mStyle.FrameRounding = 3.0f;
  mStyle.IndentSpacing = 16.0f;
  mStyle.GrabRounding = 3.0f;
  mStyle.ScrollbarSize = 12.0f;
  mStyle.ScrollbarRounding = 3.0f;

  ImGuiStyle* style = &ImGui::GetStyle();
  ImVec4* colors = style->Colors;
  colors[ImGuiCol_Text] = ImVec4(0.00f, 1.00f, 0.00f, 1.00f);
  colors[ImGuiCol_TextDisabled] = ImVec4(0.00f, 0.50f, 0.00f, 1.00f);
  colors[ImGuiCol_WindowBg] = ImVec4(0.00f, 0.00f, 0.00f, 0.94f);
  colors[ImGuiCol_ChildBg] = ImVec4(0.00f, 1.00f, 0.00f, 0.00f);
  colors[ImGuiCol_PopupBg] = ImVec4(0.00f, 0.00f, 0.00f, 0.94f);
  colors[ImGuiCol_Border] = ImVec4(0.00f, 0.43f, 0.00f, 1.00f);
  colors[ImGuiCol_BorderShadow] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
  colors[ImGuiCol_FrameBg] = ImVec4(0.00f, 0.00f, 0.00f, 0.56f);
  colors[ImGuiCol_FrameBgHovered] = ImVec4(0.00f, 0.32f, 0.00f, 0.41f);
  colors[ImGuiCol_FrameBgActive] = ImVec4(0.00f, 0.16f, 0.00f, 0.67f);
  colors[ImGuiCol_TitleBg] = ImVec4(0.00f, 0.00f, 0.00f, 0.97f);
  colors[ImGuiCol_TitleBgActive] = ImVec4(0.00f, 0.29f, 0.00f, 1.00f);
  colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.00f, 0.00f, 0.00f, 0.48f);
  colors[ImGuiCol_MenuBarBg] = ImVec4(0.00f, 0.00f, 0.00f, 1.00f);
  colors[ImGuiCol_ScrollbarBg] = ImVec4(0.02f, 0.00f, 0.00f, 0.53f);
  colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.00f, 0.31f, 0.00f, 1.00f);
  colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.00f, 0.41f, 0.00f, 1.00f);
  colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.00f, 0.51f, 0.00f, 1.00f);
  colors[ImGuiCol_CheckMark] = ImVec4(0.00f, 0.94f, 0.00f, 1.00f);
  colors[ImGuiCol_SliderGrab] = ImVec4(0.00f, 0.51f, 0.00f, 1.00f);
  colors[ImGuiCol_SliderGrabActive] = ImVec4(0.00f, 0.86f, 0.00f, 1.00f);
  colors[ImGuiCol_Button] = ImVec4(0.00f, 0.44f, 0.00f, 0.00f);
  colors[ImGuiCol_ButtonHovered] = ImVec4(0.00f, 0.47f, 0.00f, 1.00f);
  colors[ImGuiCol_ButtonActive] = ImVec4(0.00f, 0.42f, 0.00f, 1.00f);
  colors[ImGuiCol_Header] = ImVec4(0.00f, 1.00f, 0.00f, 0.11f);

  colors[ImGuiCol_HeaderHovered] = ImVec4(0.00f, 0.70f, 0.00f, 0.80f);
  colors[ImGuiCol_HeaderActive] = ImVec4(0.00f, 0.50f, 0.00f, 1.00f);
  colors[ImGuiCol_Separator] = ImVec4(0.00f, 0.43f, 0.00f, 0.50f);
  colors[ImGuiCol_SeparatorHovered] = ImVec4(0.00f, 0.72f, 0.00f, 0.78f);
  colors[ImGuiCol_SeparatorActive] = ImVec4(0.00f, 0.51f, 0.00f, 1.00f);
  colors[ImGuiCol_ResizeGrip] = ImVec4(0.00f, 0.91f, 0.00f, 0.25f);
  colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.00f, 0.81f, 0.00f, 0.67f);
  colors[ImGuiCol_ResizeGripActive] = ImVec4(0.00f, 0.46f, 0.00f, 0.95f);
  colors[ImGuiCol_Tab] = ImVec4(0.00f, 0.35f, 0.00f, 0.86f);
  colors[ImGuiCol_TabHovered] = ImVec4(0.00f, 0.59f, 0.00f, 0.80f);
  colors[ImGuiCol_TabActive] = ImVec4(0.00f, 0.41f, 0.00f, 1.00f);
  colors[ImGuiCol_TabUnfocused] = ImVec4(0.00f, 0.00f, 0.00f, 0.97f);
  colors[ImGuiCol_TabUnfocusedActive] = ImVec4(0.00f, 0.34f, 0.00f, 1.00f);
  colors[ImGuiCol_DockingPreview] = ImVec4(0.00f, 0.59f, 0.00f, 0.70f);
  colors[ImGuiCol_DockingEmptyBg] = ImVec4(0.00f, 0.20f, 0.00f, 1.00f);
  colors[ImGuiCol_PlotLines] = ImVec4(0.00f, 0.61f, 0.00f, 1.00f);
  colors[ImGuiCol_PlotLinesHovered] = ImVec4(0.00f, 0.43f, 0.00f, 1.00f);
  colors[ImGuiCol_PlotHistogram] = ImVec4(0.00f, 0.60f, 0.00f, 1.00f);
  colors[ImGuiCol_PlotHistogramHovered] = ImVec4(0.00f, 0.60f, 0.00f, 1.00f);
  colors[ImGuiCol_TextSelectedBg] = ImVec4(0.00f, 0.87f, 0.00f, 0.35f);
  colors[ImGuiCol_DragDropTarget] = ImVec4(0.00f, 1.00f, 0.00f, 0.90f);
  colors[ImGuiCol_NavHighlight] = ImVec4(0.00f, 0.60f, 0.00f, 1.00f);
  colors[ImGuiCol_NavWindowingHighlight] = ImVec4(0.00f, 1.00f, 0.00f, 0.70f);
  colors[ImGuiCol_NavWindowingDimBg] = ImVec4(0.00f, 0.80f, 0.00f, 0.20f);
  colors[ImGuiCol_ModalWindowDimBg] = ImVec4(0.00f, 0.80f, 0.00f, 0.35f);

  // set rounding and borders
  style->ChildRounding = 0;
  style->FrameRounding = 0;
  style->GrabRounding = 0;
  style->PopupRounding = 0;
  style->ScrollbarRounding = 0;
  style->TabRounding = 0;
  style->WindowRounding = 0;

  style->ChildBorderSize = 1;
  style->FrameBorderSize = 1;
  style->PopupBorderSize = 1;
  style->TabBorderSize = 1;
  style->WindowBorderSize = 1;
}

App::App() {}

void App::init(int argc, char* argv[], const char* appName, int w, int h) {
  xhfr::init(argc, argv, appName, w, h);
  XHFR_DEBUG("XHFR INIT COMPLETE");

  ImFontConfig cfg;
  // float sampling = 1.6;

  PHYSFS_mountMemory(data, data_len, nullptr, "compressed.zip", "/res/", 0);
  PHYSFS_mount("./", "/", 0);
  PHYSFS_setWriteDir("./");
  XHFR_DEBUG("MOUNTING COMPLETE");

  ImFont* fcfg = xhfr::FontManager::getInstance().addFont(
      ":res/app/fonts/Cantarell.ttf", 16, &cfg);
  xhfr::FontManager::getInstance().addDefaultFont();
  fcfg->Scale = 1.f;  /// 512.f;

  ImGuiIO& io = ImGui::GetIO();

  zw = std::make_shared<TinyIDE>();
  zw->setFont(io.Fonts->Fonts[1]);

  toolBar = std::make_shared<ToolBar>();
  console = std::make_shared<Console>();

  toolBar->hideCloseButton(true);
  console->hideCloseButton(true);
  zw->hideCloseButton(true);

  zw->setVisible(true);
  console->state = &luaState;
  console->setVisible(true);
  toolBar->setVisible(true);

  XHFR_DEBUG("Loading layout");
  xhfr::File f(":/res/app/imgui.ini");
  auto data = f.readAll();
  ImGui::LoadIniSettingsFromMemory(data.c_str(), data.size());

  toolBar->clearStateHandler = [this]() {
    luaState = sol::state();
    luaState.open_libraries();
    console->initState();
    console->addLineToConsole("--Lua state cleared--");
  };


  //this will be executed on run
  toolBar->runHandler = [this]() {
    auto doc = zw->getDocuments()[0];
    auto code = doc->text();

        execEngine.setTask([code,this](){
            try {
            toolBar->setRunning(true);
            luaState.script(code);
            toolBar->setRunning(false);
            console->addLineToConsole("-- Program execution ended --\n");
            } catch (std::exception& e) {
                console->addLineToConsole(e.what());
            }
        });

    console->addLineToConsole("-- Program execution started --\n");
  };


  toolBar->changeColorHandler = [this](bool useDark){
      zw->useDarkTheme(useDark);
  };

  zw->setSaveFileCallback(
      [](const std::shared_ptr<TinyIDE::Document>& document) {
        auto text = document->text();
#ifdef EMSCRIPTEN
        xhfr::emscripten_download_data(text.c_str(), text.size(), "code.lua");
#endif
      });

  auto code = R"(-- LuaPad free online lua sandbox
-- Copyright 2021 Quentin Kammann
--Luapad v0.9.1
--Changelog:
--    *add running program indicator
--    *make console copyable
--    *add a white mode
--    *add text to clear console button
print("Hello World !")

function fib(m)
    if m < 2 then
        return m
    end

    return fib(m -1) + fib(m-2)
end

print("Fib 13 is", fib(13))
    )";

  xhfr::addUserFunction([](){

  });

  zw->create("SCRATCHPAD", {TinyIDE::DocumentOptions::Lua}, code);
  luaState.open_libraries();
  zw->addShortcut(
      [this]() {
        toolBar->runHandler();
      },
      XHFR_KEY(ENTER), true);

  // shortcuts
  {
    zw->addShortcut(
        [this]() {
          auto doc = zw->getDocuments()[0];
          auto pos = doc->editor.GetCursorPosition();
          auto line = doc->editor.GetCurrentLineText();

          // swap comment stuff
          bool addCommentMark = true;
          if (line.length() > 1) {
            if (line[0] == '-' && line[1] == '-') {
              addCommentMark = false;
            }
          }
          if (addCommentMark) {
            line = "--" + line;
          } else {
            line = line.substr(2);
          }
          auto lines = doc->editor.GetTextLines();
          lines[pos.mLine] = line;
          doc->editor.SetTextLines(lines);
          // end swap
        },
        XHFR_KEY(SLASH), true);

    auto deleteWord = [this]() {
      auto doc = zw->getDocuments()[0];

      auto pos = doc->editor.GetCursorPosition();
      auto line = doc->editor.GetCurrentLineText();
      auto lines = doc->editor.GetTextLines();

      auto& editor = doc->editor;

      if (pos.mColumn == 0) {
        editor.Delete();
        return;
      }

      if (line.size() < 2) {
        lines.erase(lines.begin() + pos.mLine);
        editor.SetTextLines(lines);
        editor.MoveUp();
        editor.MoveEnd();
        return;
      }

      // start from the right side of the word and stop when a delimiter is
      // found
      size_t wordStartPosition = 0;
      for (int i = pos.mColumn - 1; i != 0; --i) {
        std::vector<char> delimiters({' ', '(', ')'});
        if (std::any_of(delimiters.begin(), delimiters.end(),
                        [character = line[i]](char delimiter) {
                          return character == delimiter;
                        })) {
          wordStartPosition = i;
          break;
        }
      }
      auto len = pos.mColumn - wordStartPosition;
      editor.MoveLeft(len);

      // remove the word from the current line
      line.erase(wordStartPosition, len);

      // change the document
      lines[pos.mLine] = line;
      doc->editor.SetTextLines(lines);
    };
    zw->addShortcut(
        [this, deleteWord]() {
          deleteWord();
        },
        XHFR_KEY(BACKSPACE), true);

    zw->addShortcut(
        [this, deleteWord]() {
          deleteWord();
        },
        XHFR_KEY(DELETE), true);
  }
}
