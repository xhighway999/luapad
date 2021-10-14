#ifndef TINYIDE_HPP
#define TINYIDE_HPP

#include <functional>
#include <vector>
#include <atomic>

#include <thread>
#include "ImGuiColorTextEdit/TextEditor.h"
#include "xhfr.hpp"

// Todo: abstract / complex storage system for vfs and etc.

struct IDEApplicationInterface {
  std::function<void()> onRun;
};

class TinyIDE : public xhfr::Window {
 public:
  struct DocumentOptions {
    enum CodeStyle { None = 0, Lua = 1 } codeStyle;
  };

  struct Document {
    std::string text() { return editor.GetText(); }
    std::string title = "Unnamed";
    bool unsaved = false, visible = false;
    TextEditor editor;
  };

  struct Shortcut {
    int key;
    bool control;
    std::function<void()> callback;
  };

  TinyIDE();
  std::shared_ptr<Document> create(std::string_view title = "Unnamed Document",
                                   DocumentOptions dO = {},
                                   std::string text = "");
  void onDraw() override;
  const std::vector<std::shared_ptr<Document>>& getDocuments() const;

  void addShortcut(std::function<void()> callback, int key, bool ctrl = false);

  void setSaveFileCallback(
      const std::function<void(const std::shared_ptr<Document>&)>& value);

  void setFont(ImFont* newFont);

  void useDarkTheme(bool t = true);

 private:

  void handleShortcuts();
  std::function<void(const std::shared_ptr<Document>&)> saveFileCallback;
  std::vector<std::shared_ptr<Document>> documents;
  std::vector<Shortcut> shortcuts;
  std::shared_ptr<Document> visibleDoc;
  ImFont* font = nullptr;
  bool showTabs = false;
};

#endif  // TINYIDE_HPP
