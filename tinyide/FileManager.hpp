#ifndef FILEMANAGER_HPP
#define FILEMANAGER_HPP

#include <functional>
#include <vector>
#include "physfs.h"
#include "xhfr.hpp"

class FileManager : public xhfr::Window {
 public:
  struct MenuEntry {
    std::string optionName;
    xhfr::fs::FileType type = xhfr::fs::FileType::Regular;
    std::function<void(const xhfr::fs::FileInfo&)> callback;
    bool shouldShowOption(const xhfr::fs::FileInfo info);
  };
  enum FileManagerType { None, Create, Select } currentFileManagerType = None;
  FileManager(FileManagerType fileManagerType = None);
  void onDraw() override;
  static std::vector<MenuEntry> menuOptions;

  std::vector<xhfr::fs::FileInfo> getSelectedFiles();
  void setOnOkAction(std::function<void()> action);
  void setOnFileClickedAction(std::function<void()>);
  // void
  // setFileFilters(std::vector<std::pair<std::string,std::vector<std::string>>>
  // filters); // validFilter = {"All Image files",{{"png"},{"jpg"}}} "

 private:
  void update();
  void optionsMenu();
  void mountpointsMenu();
  void fileManagerType();
  void bookmarks();

  bool showMountMenu = false, showToolbar = false;

  std::function<void()> fileClickedAction, onOkayAction;
  std::string newFileName = "";

  std::vector<xhfr::fs::FileInfo> filesInDir;
  std::vector<bool> filesSelected;
  std::string currentPath = ":/";
  xhfr::Image chevronUpImg = xhfr::Image(":/res/tinyide/chevron.png");
  xhfr::Image reload = xhfr::Image(":/res/tinyide/reload.png");
  xhfr::Image createFolder = xhfr::Image(":/res/tinyide/add_folder.png");
  xhfr::Image folder = xhfr::Image(":/res/tinyide/folder.png");
  xhfr::Image lock = xhfr::Image(":/res/tinyide/lock.png");
};

#endif  // FILEMANAGER_HPP
