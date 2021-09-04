#include "ZepWindow.hpp"

#include "zep/filesystem.h"
#include "zep/imgui/display_imgui.h"
#include "zep/imgui/editor_imgui.h"
#include "zep/mode_standard.h"
#include "zep/mode_vim.h"
#include "zep/tab_window.h"
#include "zep/theme.h"
#include "zep/window.h"

// A helper struct to init the editor and handle callbacks
struct ZepContainerImGui : public IZepComponent, public IZepReplProvider
{
    ZepContainerImGui(const std::string& startupFilePath, const std::string& configPath)
        : spEditor(std::make_unique<ZepEditor_ImGui>(configPath, GetPixelScale()))
        //, fileWatcher(spEditor->GetFileSystem().GetConfigPath(), std::chrono::seconds(2))
    {
        chibi_init(scheme, SDL_GetBasePath());

        // ZepEditor_ImGui will have created the fonts for us; but we need to build
        // the font atlas
        auto fontPath = std::string(SDL_GetBasePath()) + "Cousine-Regular.ttf";
        auto& display = static_cast<ZepDisplay_ImGui&>(spEditor->GetDisplay());

        int fontPixelHeight = (int)dpi_pixel_height_from_point_size(DemoFontPtSize, GetPixelScale().y);

        auto& io = ImGui::GetIO();
        ImVector<ImWchar> ranges;
        ImFontGlyphRangesBuilder builder;
        builder.AddRanges(io.Fonts->GetGlyphRangesDefault()); // Add one of the default ranges
        builder.AddRanges(io.Fonts->GetGlyphRangesCyrillic()); // Add one of the default ranges
        builder.AddRanges(greek_range);
        builder.BuildRanges(&ranges); // Build the final result (ordered ranges with all the unique characters submitted)

        ImFontConfig cfg;
        cfg.OversampleH = 4;
        cfg.OversampleV = 4;

        auto pImFont = ImGui::GetIO().Fonts->AddFontFromFileTTF(fontPath.c_str(), float(fontPixelHeight), &cfg, ranges.Data);

        display.SetFont(ZepTextType::UI, std::make_shared<ZepFont_ImGui>(display, pImFont, fontPixelHeight));
        display.SetFont(ZepTextType::Text, std::make_shared<ZepFont_ImGui>(display, pImFont, fontPixelHeight));
        display.SetFont(ZepTextType::Heading1, std::make_shared<ZepFont_ImGui>(display, pImFont, int(fontPixelHeight * 1.75)));
        display.SetFont(ZepTextType::Heading2, std::make_shared<ZepFont_ImGui>(display, pImFont, int(fontPixelHeight * 1.5)));
        display.SetFont(ZepTextType::Heading3, std::make_shared<ZepFont_ImGui>(display, pImFont, int(fontPixelHeight * 1.25)));

        unsigned int flags = 0; // ImGuiFreeType::NoHinting;
        ImGuiFreeType::BuildFontAtlas(ImGui::GetIO().Fonts, flags);

        spEditor->RegisterCallback(this);

        ZepMode_Orca::Register(*spEditor);

        ZepRegressExCommand::Register(*spEditor);

        // Repl
        ZepReplExCommand::Register(*spEditor, this);
        ZepReplEvaluateOuterCommand::Register(*spEditor, this);
        ZepReplEvaluateInnerCommand::Register(*spEditor, this);
        ZepReplEvaluateCommand::Register(*spEditor, this);

        if (!startupFilePath.empty())
        {
            spEditor->InitWithFileOrDir(startupFilePath);
        }
        else
        {
            spEditor->InitWithText("Shader.vert", shader);
        }

        // File watcher not used on apple yet ; needs investigating as to why it doesn't compile/run
        // The watcher is being used currently to update the config path, but clients may want to do more interesting things
        // by setting up watches for the current dir, etc.
        /*fileWatcher.start([=](std::string path, FileStatus status) {
            if (spEditor)
            {
                ZLOG(DBG, "Config File Change: " << path);
                spEditor->OnFileChanged(spEditor->GetFileSystem().GetConfigPath() / path);
            }
        });*/
    }

    ~ZepContainerImGui()
    {
    }

ZepWindow::ZepWindow() {
  setTitle("ZepWindow");

}

void ZepWindow::onDraw() {
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
  };
  ImGui::PopStyleVar();

  ImGui::SetCursorPosX((ImGui::GetWindowWidth() - 400) * 0.5);

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

  ImGui::SetCursorPosX((ImGui::GetWindowWidth() - 100) * 0.5);
  if (ImGui::Button("Close", ImVec2(100, 0))) {
    setVisible(false);
  }
}
