#include "TinyIDE.hpp"

TinyIDE::TinyIDE() {
  setTitle("TinyIDE");
}

std::shared_ptr<TinyIDE::Document> TinyIDE::create(std::string_view title,
                                                   DocumentOptions dO,
                                                   std::string text) {
  std::shared_ptr<Document> doc = std::make_shared<Document>();
  doc->visible = true;
  doc->editor.SetText(text);
  doc->title = title;
  if (dO.codeStyle == DocumentOptions::Lua) {
    doc->editor.SetLanguageDefinition(TextEditor::LanguageDefinition::Lua());
  }
  documents.push_back(doc);
  return doc;
}

void TinyIDE::onDraw() {
  // Tab bar
  if (font) {
    ImGui::PushFont(font);
  }
  ImGuiTabBarFlags flags = ImGuiTabBarFlags_Reorderable;
  if (showTabs && ImGui::BeginTabBar("##tabs", flags)) {
    int i = 0;
    for (auto& doc : documents) {
      ImGui::PushID(i);
      ImGuiTabItemFlags itemFlags = 0;
      // Unsaved
      itemFlags |= (doc->unsaved ? ImGuiTabItemFlags_UnsavedDocument : 0);
      bool vis = ImGui::BeginTabItem(doc->title.c_str(), nullptr, itemFlags);
      doc->visible = vis;
      if (vis) {
        size_t prevSize = doc->editor.GetText().size();
        doc->editor.Render(doc->title.c_str());
        if (doc->editor.GetText().size() != prevSize) {
          doc->unsaved = true;
        }
        visibleDoc = doc;
        ImGui::EndTabItem();
      }
      i++;
      ImGui::PopID();
    }
    ImGui::EndTabBar();
  } else {
    for (auto& doc : documents) {
      if (doc->visible) {
        size_t prevSize = doc->editor.GetText().size();
        doc->editor.Render(doc->title.c_str());
        if (doc->editor.GetText().size() != prevSize) {
          doc->unsaved = true;
        }
        visibleDoc = doc;
      }
    }
  }

  int i = 0;
  for (auto& doc : documents) {
    if (doc->visible) {
      ImGui::PushID(i);
      i++;
      ImGui::PopID();
    }
  }
  handleShortcuts();
  if (font) {
    ImGui::PopFont();
  }
}

const std::vector<std::shared_ptr<TinyIDE::Document> >& TinyIDE::getDocuments()
    const {
  return documents;
}

void TinyIDE::addShortcut(std::function<void()> callback, int key, bool ctrl) {
  Shortcut sc;
  sc.key = key;
  sc.control = ctrl;
  sc.callback = callback;
  shortcuts.push_back(sc);
}

void TinyIDE::setSaveFileCallback(
    const std::function<void(const std::shared_ptr<Document>&)>& value) {
  saveFileCallback = value;
}

void TinyIDE::handleShortcuts() {
  // ImGui::ShowDemoWindow();
  ImGuiIO& io = ImGui::GetIO();
  if (io.KeyCtrl && ImGui::IsKeyPressed(XHFR_KEY(S))) {
    saveFileCallback(visibleDoc);
    visibleDoc->unsaved = false;
  }
  if (io.KeyCtrl && ImGui::IsKeyPressed(XHFR_KEY(W))) {
    ImGui::OpenPopup("");
  }
  for (auto& shortcut : shortcuts) {
    if (shortcut.control && io.KeyCtrl) {
      if (ImGui::IsKeyPressed(shortcut.key)) {
        shortcut.callback();
      }
    }
  }

  // if (ImGui::IsKeyPressed()) {

  //}
}

void TinyIDE::setFont(ImFont* newFont) {
    font = newFont;
}

void TinyIDE::useDarkTheme(bool t)
{
    TextEditor::Palette p;
    p = TextEditor::GetLightPalette();
    if (t) {
        p = TextEditor::GetDarkPalette();
    }

    for (auto& doc : documents) {
        auto& te = doc->editor;
        te.SetPalette(p);
    }
}
